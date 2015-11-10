# ------------------- Required for MSVC nmake ---------------------------------
# This file should be included at the top of a MAKEFILE as follows:


CPU = AMD64
!include <ntwin32.mak>

MACHINE     = Model_justmodel
TARGET      = sfun
CHART_SRCS 	= c1_Model_justmodel.c c2_Model_justmodel.c c3_Model_justmodel.c c4_Model_justmodel.c c5_Model_justmodel.c c6_Model_justmodel.c c7_Model_justmodel.c c8_Model_justmodel.c c9_Model_justmodel.c c10_Model_justmodel.c c11_Model_justmodel.c c12_Model_justmodel.c c13_Model_justmodel.c c14_Model_justmodel.c c15_Model_justmodel.c c25_Model_justmodel.c c26_Model_justmodel.c c27_Model_justmodel.c c28_Model_justmodel.c
MACHINE_SRC	= Model_justmodel_sfun.c
MACHINE_REG = Model_justmodel_sfun_registry.c
MAKEFILE    = Model_justmodel_sfun.mak
MATLAB_ROOT	= C:\Program Files\MATLAB\R2013a
BUILDARGS   =

#--------------------------- Tool Specifications ------------------------------
#
#
MSVC_ROOT1 = $(MSDEVDIR:SharedIDE=vc)
MSVC_ROOT2 = $(MSVC_ROOT1:SHAREDIDE=vc)
MSVC_ROOT  = $(MSVC_ROOT2:sharedide=vc)

# Compiler tool locations, CC, LD, LIBCMD:
CC     = cl.exe
LD     = link.exe
LIBCMD = lib.exe
#------------------------------ Include/Lib Path ------------------------------

USER_INCLUDES   = 
AUX_INCLUDES   = 
ML_INCLUDES     = /I "C:\Program Files\MATLAB\R2013a\extern\include"
SL_INCLUDES     = /I "C:\Program Files\MATLAB\R2013a\simulink\include"
SF_INCLUDES     = /I "C:\Program Files\MATLAB\R2013a\stateflow\c\mex\include" /I "C:\Program Files\MATLAB\R2013a\stateflow\c\debugger\include"

COMPILER_INCLUDES = /I "$(MSVC_ROOT)\include"

THIRD_PARTY_INCLUDES   = 
INCLUDE_PATH = $(USER_INCLUDES) $(AUX_INCLUDES) $(ML_INCLUDES)\
 $(SL_INCLUDES) $(SF_INCLUDES) $(THIRD_PARTY_INCLUDES)
LIB_PATH     = "$(MSVC_ROOT)\lib"

CFLAGS = /c /Zp8 /GR /W3 /EHs /D_CRT_SECURE_NO_DEPRECATE /D_SCL_SECURE_NO_DEPRECATE /D_SECURE_SCL=0 /DMATLAB_MEX_FILE /nologo /MD 
LDFLAGS = /nologo /MANIFEST /dll /OPT:NOREF /export:mexFunction  
#----------------------------- Source Files -----------------------------------

REQ_SRCS  =  $(MACHINE_SRC) $(MACHINE_REG) $(CHART_SRCS)

USER_ABS_OBJS =

AUX_ABS_OBJS =

REQ_OBJS = $(REQ_SRCS:.cpp=.obj)
REQ_OBJS2 = $(REQ_OBJS:.c=.obj)
OBJS = $(REQ_OBJS2) $(USER_ABS_OBJS) $(AUX_ABS_OBJS)
OBJLIST_FILE = Model_justmodel_sfun.mol
SFCLIB = "C:\Program Files\MATLAB\R2013a\stateflow\c\mex\lib\win64\sfc_mex.lib" "C:\Program Files\MATLAB\R2013a\stateflow\c\debugger\lib\win64\sfc_debug.lib" 
AUX_LNK_OBJS =     
USER_LIBS = 
LINK_MACHINE_LIBS = 
BLAS_LIBS = "C:\Program Files\MATLAB\R2013a\extern\lib\win64\microsoft\libmwblas.lib" 
THIRD_PARTY_LIBS = 

#--------------------------------- Rules --------------------------------------

MEX_FILE_NAME_WO_EXT = $(MACHINE)_$(TARGET)
MEX_FILE_NAME = $(MEX_FILE_NAME_WO_EXT).mexw64
MEX_FILE_CSF =
all : $(MEX_FILE_NAME) $(MEX_FILE_CSF)

TMWLIB = "C:\Program Files\MATLAB\R2013a\extern\lib\win64\microsoft\libmx.lib" "C:\Program Files\MATLAB\R2013a\extern\lib\win64\microsoft\libmex.lib" "C:\Program Files\MATLAB\R2013a\extern\lib\win64\microsoft\libmat.lib" "C:\Program Files\MATLAB\R2013a\extern\lib\win64\microsoft\libfixedpoint.lib" "C:\Program Files\MATLAB\R2013a\extern\lib\win64\microsoft\libut.lib" "C:\Program Files\MATLAB\R2013a\extern\lib\win64\microsoft\libmwmathutil.lib" "C:\Program Files\MATLAB\R2013a\extern\lib\win64\microsoft\libemlrt.lib" "C:\Program Files\MATLAB\R2013a\lib\win64\libippmwipt.lib" 

$(MEX_FILE_NAME) : $(MAKEFILE) $(OBJS) $(SFCLIB) $(AUX_LNK_OBJS) $(USER_LIBS) $(THIRD_PARTY_LIBS)
 @echo ### Linking ...
 $(LD) $(LDFLAGS) /OUT:$(MEX_FILE_NAME) /map:"$(MEX_FILE_NAME_WO_EXT).map"\
  $(USER_LIBS) $(SFCLIB) $(AUX_LNK_OBJS)\
  $(TMWLIB) $(LINK_MACHINE_LIBS) $(DSP_LIBS) $(BLAS_LIBS) $(THIRD_PARTY_LIBS)\
  @$(OBJLIST_FILE)
     mt -outputresource:"$(MEX_FILE_NAME);2" -manifest "$(MEX_FILE_NAME).manifest"
	@echo ### Created $@

.c.obj :
	@echo ### Compiling "$<"
	$(CC) $(CFLAGS) $(INCLUDE_PATH) "$<"

.cpp.obj :
	@echo ### Compiling "$<"
	$(CC) $(CFLAGS) $(INCLUDE_PATH) "$<"

