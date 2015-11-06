# Portions Copyright 1994-2001 The MathWorks, Inc.
#
# File    : Template_test.mk (for Release 2007b and later)
#
# Abstract:
#       Real-Time Workshop template makefile for building a real-time
#       version of a Simulink model to run on National Instruments
#       RT Series hardware. This template makefile uses generated C code
#       and supports the Microsoft Visual C/C++ compiler.
#
#       Note that this template is automatically customized by the Real-Time
#       Workshop build procedure to create "<model>.mk"
#
#       The following defines can be used to modify the behavior of the
#       build:
#
#    	  OPT_OPTS       - Optimization option. Default is -O2. To enable
#    			   debugging specify as OPT_OPTS=-Zd.
#    	  OPTS           - User specific options.
#    	  USER_SRCS      - Additional user source code files, such as files needed by
#    			   S-functions. For example:
#                          USER_SRCS = "c:\projects\MyCode.c".
#    	  USER_INCLUDES  - Additional include paths, such as:
#                          USER_INCLUDES = "-Isomepath"
#                          or
#                          USER_INCLUDES = "-Isomepath -Ianotherpath"
#
#       This template makefile is designed to be used with a system target
#       file that contains 'rtwgensettings.BuildDirSuffix' see grt.tlc


#------------------------ Macros read by make_rtw -----------------------------
#
# The following macros are read by the Real-Time Workshop build procedure:
#
#  MAKECMD         - This is the command used to invoke the make utility
#  HOST            - What platform this template makefile is targeted for 
#                    (i.e. PC or UNIX)
#  BUILD           - Invoke make from the Real-Time Workshop build procedure 
#                    (yes/no)?
#  SYS_TARGET_FILE - Name of system target file.

#
# 	Adapted from grt_vc.tmf
#

USER_INCLUDES = 
USER_SRCS = 

MAKECMD         = nmake
HOST            = PC
BUILD           = yes
SYS_TARGET_FILE = nidll.tlc
BUILD_SUCCESS	= *** Created
CPU             = i386

MODEL           = Template_test
MODULES         = Template_test_data.c is_little_endian_rt.c rtGetInf.c rtGetNaN.c rt_atan2_snf.c rt_backsubrr_dbl.c rt_forwardsubrr_dbl.c rt_logging.c rt_look.c rt_look2d_normal.c rt_lu_real.c rt_matdivrr_dbl.c rt_nonfinite.c rt_pow_snf.c rt_rem_snf.c rt_round_snf.c rt_zcfcn.c svd_d_rt.c svd_helper_rt.c 
MAKEFILE        = Template_test.mk
MATLAB_ROOT     = C:\Program Files\MATLAB\R2009a
ALT_MATLAB_ROOT = C:\PROGRA~1\MATLAB\R2009a
MATLAB_BIN      = C:\Program Files\MATLAB\R2009a\bin
ALT_MATLAB_BIN  = C:\PROGRA~1\MATLAB\R2009a\bin
S_FUNCTIONS     = 
S_FUNCTIONS_LIB = 
SOLVER          = ode5.c
NUMST           = 2
TID01EQ         = 1
NCSTATES        = 17
BUILDARGS       =  GENERATE_REPORT=0
MULTITASKING    = 0
VISUAL_VER		= 8.0
EXT_MODE        = 0
MATLAB_VERSION	= R2009a
STR_MATLAB_VERSION = "$(MATLAB_VERSION)"
NODEBUG         = 1
SIT_VERSION		= 2010
SIT_LIB_DIR     = $(SIT_ROOT)\$(SIT_VERSION)\ModelInterface\tmw\lib\VC$(VISUAL_VER)\$(MATLAB_VERSION)

MODELREFS            = 
SHARED_SRC           = 
SHARED_SRC_DIR       = 
SHARED_BIN_DIR       = 
SHARED_LIB           = 

#--------------------------- Model and reference models -----------------------
MODELLIB                  = Template_testlib.lib
MODELREF_LINK_LIBS        = 
MODELREF_INC_PATH         = 
RELATIVE_PATH_TO_ANCHOR   = ..
# ..\..\..\..\..\..\.. or .. or even . if you want it
MODELREF_TARGET_TYPE      = NONE

!if ($(STR_MATLAB_VERSION) != "14.0") && ("$(MATLAB_ROOT)" != "$(ALT_MATLAB_ROOT)")
MATLAB_ROOT = $(ALT_MATLAB_ROOT)
!endif
!if ($(STR_MATLAB_VERSION) != "14.0") && ("$(MATLAB_BIN)" != "$(ALT_MATLAB_BIN)")
MATLAB_BIN = $(ALT_MATLAB_BIN)
!endif

#--------------------------- Tool Specifications ------------------------------
!include $(MATLAB_ROOT)\rtw\c\tools\vctools.mak

PERL = $(MATLAB_ROOT)\sys\perl\win32\bin\perl
#------------------------------ Include/Lib Path ------------------------------

MATLAB_INCLUDES =                    $(MATLAB_ROOT)\simulink\include
MATLAB_INCLUDES = $(MATLAB_INCLUDES);$(MATLAB_ROOT)\extern\include
MATLAB_INCLUDES = $(MATLAB_INCLUDES);$(MATLAB_ROOT)\rtw\c\src
MATLAB_INCLUDES = $(MATLAB_INCLUDES);$(MATLAB_ROOT)\rtw\c\src\ext_mode\common
# Additional file include paths


MATLAB_INCLUDES = $(MATLAB_INCLUDES);C:\DOCUME~1\mcl\Desktop\CSENTE~1\HMIs\models\simulink\Template_test_nidll_rtw
MATLAB_INCLUDES = $(MATLAB_INCLUDES);C:\DOCUME~1\mcl\Desktop\CSENTE~1\HMIs\models\simulink
MATLAB_INCLUDES = $(MATLAB_INCLUDES);$(MATLAB_ROOT)\toolbox\dspblks\include

INCLUDE = .;$(RELATIVE_PATH_TO_ANCHOR);$(MATLAB_INCLUDES);$(INCLUDE);$(MODELREF_INC_PATH);$(SIT_ROOT)\$(SIT_VERSION)\ModelInterface\

!if "$(SHARED_SRC_DIR)" != ""
INCLUDE = $(INCLUDE);$(SHARED_SRC_DIR)
!endif

RTM_CC_OPTS = -DUSE_RTMODEL
LOG_SRC=
NIDLL_SRC=nidll_main.c

#----------------- Compiler and Linker Options --------------------------------


# Optimization Options
#   Set  OPT_OPTS=-Zd  for debugging
OPT_OPTS = $(DEFAULT_OPT_OPTS)

# General User Options

CRTLIBS = msvcrt.lib

USE_REBUILT_RTW_LIB_FILES = 1

# Other User Options
CC_OPTS = $(OPT_OPTS) $(OPTS) $(RTM_CC_OPTS)

!if "$(MODELREF_TARGET_TYPE)" == "NONE"
CC_OPTS = $(CC_OPTS) -DNI_ROOTMODEL_$(MODEL)
!endif

CPP_REQ_DEFINES = -DMODEL=$(MODEL) -DRT -DNUMST=$(NUMST) \
		  -DTID01EQ=$(TID01EQ) -DNCSTATES=$(NCSTATES) \
		  -DMT=$(MULTITASKING) -DHAVESTDIO -DNATIONAL_INSTRUMENTS_SIT \
		  -D_CRT_SECURE_NO_DEPRECATE

CFLAGS = $(CC_OPTS) $(CPP_REQ_DEFINES) $(USER_INCLUDES) \
	 $(cflags)

CPPFLAGS = $(CPP_OPTS) $(CC_OPTS) $(CPP_REQ_DEFINES) $(USER_INCLUDES) \
	 $(cflags) /GX

LDFLAGS  = $(ldebug) $(dlllflags) 

!if "$(VISUAL_VER)" == "9.0" || "$(VISUAL_VER)" == "7.1" || "$(VISUAL_VER)" == "6.0"
CFLAGS = $(CFLAGS) $(cvarsdll)
CPPFLAGS = $(CPPFLAGS) $(cvarsdll)
LDFLAGS = $(LDFLAGS) $(CRTLIBS) $(conlibsdll)
!else
CFLAGS = $(CFLAGS) /MT
CPPFLAGS = $(CPPFLAGS) /MT
LDFLAGS = $(LDFLAGS) /NODEFAULTLIB:MSVCRT LIBCMT.LIB $(conlibsdll)
!endif

# libcp.lib is the single-threaded, static lib version of the C++ standard lib
# /GX enables exception handling (needed to use C++ standard lib)

#----------------------------- Source Files -----------------------------------

#DLL
!if "$(MODELREF_TARGET_TYPE)" == "NONE"
PRODUCT   = $(MODEL).dll

REQ_SRCS  = $(MODEL).c $(MODULES) $(NIDLL_SRC) rt_sim.c \
	    $(SOLVER) $(LOG_SRC) $(MODEL).rc

#Model Reference Target
!else
PRODUCT   = $(MODELLIB)
REQ_SRCS  = $(MODULES)
!endif

SRCS = $(REQ_SRCS) $(USER_SRCS) $(S_FUNCTIONS)
OBJS_CPP_UPPER = $(SRCS:.CPP=.obj)
OBJS_CPP_LOWER = $(OBJS_CPP_UPPER:.cpp=.obj)
OBJS_C_UPPER = $(OBJS_CPP_LOWER:.C=.obj)
OBJS_C_LOWER = $(OBJS_C_UPPER:.c=.obj)
OBJS = $(OBJS_C_LOWER:.rc=.res)
SHARED_OBJS = $(SHARED_SRC:.c=.obj)

# ------------------------- Additional Libraries ------------------------------

LIBS =


LIBS = $(LIBS)

CMD_FILE = $(MODEL).lnk
GEN_LNK_SCRIPT = $(MATLAB_ROOT)\rtw\c\tools\mkvc_lnk.pl


#--------------------------------- Rules --------------------------------------

!if "$(MODELREF_TARGET_TYPE)" == "NONE"
#--- Stand-alone model ---
$(PRODUCT) : set_environment_variables create_nidll_code create_lib_dir $(OBJS) $(SHARED_LIB) $(LIBS) $(MODELREF_LINK_LIBS)
	@echo ### Linking ...
	$(PERL) $(GEN_LNK_SCRIPT) $(CMD_FILE) $(OBJS) $(MODELREF_LINK_LIBS)
	$(LD) $(LDFLAGS) $(LIBS) $(SHARED_LIB) $(S_FUNCTIONS_LIB) $(MAT_LIBS) @$(CMD_FILE) /dll -out:$@
!if "$(VISUAL_VER)" == "9.0"
	@if exist $@.manifest mt.exe -manifest $@.manifest -outputresource:$@;2
	@- del $@.manifest
!endif
	@del $(CMD_FILE)
	@echo $(BUILD_SUCCESS) DLL %cd%\$@
!else
#--- Model reference RTW Target ---
$(PRODUCT) : set_environment_variables create_lib_dir $(OBJS) $(LIBS)
	@echo ### Linking ...
	$(PERL) $(GEN_LNK_SCRIPT) $(CMD_FILE) $(OBJS)
	$(LD) -lib /OUT:$(MODELLIB) @$(CMD_FILE) $(S_FUNCTIONS_LIB)
	@del $(CMD_FILE)
	@echo $(BUILD_SUCCESS) static library $(MODELLIB)
!endif

# Copy files.
create_nidll_code :
	@echo copy $(SIT_ROOT)\$(SIT_VERSION)\ModelInterface\tmw\$(NIDLL_SRC) .\$(NIDLL_SRC)
	copy $(SIT_ROOT)\$(SIT_VERSION)\ModelInterface\tmw\$(NIDLL_SRC) .\$(NIDLL_SRC)
	copy $(SIT_ROOT)\$(SIT_VERSION)\ModelInterface\tmw\model_info.h .

# Create the lib folder if it does not exist.
create_lib_dir :
	@IF NOT EXIST $(SIT_LIB_DIR) (echo mkdir $(SIT_LIB_DIR) )
	@IF NOT EXIST $(SIT_LIB_DIR) (mkdir $(SIT_LIB_DIR) )

{$(MATLAB_ROOT)\rtw\c\src}.c.obj :
	@echo ### Compiling $<
	$(CC) $(CFLAGS) $<

# Additional sources

{$(MATLAB_ROOT)\toolbox\rtw\dspblks\c\dspsvd}.c.obj :
	@echo ### Compiling $<
	$(CC) $(CFLAGS) $<

{$(MATLAB_ROOT)\toolbox\rtw\dspblks\c\dspendian}.c.obj :
	@echo ### Compiling $<
	$(CC) $(CFLAGS) $<

{$(MATLAB_ROOT)\rtw\c\src}.c.obj :
	@echo ### Compiling $<
	$(CC) $(CFLAGS) $<



{$(MATLAB_ROOT)\toolbox\rtw\dspblks\c\dspsvd}.cpp.obj :
	@echo ### Compiling $<
	$(CC) $(CPPFLAGS) $<

{$(MATLAB_ROOT)\toolbox\rtw\dspblks\c\dspendian}.cpp.obj :
	@echo ### Compiling $<
	$(CC) $(CPPFLAGS) $<

{$(MATLAB_ROOT)\rtw\c\src}.cpp.obj :
	@echo ### Compiling $<
	$(CC) $(CPPFLAGS) $<




{$(MATLAB_ROOT)\toolbox\rtw\dspblks\c\dspsvd}.c{$(SIT_LIB_DIR)}.obj :
	@echo ### Compiling $<
	$(CC) $(CFLAGS) $< /Fo$@

{$(MATLAB_ROOT)\toolbox\rtw\dspblks\c\dspendian}.c{$(SIT_LIB_DIR)}.obj :
	@echo ### Compiling $<
	$(CC) $(CFLAGS) $< /Fo$@

{$(MATLAB_ROOT)\rtw\c\src}.c{$(SIT_LIB_DIR)}.obj :
	@echo ### Compiling $<
	$(CC) $(CFLAGS) $< /Fo$@



{$(MATLAB_ROOT)\toolbox\rtw\dspblks\c\dspsvd}.cpp{$(SIT_LIB_DIR)}.obj :
	@echo ### Compiling $<
	$(CC) $(CPPFLAGS) $< /Fo$@

{$(MATLAB_ROOT)\toolbox\rtw\dspblks\c\dspendian}.cpp{$(SIT_LIB_DIR)}.obj :
	@echo ### Compiling $<
	$(CC) $(CPPFLAGS) $< /Fo$@

{$(MATLAB_ROOT)\rtw\c\src}.cpp{$(SIT_LIB_DIR)}.obj :
	@echo ### Compiling $<
	$(CC) $(CPPFLAGS) $< /Fo$@



# Look in simulink/src helper files

{$(MATLAB_ROOT)\simulink\src}.c.obj :
	@echo ### Compiling $<
	$(CC) $(CFLAGS) $<

{$(MATLAB_ROOT)\simulink\src}.cpp.obj :
	@echo ### Compiling $<
	$(CC) $(CPPFLAGS) $<

# Put these rule last, otherwise nmake will check toolboxes first

{$(RELATIVE_PATH_TO_ANCHOR)}.c.obj :
	@echo ### Compiling $<
	$(CC) $(CFLAGS) $<

{$(RELATIVE_PATH_TO_ANCHOR)}.cpp.obj :
	@echo ### Compiling $<
	$(CC) $(CPPFLAGS) $<

.cpp.obj :
	@echo ### Compiling $<
	$(CC) $(CPPFLAGS) $<

$(MODEL).obj :
	@echo ### Compiling the source $(MODEL)
	$(CC) $(CFLAGS) -DRVE $(MODEL).c

.c.obj :
	@echo ### Compiling $<
	$(CC) $(CFLAGS) $<
	
.rc.res : 
	@echo ### Compiling $<
	$(RC) $<

!if "$(SHARED_LIB)" != ""
$(SHARED_LIB) : $(SHARED_SRC)
	@echo ### Creating $@
	@$(CC) $(CFLAGS) -Fo$(SHARED_BIN_DIR)\ $?
	@$(LIBCMD) /nologo /out:$@ $(SHARED_OBJS)
	@echo ### $@ Created
!endif

set_environment_variables:
	@set INCLUDE=$(INCLUDE)
	@set LIB=$(LIB)

# Libraries:








#----------------------------- Dependencies -----------------------------------

$(OBJS) : $(MAKEFILE) rtw_proj.tmw
