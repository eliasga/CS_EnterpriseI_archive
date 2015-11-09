/************************************************************************************
This is a modified version of the demo software HighResWebcamDemo, available from 
https://github.com/OculusRiftInAction/OculusRiftInAction.git

The program originally shows a live video feed on the Oculus Rift display.
It has been modified to sensor data over a TCP server and display som attitude information to the user.

Eirik Valle, 08-06-2015 - Trondheim, Norway
*************************************************************************************/


#include "Common.h"

#include <opencv2/opencv.hpp>
#include <thread>
#include <mutex>

#include<io.h>
#include<stdio.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

// Define camera paramters and streams

#define CAMERA_PARAMS_FILE "camera.xml"
#define CAMERA_WIDTH 1280
#define CAMERA_HEIGHT 720
#define CAMERA_HFOV_DEGREES 70.42f
#define IMAGE_DISTANCE 1.0f//10.0f

#define CAMERA_DEVICE 0																// If camera device is webcam input 0,1 or 2...							
//#define CAMERA_DEVICE "http://192.168.254.10:8090/?action=stream ;type=.mjpg"     // Stream input, this stream type represents the Beaglbone stream
//#define CAMERA_DEVICE "http://78.91.48.191:8080/video?x.mjpg"						// Stream input, this stream type represents the Android app stream

#define CAMERA_LATENCY 0.040
#define CAMERA_ASPECT ((float)CAMERA_WIDTH / (float)CAMERA_HEIGHT)
//#define CAMERA_ASPECT ((float)CAMERA_HEIGHT/(float)CAMERA_WIDTH)
#define CAMERA_HALF_FOV (CAMERA_HFOV_DEGREES / 2.0f) * DEGREES_TO_RADIANS
#define CAMERA_SCALE (tan(CAMERA_HALF_FOV) * IMAGE_DISTANCE)


//initialize socket server
SOCKET initServer(){
	WSADATA wsa;
	SOCKET s, new_socket;
	struct sockaddr_in server, client;
	int c;

	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		return 1;
	}

	printf("Initialised.\n");

	//Create a socket
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
	}

	printf("Socket created.\n");

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(52717);

	//Bind
	if (bind(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	puts("Bind done");

	//Listen to incoming connections
	listen(s, 3);

	//Accept and incoming connection
	puts("Waiting for incoming connections...");

	c = sizeof(struct sockaddr_in);

	if ((new_socket = accept(s, (struct sockaddr *)&client, &c)) != INVALID_SOCKET)
		puts("Connection accepted");
	if (new_socket == INVALID_SOCKET)
	{
		printf("accept failed with error code : %d", WSAGetLastError());
		return 1;
	}
	return new_socket;
}


// Sen data function
void sendData(SOCKET s, int roll, int pitch, int yaw){
	char buffer[256];
	//int buflen;
	int data = 0;
	sprintf_s(buffer, "%10d\t%10d\t%10d\t%10d\t%10d\t%10d\t%10d\t%10d\t%10d\t%10d\t%10d\t%10d\t%10d\t%10d\t%10d\t%10d\t%10d\t%10d\t%10d\t%10d\t%10d\t%10d\n",
		roll, pitch, yaw, data + 4000, data + 5000, data + 6000, data + 7000, data + 8000, data + 9000, data + 10000, data + 11000, data + 12000, data + 13000,
		data + 14000, data + 15000, data + 16000, data + 17000, data + 18000, data + 19000, data + 20000, data + 21000, data + 22000);
	int buflen = strlen(buffer);
	//Reply to the client
	send(s, buffer, buflen, 0);
	//Sleep(10);

	//return 0;
}
// Terminate server function
void closeServer(SOCKET s){
	closesocket(s);
	puts("closed");
	WSACleanup();
}

template <class T>
class CaptureHandler {
private:
  typedef std::lock_guard<std::mutex> lock_guard;

  std::thread captureThread;
  std::mutex mutex;

  bool changed{ false };
  bool stop{ false };

  float firstCapture{ -1 };
  int captures{ -1 };
  float cps{ -1 };

  T result;

protected:

  bool isStopped() {
    return stop;
  }

  void setResult(const T & newResult) {
    if (0 == ++captures) {
      firstCapture = Platform::elapsedSeconds();
    }
    lock_guard guard(mutex);
    result = newResult;
    changed = true;
  }

public:

  float getCapturesPerSecond() {
    if (-1 == captures) {
      return 0;
    }

    float elapsed = Platform::elapsedSeconds() - firstCapture;
    if (elapsed > 2.0f) {
      cps = (float)captures / elapsed;
      captures = -1;
    }
    if (cps > 0) {
      return cps;
    }
    return (float)captures / elapsed;
  }

  void startCapture() {
    stop = false;
    captureThread = std::thread(&CaptureHandler::captureLoop, this);
  }

  void stopCapture(SOCKET new_socket) {
    stop = true;
    captureThread.join();
	stopCapture(new_socket);
  }

  bool getResult(T & outResult) {
    if (!changed) {
      return false;
    }
    lock_guard guard(mutex);
    changed = false;
    outResult = result;
    result = T();
    return true;
  }

  virtual void captureLoop() = 0;
};

struct CaptureData {
  ovrPosef pose;
  cv::Mat image;
};

// This class handles the webcam stream 
class WebcamCaptureHandler : public CaptureHandler<CaptureData> {
private:
  cv::VideoCapture videoCapture;
  ovrHmd hmd;
  cv::Mat distortionMap;
  bool hasCalibration{ false };

public:

  WebcamCaptureHandler(ovrHmd hmd) : hmd(hmd) {
    videoCapture.open(CAMERA_DEVICE);				//Initialize camera
    if (!videoCapture.isOpened()) {					
      FAIL("Could not open video source");
    }

    cv::Mat cameraMatrix;
    cv::Mat distCoeffs;
    cv::Mat map1, map2;

    cv::FileStorage fs(CAMERA_PARAMS_FILE, cv::FileStorage::READ); // Read the settings
    if (fs.isOpened()) {
      fs["Camera_Matrix"] >> cameraMatrix;
      fs["Distortion_Coefficients"] >> distCoeffs;
      hasCalibration = true;
      cv::Size imageSize(CAMERA_WIDTH, CAMERA_HEIGHT);
      cv::Mat optimalMatrix = getOptimalNewCameraMatrix(
        cameraMatrix, distCoeffs, imageSize, 1, imageSize, 0);
      initUndistortRectifyMap(cameraMatrix, distCoeffs, cv::Mat(), 
        optimalMatrix, imageSize, CV_16SC2, map1, map2);
      distortionMap = cv::Mat(imageSize, CV_32FC2);
      cv::Mat map3(imageSize, CV_32FC1);
      cv::convertMaps(map1, map2, distortionMap, map3, CV_32FC2);
    }

    videoCapture.set(CV_CAP_PROP_FRAME_WIDTH, CAMERA_WIDTH);
    videoCapture.set(CV_CAP_PROP_FRAME_HEIGHT, CAMERA_HEIGHT);
    videoCapture.set(CV_CAP_PROP_FPS, 60);
  }
  //camera loop
  virtual void captureLoop() {				
	  cv::Point org(150, 700);			
	  std::string Pitch("  Pitch:  ");
	  std::string Roll("  Roll:  ");
	  std::string Yaw("  Yaw:  ");
	  std::string text;
    while (!isStopped()) {
      CaptureData captured;
      float captureTime = 
        ovr_GetTimeInSeconds() - CAMERA_LATENCY;
      ovrTrackingState tracking = 
        ovrHmd_GetTrackingState(hmd, captureTime);
      captured.pose = tracking.HeadPose.ThePose;

      if (!videoCapture.grab() ||
          !videoCapture.retrieve(captured.image)) {
        FAIL("Failed video capture");
      }

      if (hasCalibration) {
        remap(captured.image.clone(), captured.image, distortionMap, cv::Mat(), cv::INTER_LINEAR);
      }
	
	  ovrTrackingState state = ovrHmd_GetTrackingState(hmd, 0);//
	  ovrQuatf orientation = state.HeadPose.ThePose.Orientation;//
	  glm::quat q = glm::make_quat(&orientation.x);
	  glm::vec3 euler = glm::eulerAngles(q);//

	  int roll = -euler.z* RADIANS_TO_DEGREES;
	  int pitch = -euler.x* RADIANS_TO_DEGREES;
	  int yaw = -euler.y* RADIANS_TO_DEGREES;

	  text = "Head attitude:  " + Pitch + std::to_string(pitch) + Roll + std::to_string(roll) + Yaw + std::to_string(yaw);
	  cv::putText(captured.image, text, org, 2, CV_FONT_HERSHEY_PLAIN, CV_RGB(255, 0, 0), 4, 8, false);						

      cv::flip(captured.image.clone(), captured.image, 0);
      setResult(captured);
    }
  }
};

class WebcamApp : public RiftApp
{
protected:
  WebcamCaptureHandler captureHandler;
  CaptureData captureData;

  TexturePtr texture;
  ShapeWrapperPtr videoGeometry;
  ProgramPtr videoRenderProgram;
  SOCKET new_socket;

public:

  WebcamApp() : captureHandler(hmd) {
    captureHandler.startCapture();
  }

  virtual ~WebcamApp() {
	  captureHandler.stopCapture(new_socket);
  }


void initGl() {
  RiftApp::initGl();
  glEnable(GL_PRIMITIVE_RESTART);
  glPrimitiveRestartIndex(UINT_MAX);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  videoRenderProgram = oria::loadProgram(
    Resource::SHADERS_TEXTURED_VS,
    Resource::SHADERS_TEXTURED_FS);

  using namespace oglplus;
  texture = TexturePtr(new Texture());
  Context::Bound(TextureTarget::_2D, *texture)
    .MagFilter(TextureMagFilter::Linear)
    .MinFilter(TextureMinFilter::Linear);
  DefaultTexture().Bind(TextureTarget::_2D);

  videoGeometry = oria::loadPlane(videoRenderProgram, CAMERA_ASPECT);

  new_socket = initServer();
}

virtual void update() {
  if (captureHandler.getResult(captureData)) {
    using namespace oglplus;
    Context::Bound(TextureTarget::_2D, *texture)
      .Image2D(0, PixelDataInternalFormat::RGBA8,
             captureData.image.cols, captureData.image.rows, 0,
             PixelDataFormat::BGR, PixelDataType::UnsignedByte,
             captureData.image.data);
    DefaultTexture().Bind(TextureTarget::_2D);
	
  }
}


// Render scnene on Oculus Rift
virtual void renderScene() {
  glClear(GL_DEPTH_BUFFER_BIT);
  oria::renderSkybox(Resource::IMAGES_SKY_CITY_XNEG_PNG);
  MatrixStack & mv = Stacks::modelview();

  mv.withPush([&]{
    mv.identity();

    glm::quat eyePose = ovr::toGlm(getEyePose().Orientation);
    glm::quat webcamPose = ovr::toGlm(captureData.pose.Orientation);
    glm::mat4 webcamDelta = glm::mat4_cast(glm::inverse(eyePose) * webcamPose);
	
	

    mv.preMultiply(webcamDelta);
    mv.translate(glm::vec3(0, 0, -IMAGE_DISTANCE));

    texture->Bind(oglplus::Texture::Target::_2D);
    oria::renderGeometry(videoGeometry, videoRenderProgram);
    oglplus::DefaultTexture().Bind(oglplus::Texture::Target::_2D);
  });

  std::string message = Platform::format(
    "OpenGL FPS: %0.2f\n"
    "Vidcap FPS: %0.2f\n",
    fps, captureHandler.getCapturesPerSecond());
  GlfwApp::renderStringAt(message, glm::vec2(-0.5f, 0.5f));

  
  ovrTrackingState state = ovrHmd_GetTrackingState(hmd, 0);//
  ovrQuatf orientation = state.HeadPose.ThePose.Orientation;//
  glm::quat q = glm::make_quat(&orientation.x);
  glm::vec3 euler = glm::eulerAngles(q);


  int roll = euler.z * 10000;
  int pitch = euler.x * 10000;
  int yaw = euler.y * 10000;
 
  // Send data to control system
  sendData(new_socket, roll, pitch, yaw);

};

RUN_OVR_APP(WebcamApp);

