﻿<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="14008000">
	<Property Name="SMProvider.SMVersion" Type="Int">201310</Property>
	<Item Name="My Computer" Type="My Computer">
		<Property Name="IOScan.Faults" Type="Str"></Property>
		<Property Name="IOScan.NetVarPeriod" Type="UInt">100</Property>
		<Property Name="IOScan.NetWatchdogEnabled" Type="Bool">false</Property>
		<Property Name="IOScan.Period" Type="UInt">10000</Property>
		<Property Name="IOScan.PowerupMode" Type="UInt">0</Property>
		<Property Name="IOScan.Priority" Type="UInt">9</Property>
		<Property Name="IOScan.ReportModeConflict" Type="Bool">true</Property>
		<Property Name="IOScan.StartEngineOnDeploy" Type="Bool">false</Property>
		<Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="Control Panel" Type="Folder">
			<Item Name="Camera Control.vi" Type="VI" URL="../Camera Control.vi"/>
			<Item Name="Collecting Unit.vi" Type="VI" URL="../Collecting Unit.vi"/>
			<Item Name="Light Panel.vi" Type="VI" URL="../Light Panel.vi"/>
			<Item Name="Manipulator Panel.vi" Type="VI" URL="../Manipulator Panel.vi"/>
		</Item>
		<Item Name="Controllers" Type="Folder">
			<Item Name="BoolPushCust.ctl" Type="VI" URL="../BoolPushCust.ctl"/>
			<Item Name="ConnectionButton.ctl" Type="VI" URL="../ConnectionButton.ctl"/>
			<Item Name="Control 1.ctl" Type="VI" URL="../Control 1.ctl"/>
			<Item Name="Control 2.ctl" Type="VI" URL="../Control 2.ctl"/>
			<Item Name="Control 3.ctl" Type="VI" URL="../Control 3.ctl"/>
			<Item Name="Control 22.ctl" Type="VI" URL="../Control 22.ctl"/>
		</Item>
		<Item Name="Dialog Boxes" Type="Folder">
			<Item Name="About.vi" Type="VI" URL="../About.vi"/>
			<Item Name="AltitudeDialog.vi" Type="VI" URL="../AltitudeDialog.vi"/>
			<Item Name="DialogMenu.rtm" Type="Document" URL="../DialogMenu.rtm"/>
			<Item Name="EasterEgg.vi" Type="VI" URL="../EasterEgg.vi"/>
			<Item Name="SetOriginPanel.vi" Type="VI" URL="../SetOriginPanel.vi"/>
			<Item Name="Startup Panel.vi" Type="VI" URL="../Startup Panel.vi"/>
		</Item>
		<Item Name="Functions" Type="Folder">
			<Item Name="Change Map Range.vi" Type="VI" URL="../Change Map Range.vi"/>
			<Item Name="Create Joystick Message.vi" Type="VI" URL="../Create Joystick Message.vi"/>
			<Item Name="HeadingMod.vi" Type="VI" URL="../HeadingMod.vi"/>
			<Item Name="Joystick Mapping Function.vi" Type="VI" URL="../Joystick Mapping Function.vi"/>
			<Item Name="LogStringCreator.vi" Type="VI" URL="../LogStringCreator.vi"/>
			<Item Name="LogThrustStringCreator.vi" Type="VI" URL="../LogThrustStringCreator.vi"/>
			<Item Name="Read Attitude Msg.vi" Type="VI" URL="../Read Attitude Msg.vi"/>
			<Item Name="Read Input String.vi" Type="VI" URL="../Read Input String.vi"/>
			<Item Name="Read Ship States.vi" Type="VI" URL="../Read Ship States.vi"/>
			<Item Name="ReadAltitudeMsg.vi" Type="VI" URL="../ReadAltitudeMsg.vi"/>
			<Item Name="ReadThrusterMsg.vi" Type="VI" URL="../ReadThrusterMsg.vi"/>
			<Item Name="Restart Procedure.vi" Type="VI" URL="../Restart Procedure.vi"/>
			<Item Name="Stop VIs.vi" Type="VI" URL="../Stop VIs.vi"/>
		</Item>
		<Item Name="GraphView" Type="Folder">
			<Item Name="AltitudePlots.vi" Type="VI" URL="../AltitudePlots.vi"/>
			<Item Name="ECFPlot.vi" Type="VI" URL="../ECFPlot.vi"/>
			<Item Name="GraphView.vi" Type="VI" URL="../GraphView.vi"/>
			<Item Name="MTiPlots.vi" Type="VI" URL="../MTiPlots.vi"/>
			<Item Name="PositionPlotInterval.vi" Type="VI" URL="../PositionPlotInterval.vi"/>
			<Item Name="PositionPlots.vi" Type="VI" URL="../PositionPlots.vi"/>
			<Item Name="ThrustPlot.vi" Type="VI" URL="../ThrustPlot.vi"/>
			<Item Name="VelocityPlots.vi" Type="VI" URL="../VelocityPlots.vi"/>
		</Item>
		<Item Name="HelpSites" Type="Folder">
			<Item Name="CameraControlHelp.vi" Type="VI" URL="../CameraControlHelp.vi"/>
			<Item Name="ControlPanelHelp.vi" Type="VI" URL="../ControlPanelHelp.vi"/>
			<Item Name="DPButtonsHelp.vi" Type="VI" URL="../DPButtonsHelp.vi"/>
			<Item Name="DPHelp.vi" Type="VI" URL="../DPHelp.vi"/>
			<Item Name="DPModesHelp.vi" Type="VI" URL="../DPModesHelp.vi"/>
			<Item Name="Empty Panel 3.vi" Type="VI" URL="../Empty Panel 3.vi"/>
			<Item Name="General.vi" Type="VI" URL="../General.vi"/>
			<Item Name="Help Center.vi" Type="VI" URL="../Help Center.vi"/>
			<Item Name="JoystickButtonHelp.vi" Type="VI" URL="../JoystickButtonHelp.vi"/>
			<Item Name="JoystickHelp.vi" Type="VI" URL="../JoystickHelp.vi"/>
			<Item Name="LightPanelHelp.vi" Type="VI" URL="../LightPanelHelp.vi"/>
			<Item Name="ManipulatorPanelHelp.vi" Type="VI" URL="../ManipulatorPanelHelp.vi"/>
			<Item Name="MapVHelp.vi" Type="VI" URL="../MapVHelp.vi"/>
			<Item Name="TrackingButtonsHelp.vi" Type="VI" URL="../TrackingButtonsHelp.vi"/>
			<Item Name="TrackingHelp.vi" Type="VI" URL="../TrackingHelp.vi"/>
			<Item Name="TrackingLawnMowerHelp.vi" Type="VI" URL="../TrackingLawnMowerHelp.vi"/>
			<Item Name="UserGuideMenu.rtm" Type="Document" URL="../UserGuideMenu.rtm"/>
			<Item Name="VesselDHelp.vi" Type="VI" URL="../VesselDHelp.vi"/>
		</Item>
		<Item Name="Mission Control" Type="Folder">
			<Item Name="DP Panel.vi" Type="VI" URL="../DP Panel.vi"/>
			<Item Name="HMI Panel.vi" Type="VI" URL="../HMI Panel.vi"/>
			<Item Name="Tracking Panel.vi" Type="VI" URL="../Tracking Panel.vi"/>
		</Item>
		<Item Name="Object Of Interest" Type="Folder">
			<Item Name="OOI Input Dialog.vi" Type="VI" URL="../Objects Of Interest/OOI Input Dialog.vi"/>
			<Item Name="Read OOI List.vi" Type="VI" URL="../Objects Of Interest/Read OOI List.vi"/>
			<Item Name="UpdateOOI List.vi" Type="VI" URL="../Objects Of Interest/UpdateOOI List.vi"/>
		</Item>
		<Item Name="Options" Type="Folder">
			<Item Name="DP Options.vi" Type="VI" URL="../DP Options.vi"/>
			<Item Name="Extra Buttons.vi" Type="VI" URL="../Extra Buttons.vi"/>
			<Item Name="Joystick Options.vi" Type="VI" URL="../Joystick Options.vi"/>
			<Item Name="Options Panel.vi" Type="VI" URL="../Options Panel.vi"/>
			<Item Name="Port Configuration Options.vi" Type="VI" URL="../Port Configuration Options.vi"/>
			<Item Name="Power Instruments.vi" Type="VI" URL="../Power Instruments.vi"/>
			<Item Name="Tracking Options.vi" Type="VI" URL="../Tracking Options.vi"/>
		</Item>
		<Item Name="Pictures" Type="Folder">
			<Item Name="camerapanel.PNG" Type="Document" URL="../Pictures/camerapanel.PNG"/>
			<Item Name="dppan.PNG" Type="Document" URL="../Pictures/dppan.PNG"/>
			<Item Name="EasterEgg.jpg" Type="Document" URL="../Pictures/EasterEgg.jpg"/>
			<Item Name="joystick.jpg" Type="Document" URL="../Pictures/joystick.jpg"/>
			<Item Name="joystickpanel.PNG" Type="Document" URL="../Pictures/joystickpanel.PNG"/>
			<Item Name="light.PNG" Type="Document" URL="../Pictures/light.PNG"/>
			<Item Name="main.png" Type="Document" URL="../Pictures/main.png"/>
			<Item Name="manipulator.PNG" Type="Document" URL="../Pictures/manipulator.PNG"/>
			<Item Name="mapvis.PNG" Type="Document" URL="../Pictures/mapvis.PNG"/>
			<Item Name="mario10.wav" Type="Document" URL="../Pictures/mario10.wav"/>
			<Item Name="trackingpanel.PNG" Type="Document" URL="../Pictures/trackingpanel.PNG"/>
		</Item>
		<Item Name="Tuning Pages" Type="Folder">
			<Item Name="Update GUI Values" Type="Folder">
				<Item Name="update KF tuning GUI.vi" Type="VI" URL="../Tuning/update KF tuning GUI.vi"/>
				<Item Name="update PID tuning GUI.vi" Type="VI" URL="../Tuning/update PID tuning GUI.vi"/>
			</Item>
			<Item Name="Empty Tuning Panel.vi" Type="VI" URL="../Empty Tuning Panel.vi"/>
			<Item Name="KalmanFilterObserverTuningPanel.vi" Type="VI" URL="../KalmanFilterObserverTuningPanel.vi"/>
			<Item Name="LinearPidTuningPanel.vi" Type="VI" URL="../LinearPidTuningPanel.vi"/>
			<Item Name="LQRTuningPanel.vi" Type="VI" URL="../LQRTuningPanel.vi"/>
			<Item Name="NonLinearPidTuningPanel.vi" Type="VI" URL="../NonLinearPidTuningPanel.vi"/>
			<Item Name="PassiveObserverTuningPanel.vi" Type="VI" URL="../PassiveObserverTuningPanel.vi"/>
			<Item Name="TuningPanel.vi" Type="VI" URL="../TuningPanel.vi"/>
		</Item>
		<Item Name="Useful Routines" Type="Folder">
			<Item Name="Find CS Path.vi" Type="VI" URL="../Useful Routines/Find CS Path.vi"/>
		</Item>
		<Item Name="Control go.ctl" Type="VI" URL="../Control go.ctl"/>
		<Item Name="Empty Panel 2.vi" Type="VI" URL="../Empty Panel 2.vi"/>
		<Item Name="Empty Panel.vi" Type="VI" URL="../Empty Panel.vi"/>
		<Item Name="Graphical User Interface - Frigg.vi" Type="VI" URL="../Graphical User Interface - Frigg.vi"/>
		<Item Name="GUI.ico" Type="Document" URL="../GUI.ico"/>
		<Item Name="GUI_Menu.rtm" Type="Document" URL="../GUI_Menu.rtm"/>
		<Item Name="Map Visualization.vi" Type="VI" URL="../Map Visualization.vi"/>
		<Item Name="MapOwnWindow.vi" Type="VI" URL="../MapOwnWindow.vi"/>
		<Item Name="StringToMatrix.vi" Type="VI" URL="../../Library/Helping Routines/StringToMatrix.vi"/>
		<Item Name="TestVI.vi" Type="VI" URL="../TestVI.vi"/>
		<Item Name="Vessel Visualization.vi" Type="VI" URL="../Vessel Visualization.vi"/>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
				<Item Name="_2DArrToArrWfms.vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/_2DArrToArrWfms.vi"/>
				<Item Name="_ArrWfmsTo1DInterleave.vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/_ArrWfmsTo1DInterleave.vi"/>
				<Item Name="_ArrWfmsTo2DArr.vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/_ArrWfmsTo2DArr.vi"/>
				<Item Name="_ArrWfmsToData.vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/_ArrWfmsToData.vi"/>
				<Item Name="_FormatFromData (DBL).vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/_FormatFromData (DBL).vi"/>
				<Item Name="_FormatFromData (I16).vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/_FormatFromData (I16).vi"/>
				<Item Name="_FormatFromData (I32).vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/_FormatFromData (I32).vi"/>
				<Item Name="_FormatFromData (SGL).vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/_FormatFromData (SGL).vi"/>
				<Item Name="_FormatFromData (U8).vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/_FormatFromData (U8).vi"/>
				<Item Name="_FormatFromData.vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/_FormatFromData.vi"/>
				<Item Name="_Get Sound Error From Return Value.vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/_Get Sound Error From Return Value.vi"/>
				<Item Name="Acquire Input Data.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/inputDevices.llb/Acquire Input Data.vi"/>
				<Item Name="Attitude Indicator.xctl" Type="XControl" URL="/&lt;vilib&gt;/robotics/Controls/Attitude Indicator/Attitude Indicator.xctl"/>
				<Item Name="Bit-array To Byte-array.vi" Type="VI" URL="/&lt;vilib&gt;/picture/pictutil.llb/Bit-array To Byte-array.vi"/>
				<Item Name="BuildHelpPath.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/BuildHelpPath.vi"/>
				<Item Name="CenterRectInBnds.vi" Type="VI" URL="/&lt;vilib&gt;/picture/PictureSupport.llb/CenterRectInBnds.vi"/>
				<Item Name="Check if File or Folder Exists.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/libraryn.llb/Check if File or Folder Exists.vi"/>
				<Item Name="Check Path.vi" Type="VI" URL="/&lt;vilib&gt;/picture/jpeg.llb/Check Path.vi"/>
				<Item Name="Check Special Tags.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Check Special Tags.vi"/>
				<Item Name="Clear Errors.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Clear Errors.vi"/>
				<Item Name="Close Input Device.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/inputDevices.llb/Close Input Device.vi"/>
				<Item Name="closeJoystick.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/inputDevices.llb/closeJoystick.vi"/>
				<Item Name="closeKeyboard.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/inputDevices.llb/closeKeyboard.vi"/>
				<Item Name="closeMouse.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/inputDevices.llb/closeMouse.vi"/>
				<Item Name="Color to RGB.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/colorconv.llb/Color to RGB.vi"/>
				<Item Name="Compass Indicator.xctl" Type="XControl" URL="/&lt;vilib&gt;/robotics/Controls/Compass Indicator/Compass Indicator.xctl"/>
				<Item Name="Convert property node font to graphics font.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Convert property node font to graphics font.vi"/>
				<Item Name="Create Mask By Alpha.vi" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/Create Mask By Alpha.vi"/>
				<Item Name="Create Mask.vi" Type="VI" URL="/&lt;vilib&gt;/picture/pictutil.llb/Create Mask.vi"/>
				<Item Name="Details Display Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Details Display Dialog.vi"/>
				<Item Name="DialogType.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/DialogType.ctl"/>
				<Item Name="DialogTypeEnum.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/DialogTypeEnum.ctl"/>
				<Item Name="Directory of Top Level VI.vi" Type="VI" URL="/&lt;vilib&gt;/picture/jpeg.llb/Directory of Top Level VI.vi"/>
				<Item Name="Draw Arc.vi" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/Draw Arc.vi"/>
				<Item Name="Draw Circle by Radius.vi" Type="VI" URL="/&lt;vilib&gt;/picture/pictutil.llb/Draw Circle by Radius.vi"/>
				<Item Name="Draw Flattened Pixmap.vi" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/Draw Flattened Pixmap.vi"/>
				<Item Name="Draw Multiple Lines.vi" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/Draw Multiple Lines.vi"/>
				<Item Name="Draw Point.vi" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/Draw Point.vi"/>
				<Item Name="Draw Rect.vi" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/Draw Rect.vi"/>
				<Item Name="Draw Text at Point.vi" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/Draw Text at Point.vi"/>
				<Item Name="Draw Text in Rect.vi" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/Draw Text in Rect.vi"/>
				<Item Name="DWDT Error Code.vi" Type="VI" URL="/&lt;vilib&gt;/Waveform/DWDTOps.llb/DWDT Error Code.vi"/>
				<Item Name="Dynamic To Waveform Array.vi" Type="VI" URL="/&lt;vilib&gt;/express/express shared/transition.llb/Dynamic To Waveform Array.vi"/>
				<Item Name="Empty Picture" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/Empty Picture"/>
				<Item Name="Error Cluster From Error Code.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Error Cluster From Error Code.vi"/>
				<Item Name="Error Code Database.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Error Code Database.vi"/>
				<Item Name="ErrorDescriptions.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/inputDevices.llb/ErrorDescriptions.vi"/>
				<Item Name="errorList.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/inputDevices.llb/errorList.vi"/>
				<Item Name="ErrWarn.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/ErrWarn.ctl"/>
				<Item Name="eventvkey.ctl" Type="VI" URL="/&lt;vilib&gt;/event_ctls.llb/eventvkey.ctl"/>
				<Item Name="ex_BuildTextVarProps.ctl" Type="VI" URL="/&lt;vilib&gt;/express/express output/BuildTextBlock.llb/ex_BuildTextVarProps.ctl"/>
				<Item Name="ex_CorrectErrorChain.vi" Type="VI" URL="/&lt;vilib&gt;/express/express shared/ex_CorrectErrorChain.vi"/>
				<Item Name="Find Tag.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Find Tag.vi"/>
				<Item Name="FixBadRect.vi" Type="VI" URL="/&lt;vilib&gt;/picture/pictutil.llb/FixBadRect.vi"/>
				<Item Name="Format Message String.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Format Message String.vi"/>
				<Item Name="FormatTime String.vi" Type="VI" URL="/&lt;vilib&gt;/express/express execution control/ElapsedTimeBlock.llb/FormatTime String.vi"/>
				<Item Name="General Error Handler Core CORE.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/General Error Handler Core CORE.vi"/>
				<Item Name="General Error Handler.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/General Error Handler.vi"/>
				<Item Name="Get File Extension.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/libraryn.llb/Get File Extension.vi"/>
				<Item Name="Get String Text Bounds.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Get String Text Bounds.vi"/>
				<Item Name="Get Text Rect.vi" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/Get Text Rect.vi"/>
				<Item Name="GetHelpDir.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/GetHelpDir.vi"/>
				<Item Name="GetRTHostConnectedProp.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/GetRTHostConnectedProp.vi"/>
				<Item Name="Hilite Color.vi" Type="VI" URL="/&lt;vilib&gt;/picture/pictutil.llb/Hilite Color.vi"/>
				<Item Name="imagedata.ctl" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/imagedata.ctl"/>
				<Item Name="Initialize Joystick.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/inputDevices.llb/Initialize Joystick.vi"/>
				<Item Name="joystickAcquire.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/inputDevices.llb/joystickAcquire.vi"/>
				<Item Name="keyboardAcquire.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/inputDevices.llb/keyboardAcquire.vi"/>
				<Item Name="Longest Line Length in Pixels.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Longest Line Length in Pixels.vi"/>
				<Item Name="LVBoundsTypeDef.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/miscctls.llb/LVBoundsTypeDef.ctl"/>
				<Item Name="LVCursorListTypeDef.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/miscctls.llb/LVCursorListTypeDef.ctl"/>
				<Item Name="LVPositionTypeDef.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/miscctls.llb/LVPositionTypeDef.ctl"/>
				<Item Name="LVRectTypeDef.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/miscctls.llb/LVRectTypeDef.ctl"/>
				<Item Name="mouseAcquire.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/inputDevices.llb/mouseAcquire.vi"/>
				<Item Name="NI_3D Picture Control.lvlib" Type="Library" URL="/&lt;vilib&gt;/picture/3D Picture Control/NI_3D Picture Control.lvlib"/>
				<Item Name="NI_AAL_Angle.lvlib" Type="Library" URL="/&lt;vilib&gt;/Analysis/NI_AAL_Angle.lvlib"/>
				<Item Name="NI_AALBase.lvlib" Type="Library" URL="/&lt;vilib&gt;/Analysis/NI_AALBase.lvlib"/>
				<Item Name="NI_AALPro.lvlib" Type="Library" URL="/&lt;vilib&gt;/Analysis/NI_AALPro.lvlib"/>
				<Item Name="NI_AngleManipulation.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/AngleManip/NI_AngleManipulation.lvlib"/>
				<Item Name="NI_FileType.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/lvfile.llb/NI_FileType.lvlib"/>
				<Item Name="NI_Matrix.lvlib" Type="Library" URL="/&lt;vilib&gt;/Analysis/Matrix/NI_Matrix.lvlib"/>
				<Item Name="NI_PackedLibraryUtility.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/LVLibp/NI_PackedLibraryUtility.lvlib"/>
				<Item Name="NI_Robotics_Attitude Picture.lvlib" Type="Library" URL="/&lt;vilib&gt;/robotics/Controls/Attitude Indicator/Attitude Picture/NI_Robotics_Attitude Picture.lvlib"/>
				<Item Name="NI_Robotics_Compass Picture.lvlib" Type="Library" URL="/&lt;vilib&gt;/robotics/Controls/Compass Indicator/Compass Picture/NI_Robotics_Compass Picture.lvlib"/>
				<Item Name="NI_Robotics_Control Utilities.lvlib" Type="Library" URL="/&lt;vilib&gt;/robotics/Controls/Utilities/NI_Robotics_Control Utilities.lvlib"/>
				<Item Name="NI_XML.lvlib" Type="Library" URL="/&lt;vilib&gt;/xml/NI_XML.lvlib"/>
				<Item Name="Normalize Waveform.vi" Type="VI" URL="/&lt;vilib&gt;/Waveform/WDTOps.llb/Normalize Waveform.vi"/>
				<Item Name="Not Found Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Not Found Dialog.vi"/>
				<Item Name="Path To Command Line String.vi" Type="VI" URL="/&lt;vilib&gt;/AdvancedString/Path To Command Line String.vi"/>
				<Item Name="PathToUNIXPathString.vi" Type="VI" URL="/&lt;vilib&gt;/Platform/CFURL.llb/PathToUNIXPathString.vi"/>
				<Item Name="PCT Pad String.vi" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/PCT Pad String.vi"/>
				<Item Name="Picture to Pixmap.vi" Type="VI" URL="/&lt;vilib&gt;/picture/pictutil.llb/Picture to Pixmap.vi"/>
				<Item Name="POffsetRect.vi" Type="VI" URL="/&lt;vilib&gt;/picture/PictureSupport.llb/POffsetRect.vi"/>
				<Item Name="Point2Rect.vi" Type="VI" URL="/&lt;vilib&gt;/picture/PictureSupport.llb/Point2Rect.vi"/>
				<Item Name="Query Input Devices.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/inputDevices.llb/Query Input Devices.vi"/>
				<Item Name="Read JPEG File.vi" Type="VI" URL="/&lt;vilib&gt;/picture/jpeg.llb/Read JPEG File.vi"/>
				<Item Name="Read PNG File.vi" Type="VI" URL="/&lt;vilib&gt;/picture/png.llb/Read PNG File.vi"/>
				<Item Name="Real Matrix NI_Silver.ctl" Type="VI" URL="/&lt;vilib&gt;/silver_ctls/ArrayMatrixCluster/Real Matrix NI_Silver.ctl"/>
				<Item Name="RectCentroid.vi" Type="VI" URL="/&lt;vilib&gt;/picture/PictureSupport.llb/RectCentroid.vi"/>
				<Item Name="RGB to Color.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/colorconv.llb/RGB to Color.vi"/>
				<Item Name="Sampling Mode.ctl" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sampling Mode.ctl"/>
				<Item Name="Search and Replace Pattern.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Search and Replace Pattern.vi"/>
				<Item Name="Set Bold Text.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Set Bold Text.vi"/>
				<Item Name="Set Pen State.vi" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/Set Pen State.vi"/>
				<Item Name="Set String Value.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Set String Value.vi"/>
				<Item Name="Simple Error Handler.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Simple Error Handler.vi"/>
				<Item Name="Sound Data Format.ctl" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound Data Format.ctl"/>
				<Item Name="Sound File Close.vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound File Close.vi"/>
				<Item Name="Sound File Info (refnum).vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound File Info (refnum).vi"/>
				<Item Name="Sound File Position.ctl" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound File Position.ctl"/>
				<Item Name="Sound File Read (DBL).vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound File Read (DBL).vi"/>
				<Item Name="Sound File Read Open.vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound File Read Open.vi"/>
				<Item Name="Sound File Read Simple.vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound File Read Simple.vi"/>
				<Item Name="Sound File Refnum.ctl" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound File Refnum.ctl"/>
				<Item Name="Sound Output Clear.vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound Output Clear.vi"/>
				<Item Name="Sound Output Configure.vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound Output Configure.vi"/>
				<Item Name="Sound Output Start.vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound Output Start.vi"/>
				<Item Name="Sound Output Task ID.ctl" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound Output Task ID.ctl"/>
				<Item Name="Sound Output Wait.vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound Output Wait.vi"/>
				<Item Name="Sound Output Write (DBL Single).vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound Output Write (DBL Single).vi"/>
				<Item Name="Sound Output Write (DBL).vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound Output Write (DBL).vi"/>
				<Item Name="Sound Output Write (I16).vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound Output Write (I16).vi"/>
				<Item Name="Sound Output Write (I32).vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound Output Write (I32).vi"/>
				<Item Name="Sound Output Write (SGL).vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound Output Write (SGL).vi"/>
				<Item Name="Sound Output Write (U8).vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound Output Write (U8).vi"/>
				<Item Name="Sound Output Write Simple (DBL1).vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound Output Write Simple (DBL1).vi"/>
				<Item Name="Sound Output Write Simple (DBL2).vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound Output Write Simple (DBL2).vi"/>
				<Item Name="Sound Output Write Simple.vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound Output Write Simple.vi"/>
				<Item Name="Sound Output Write.vi" Type="VI" URL="/&lt;vilib&gt;/sound2/lvsound2.llb/Sound Output Write.vi"/>
				<Item Name="subDisplayMessage.vi" Type="VI" URL="/&lt;vilib&gt;/express/express output/DisplayMessageBlock.llb/subDisplayMessage.vi"/>
				<Item Name="subElapsedTime.vi" Type="VI" URL="/&lt;vilib&gt;/express/express execution control/ElapsedTimeBlock.llb/subElapsedTime.vi"/>
				<Item Name="subFile Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/express/express input/FileDialogBlock.llb/subFile Dialog.vi"/>
				<Item Name="subPlayWaveform.vi" Type="VI" URL="/&lt;vilib&gt;/sound2/PlayWaveformSource.llb/subPlayWaveform.vi"/>
				<Item Name="TagReturnType.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/TagReturnType.ctl"/>
				<Item Name="Three Button Dialog CORE.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Three Button Dialog CORE.vi"/>
				<Item Name="Three Button Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Three Button Dialog.vi"/>
				<Item Name="Trim Whitespace.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Trim Whitespace.vi"/>
				<Item Name="Unflatten Pixmap.vi" Type="VI" URL="/&lt;vilib&gt;/picture/pixmap.llb/Unflatten Pixmap.vi"/>
				<Item Name="Version To Dotted String.vi" Type="VI" URL="/&lt;vilib&gt;/_xctls/Version To Dotted String.vi"/>
				<Item Name="whitespace.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/whitespace.ctl"/>
				<Item Name="XControlSupport.lvlib" Type="Library" URL="/&lt;vilib&gt;/_xctls/XControlSupport.lvlib"/>
			</Item>
			<Item Name="DOMUserDefRef.dll" Type="Document" URL="DOMUserDefRef.dll">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
			<Item Name="JoystickManipulatorButtonHelp.vi" Type="VI" URL="../JoystickManipulatorButtonHelp.vi"/>
			<Item Name="LawnMower pattern INPUT dialog.vi" Type="VI" URL="../LawnMower pattern INPUT dialog.vi"/>
			<Item Name="lvanlys.dll" Type="Document" URL="/&lt;resource&gt;/lvanlys.dll"/>
			<Item Name="lvinput.dll" Type="Document" URL="/&lt;resource&gt;/lvinput.dll"/>
			<Item Name="lvsound2.dll" Type="Document" URL="/&lt;resource&gt;/lvsound2.dll"/>
			<Item Name="OOI In Dialog.vi" Type="VI" URL="../Objects Of Interest/OOI In Dialog.vi"/>
			<Item Name="Rad 2 PI-PI Scalar.vi" Type="VI" URL="../../Library/Helping Routines/Rad 2 PI-PI Scalar.vi"/>
			<Item Name="Rad 2 PI-PI Vector.vi" Type="VI" URL="../../Library/Helping Routines/Rad 2 PI-PI Vector.vi"/>
			<Item Name="Rad 2 PI-PI.vi" Type="VI" URL="../../Library/Helping Routines/Rad 2 PI-PI.vi"/>
			<Item Name="Read Node Name.vi" Type="VI" URL="../../Library/Helping Routines/Read Node Name.vi"/>
			<Item Name="Waypoints Generator.vi" Type="VI" URL="../Waypoints Generator.vi"/>
		</Item>
		<Item Name="Build Specifications" Type="Build">
			<Item Name="GUI" Type="EXE">
				<Property Name="App_copyErrors" Type="Bool">true</Property>
				<Property Name="App_INI_aliasGUID" Type="Str">{5C8016EC-73DF-4FC3-9C01-BB2F15AFED54}</Property>
				<Property Name="App_INI_GUID" Type="Str">{50FF56F5-A866-4C1A-9196-8D25467A3322}</Property>
				<Property Name="App_serverConfig.httpPort" Type="Int">8002</Property>
				<Property Name="Bld_buildCacheID" Type="Str">{A396933D-26A0-41AD-9C71-7EBBD9D4615A}</Property>
				<Property Name="Bld_buildSpecName" Type="Str">GUI</Property>
				<Property Name="Bld_excludeLibraryItems" Type="Bool">true</Property>
				<Property Name="Bld_excludePolymorphicVIs" Type="Bool">true</Property>
				<Property Name="Bld_localDestDir" Type="Path">../builds/NI_AB_PROJECTNAME/GUI</Property>
				<Property Name="Bld_localDestDirType" Type="Str">relativeToCommon</Property>
				<Property Name="Bld_modifyLibraryFile" Type="Bool">true</Property>
				<Property Name="Bld_previewCacheID" Type="Str">{4D86B952-C806-447F-BDD0-6C3BC83673B0}</Property>
				<Property Name="Bld_version.major" Type="Int">1</Property>
				<Property Name="Destination[0].destName" Type="Str">GUI.exe</Property>
				<Property Name="Destination[0].path" Type="Path">../builds/NI_AB_PROJECTNAME/GUI/GUI.exe</Property>
				<Property Name="Destination[0].preserveHierarchy" Type="Bool">true</Property>
				<Property Name="Destination[0].type" Type="Str">App</Property>
				<Property Name="Destination[1].destName" Type="Str">Support Directory</Property>
				<Property Name="Destination[1].path" Type="Path">../builds/NI_AB_PROJECTNAME/GUI/data</Property>
				<Property Name="DestinationCount" Type="Int">2</Property>
				<Property Name="Exe_iconItemID" Type="Ref">/My Computer/GUI.ico</Property>
				<Property Name="Source[0].itemID" Type="Str">{AF76C13E-C024-4B07-BF51-793E09D1C53C}</Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[1].itemID" Type="Ref">/My Computer/Graphical User Interface - Frigg.vi</Property>
				<Property Name="Source[1].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[1].type" Type="Str">VI</Property>
				<Property Name="Source[10].Container.applyInclusion" Type="Bool">true</Property>
				<Property Name="Source[10].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[10].itemID" Type="Ref">/My Computer/Pictures</Property>
				<Property Name="Source[10].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[10].type" Type="Str">Container</Property>
				<Property Name="Source[11].Container.applyInclusion" Type="Bool">true</Property>
				<Property Name="Source[11].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[11].itemID" Type="Ref">/My Computer/Tuning Pages</Property>
				<Property Name="Source[11].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[11].type" Type="Str">Container</Property>
				<Property Name="Source[12].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[12].itemID" Type="Ref">/My Computer/Empty Panel 2.vi</Property>
				<Property Name="Source[12].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[12].type" Type="Str">VI</Property>
				<Property Name="Source[13].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[13].itemID" Type="Ref">/My Computer/Empty Panel.vi</Property>
				<Property Name="Source[13].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[13].type" Type="Str">VI</Property>
				<Property Name="Source[14].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[14].itemID" Type="Ref">/My Computer/GUI.ico</Property>
				<Property Name="Source[14].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[15].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[15].itemID" Type="Ref">/My Computer/GUI_Menu.rtm</Property>
				<Property Name="Source[15].lvfile" Type="Bool">true</Property>
				<Property Name="Source[15].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[16].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[16].itemID" Type="Ref">/My Computer/Map Visualization.vi</Property>
				<Property Name="Source[16].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[16].type" Type="Str">VI</Property>
				<Property Name="Source[17].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[17].itemID" Type="Ref">/My Computer/MapOwnWindow.vi</Property>
				<Property Name="Source[17].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[17].type" Type="Str">VI</Property>
				<Property Name="Source[18].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[18].itemID" Type="Ref">/My Computer/TestVI.vi</Property>
				<Property Name="Source[18].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[18].type" Type="Str">VI</Property>
				<Property Name="Source[19].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[19].itemID" Type="Ref">/My Computer/Vessel Visualization.vi</Property>
				<Property Name="Source[19].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[19].type" Type="Str">VI</Property>
				<Property Name="Source[2].Container.applyInclusion" Type="Bool">true</Property>
				<Property Name="Source[2].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[2].itemID" Type="Ref">/My Computer/GraphView</Property>
				<Property Name="Source[2].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[2].type" Type="Str">Container</Property>
				<Property Name="Source[3].Container.applyInclusion" Type="Bool">true</Property>
				<Property Name="Source[3].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[3].itemID" Type="Ref">/My Computer/Control Panel</Property>
				<Property Name="Source[3].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[3].type" Type="Str">Container</Property>
				<Property Name="Source[4].Container.applyInclusion" Type="Bool">true</Property>
				<Property Name="Source[4].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[4].itemID" Type="Ref">/My Computer/Controllers</Property>
				<Property Name="Source[4].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[4].type" Type="Str">Container</Property>
				<Property Name="Source[5].Container.applyInclusion" Type="Bool">true</Property>
				<Property Name="Source[5].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[5].itemID" Type="Ref">/My Computer/Dialog Boxes</Property>
				<Property Name="Source[5].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[5].type" Type="Str">Container</Property>
				<Property Name="Source[6].Container.applyInclusion" Type="Bool">true</Property>
				<Property Name="Source[6].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[6].itemID" Type="Ref">/My Computer/Functions</Property>
				<Property Name="Source[6].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[6].type" Type="Str">Container</Property>
				<Property Name="Source[7].Container.applyInclusion" Type="Bool">true</Property>
				<Property Name="Source[7].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[7].itemID" Type="Ref">/My Computer/HelpSites</Property>
				<Property Name="Source[7].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[7].type" Type="Str">Container</Property>
				<Property Name="Source[8].Container.applyInclusion" Type="Bool">true</Property>
				<Property Name="Source[8].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[8].itemID" Type="Ref">/My Computer/Mission Control</Property>
				<Property Name="Source[8].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[8].type" Type="Str">Container</Property>
				<Property Name="Source[9].Container.applyInclusion" Type="Bool">true</Property>
				<Property Name="Source[9].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[9].itemID" Type="Ref">/My Computer/Options</Property>
				<Property Name="Source[9].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[9].type" Type="Str">Container</Property>
				<Property Name="SourceCount" Type="Int">20</Property>
				<Property Name="TgtF_fileDescription" Type="Str">GUI</Property>
				<Property Name="TgtF_internalName" Type="Str">GUI</Property>
				<Property Name="TgtF_legalCopyright" Type="Str">Copyright © 2012 </Property>
				<Property Name="TgtF_productName" Type="Str">GUI</Property>
				<Property Name="TgtF_targetfileGUID" Type="Str">{541D4195-DDEC-401F-B609-903656D06108}</Property>
				<Property Name="TgtF_targetfileName" Type="Str">GUI.exe</Property>
			</Item>
			<Item Name="GUI5" Type="EXE">
				<Property Name="App_copyErrors" Type="Bool">true</Property>
				<Property Name="App_INI_aliasGUID" Type="Str">{37679232-E286-456A-B240-594BAC0BD294}</Property>
				<Property Name="App_INI_GUID" Type="Str">{4684C7BA-97AF-4B70-8DF3-FB9F86CDEA16}</Property>
				<Property Name="App_serverConfig.httpPort" Type="Int">8002</Property>
				<Property Name="Bld_buildCacheID" Type="Str">{E0CCE9DF-DA69-4A80-AFC3-714E5AB1F77A}</Property>
				<Property Name="Bld_buildSpecName" Type="Str">GUI5</Property>
				<Property Name="Bld_excludeLibraryItems" Type="Bool">true</Property>
				<Property Name="Bld_excludePolymorphicVIs" Type="Bool">true</Property>
				<Property Name="Bld_localDestDir" Type="Path">../builds/NI_AB_PROJECTNAME/GUI5</Property>
				<Property Name="Bld_localDestDirType" Type="Str">relativeToCommon</Property>
				<Property Name="Bld_modifyLibraryFile" Type="Bool">true</Property>
				<Property Name="Bld_previewCacheID" Type="Str">{6183326D-9EFC-4ADC-9F5B-48F1DF29C2E6}</Property>
				<Property Name="Bld_version.major" Type="Int">1</Property>
				<Property Name="Destination[0].destName" Type="Str">Application.exe</Property>
				<Property Name="Destination[0].path" Type="Path">../builds/NI_AB_PROJECTNAME/GUI5/Application.exe</Property>
				<Property Name="Destination[0].preserveHierarchy" Type="Bool">true</Property>
				<Property Name="Destination[0].type" Type="Str">App</Property>
				<Property Name="Destination[1].destName" Type="Str">Support Directory</Property>
				<Property Name="Destination[1].path" Type="Path">../builds/NI_AB_PROJECTNAME/GUI5/data</Property>
				<Property Name="DestinationCount" Type="Int">2</Property>
				<Property Name="Source[0].itemID" Type="Str">{8CFD6288-81E7-400E-992A-D50A3DFAEE1F}</Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[1].itemID" Type="Ref">/My Computer/Graphical User Interface - Frigg.vi</Property>
				<Property Name="Source[1].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[1].type" Type="Str">VI</Property>
				<Property Name="SourceCount" Type="Int">2</Property>
				<Property Name="TgtF_fileDescription" Type="Str">GUI5</Property>
				<Property Name="TgtF_internalName" Type="Str">GUI5</Property>
				<Property Name="TgtF_legalCopyright" Type="Str">Copyright © 2012 </Property>
				<Property Name="TgtF_productName" Type="Str">GUI5</Property>
				<Property Name="TgtF_targetfileGUID" Type="Str">{DE0D2944-3ADF-4F1B-BE86-B4E1508EA7E5}</Property>
				<Property Name="TgtF_targetfileName" Type="Str">Application.exe</Property>
			</Item>
			<Item Name="User Guide5" Type="EXE">
				<Property Name="App_copyErrors" Type="Bool">true</Property>
				<Property Name="App_INI_aliasGUID" Type="Str">{9D2DB6D8-8C73-486D-9332-F07B63BDC70E}</Property>
				<Property Name="App_INI_GUID" Type="Str">{2503D400-797A-46FA-9347-F8E5C8179DFD}</Property>
				<Property Name="App_serverConfig.httpPort" Type="Int">8002</Property>
				<Property Name="Bld_buildCacheID" Type="Str">{2BCDF1B4-EE24-457E-962F-B875C7A9C5B0}</Property>
				<Property Name="Bld_buildSpecName" Type="Str">User Guide5</Property>
				<Property Name="Bld_excludeLibraryItems" Type="Bool">true</Property>
				<Property Name="Bld_excludePolymorphicVIs" Type="Bool">true</Property>
				<Property Name="Bld_localDestDir" Type="Path">/D/Espen Tolpinrud/My Documents/LabView/builds/User Guide 5</Property>
				<Property Name="Bld_modifyLibraryFile" Type="Bool">true</Property>
				<Property Name="Bld_previewCacheID" Type="Str">{A5FE5BFB-F278-4553-A767-F1EF9F82799A}</Property>
				<Property Name="Bld_version.major" Type="Int">1</Property>
				<Property Name="Destination[0].destName" Type="Str">Application.exe</Property>
				<Property Name="Destination[0].path" Type="Path">/D/Espen Tolpinrud/My Documents/LabView/builds/User Guide 5/Application.exe</Property>
				<Property Name="Destination[0].path.type" Type="Str">&lt;none&gt;</Property>
				<Property Name="Destination[0].preserveHierarchy" Type="Bool">true</Property>
				<Property Name="Destination[0].type" Type="Str">App</Property>
				<Property Name="Destination[1].destName" Type="Str">Support Directory</Property>
				<Property Name="Destination[1].path" Type="Path">/D/Espen Tolpinrud/My Documents/LabView/builds/User Guide 5/data</Property>
				<Property Name="Destination[1].path.type" Type="Str">&lt;none&gt;</Property>
				<Property Name="DestinationCount" Type="Int">2</Property>
				<Property Name="Source[0].itemID" Type="Str">{98B57908-1717-4C0A-99E4-254493289828}</Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[1].itemID" Type="Ref">/My Computer/HelpSites/Help Center.vi</Property>
				<Property Name="Source[1].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[1].type" Type="Str">VI</Property>
				<Property Name="Source[10].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[10].itemID" Type="Ref">/My Computer/HelpSites/JoystickHelp.vi</Property>
				<Property Name="Source[10].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[10].type" Type="Str">VI</Property>
				<Property Name="Source[11].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[11].itemID" Type="Ref">/My Computer/HelpSites/LightPanelHelp.vi</Property>
				<Property Name="Source[11].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[11].type" Type="Str">VI</Property>
				<Property Name="Source[12].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[12].itemID" Type="Ref">/My Computer/HelpSites/ManipulatorPanelHelp.vi</Property>
				<Property Name="Source[12].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[12].type" Type="Str">VI</Property>
				<Property Name="Source[13].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[13].itemID" Type="Ref">/My Computer/HelpSites/MapVHelp.vi</Property>
				<Property Name="Source[13].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[13].type" Type="Str">VI</Property>
				<Property Name="Source[14].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[14].itemID" Type="Ref">/My Computer/HelpSites/TrackingButtonsHelp.vi</Property>
				<Property Name="Source[14].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[14].type" Type="Str">VI</Property>
				<Property Name="Source[15].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[15].itemID" Type="Ref">/My Computer/HelpSites/TrackingHelp.vi</Property>
				<Property Name="Source[15].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[15].type" Type="Str">VI</Property>
				<Property Name="Source[16].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[16].itemID" Type="Ref">/My Computer/HelpSites/TrackingLawnMowerHelp.vi</Property>
				<Property Name="Source[16].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[16].type" Type="Str">VI</Property>
				<Property Name="Source[17].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[17].itemID" Type="Ref">/My Computer/HelpSites/UserGuideMenu.rtm</Property>
				<Property Name="Source[17].lvfile" Type="Bool">true</Property>
				<Property Name="Source[17].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[18].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[18].itemID" Type="Ref">/My Computer/HelpSites/VesselDHelp.vi</Property>
				<Property Name="Source[18].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[18].type" Type="Str">VI</Property>
				<Property Name="Source[19].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[19].itemID" Type="Ref">/My Computer/Pictures/main.png</Property>
				<Property Name="Source[19].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[2].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[2].itemID" Type="Ref">/My Computer/HelpSites/CameraControlHelp.vi</Property>
				<Property Name="Source[2].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[2].type" Type="Str">VI</Property>
				<Property Name="Source[3].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[3].itemID" Type="Ref">/My Computer/HelpSites/ControlPanelHelp.vi</Property>
				<Property Name="Source[3].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[3].type" Type="Str">VI</Property>
				<Property Name="Source[4].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[4].itemID" Type="Ref">/My Computer/HelpSites/DPButtonsHelp.vi</Property>
				<Property Name="Source[4].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[4].type" Type="Str">VI</Property>
				<Property Name="Source[5].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[5].itemID" Type="Ref">/My Computer/HelpSites/DPHelp.vi</Property>
				<Property Name="Source[5].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[5].type" Type="Str">VI</Property>
				<Property Name="Source[6].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[6].itemID" Type="Ref">/My Computer/HelpSites/DPModesHelp.vi</Property>
				<Property Name="Source[6].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[6].type" Type="Str">VI</Property>
				<Property Name="Source[7].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[7].itemID" Type="Ref">/My Computer/HelpSites/Empty Panel 3.vi</Property>
				<Property Name="Source[7].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[7].type" Type="Str">VI</Property>
				<Property Name="Source[8].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[8].itemID" Type="Ref">/My Computer/HelpSites/General.vi</Property>
				<Property Name="Source[8].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[8].type" Type="Str">VI</Property>
				<Property Name="Source[9].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[9].itemID" Type="Ref">/My Computer/HelpSites/JoystickButtonHelp.vi</Property>
				<Property Name="Source[9].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[9].type" Type="Str">VI</Property>
				<Property Name="SourceCount" Type="Int">20</Property>
				<Property Name="TgtF_fileDescription" Type="Str">User Guide5</Property>
				<Property Name="TgtF_internalName" Type="Str">User Guide5</Property>
				<Property Name="TgtF_legalCopyright" Type="Str">Copyright © 2012 </Property>
				<Property Name="TgtF_productName" Type="Str">User Guide5</Property>
				<Property Name="TgtF_targetfileGUID" Type="Str">{061F4D21-068F-4193-A1E3-F37A94587F66}</Property>
				<Property Name="TgtF_targetfileName" Type="Str">Application.exe</Property>
			</Item>
		</Item>
	</Item>
</Project>
