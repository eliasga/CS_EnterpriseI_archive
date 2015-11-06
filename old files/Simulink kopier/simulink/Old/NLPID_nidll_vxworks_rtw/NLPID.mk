
# Copyright 1994-2001 The MathWorks, Inc.
#
# File    : NLPID.mk (for Release 2007b and later)
#
# Abstract:
#       Real-Time Workshop template makefile for building a real-time
#       version of a Simulink model to run on National Instruments
#       RT Series hardware. This template makefile uses generated C code
#       and supports the WindRiver GNU Toolchain.
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

USER_INCLUDES := 
USER_SRCS := 

MAKECMD         = c:\gccdist\supp\setup-gcc.bat && make
HOST            = PC
BUILD           = yes
SYS_TARGET_FILE = nidll_vxworks.tlc
BUILD_SUCCESS	= ... Created
CPU             = PPC603

MODEL           := NLPID
MODULES         := NLPID_data.c is_little_endian_rt.c rtGetInf.c rtGetNaN.c rt_atan2_snf.c rt_backsubrr_dbl.c rt_forwardsubrr_dbl.c rt_logging.c rt_look.c rt_look2d_normal.c rt_lu_real.c rt_matdivrr_dbl.c rt_nonfinite.c rt_pow_snf.c rt_rem_snf.c rt_round_snf.c rt_zcfcn.c svd_d_rt.c svd_helper_rt.c 
MAKEFILE        := NLPID.mk
MATLAB_ROOT     := C:\Program Files\MATLAB\R2009a
ALT_MATLAB_ROOT := C:\PROGRA~1\MATLAB\R2009a
MATLAB_BIN      := C:\Program Files\MATLAB\R2009a\bin
ALT_MATLAB_BIN  := C:\PROGRA~1\MATLAB\R2009a\bin
S_FUNCTIONS     := 
S_FUNCTIONS_LIB := 
SOLVER          := ode5.c
NUMST           := 2
TID01EQ         := 1
NCSTATES        := 17
BUILDARGS       :=  GENERATE_REPORT=0
MULTITASKING    := 0
EXT_MODE        := 0
MATLAB_VERSION	:= R2009a
STR_MATLAB_VERSION := "$(MATLAB_VERSION)"
SIT_VERSION		= 2010
SIT_LIB_DIR     = $(SIT_ROOT)\$(SIT_VERSION)\ModelInterface\tmw\lib\vxworks\$(MATLAB_VERSION)

MODELREFS            := 
SHARED_SRC           := 
SHARED_SRC_DIR       := 
SHARED_BIN_DIR       := 
SHARED_LIB           := 

#--------------------------- Model and reference models -----------------------
MODELLIB                  := NLPIDlib.lib
MODELREF_LINK_LIBS   	  := 
MODELREF_INC_PATH         := 
RELATIVE_PATH_TO_ANCHOR   := ..
# ..\..\..\..\..\..\.. or .. or even . if you want it
MODELREF_TARGET_TYPE      := NONE

#------------------------- Adjustments Needed By VxWorks ----------------------
MODELREF_LINK_LIBS        := $(subst \,/,$(MODELREF_LINK_LIBS))
MATLAB_ROOT               := $(subst \,/,$(MATLAB_ROOT))
ALT_MATLAB_ROOT           := $(subst \,/,$(ALT_MATLAB_ROOT))
MATLAB_BIN                := $(subst \,/,$(MATLAB_BIN))
ALT_MATLAB_BIN            := $(subst \,/,$(ALT_MATLAB_BIN))
S_FUNCTIONS               := $(subst \,/,$(S_FUNCTIONS))
S_FUNCTIONS_LIB           := $(S_FUNCTIONS_LIB:.lib=.a)
S_FUNCTIONS_LIB           := $(subst \,/,$(S_FUNCTIONS_LIB))
MODELREFS                 := $(subst \,/,$(MODELREFS))
SHARED_SRC                := $(subst \,/,$(SHARED_SRC))
SHARED_SRC_DIR            := $(subst \,/,$(SHARED_SRC_DIR))
SHARED_BIN_DIR            := $(subst \,/,$(SHARED_BIN_DIR))
SHARED_LIB	              := $(subst \,/,$(SHARED_LIB))
MODELREF_INC_PATH         := $(subst \,/,$(MODELREF_INC_PATH))
RELATIVE_PATH_TO_ANCHOR   := $(subst \,/,$(RELATIVE_PATH_TO_ANCHOR))
SHARED_LIB                := $(SHARED_LIB:.lib=.a)
SIT_ROOT                  := $(subst \,/,$(SIT_ROOT))
SIT_LIB_DIR               := $(subst \,/,$(SIT_LIB_DIR))

ifneq "$(STR_MATLAB_VERSION)" "14.0"
MATLAB_ROOT := $(ALT_MATLAB_ROOT)
MATLAB_BIN := $(ALT_MATLAB_BIN)
endif

#--------------------------- Tool Specifications ------------------------------
WIND_BASE := $(subst \,/,$(WIND_BASE))
WIND_HOME := $(subst \,/,$(WIND_HOME))
TOOL_FAMILY = gnu
TOOL = gnu

CC := ccppc.exe
AR := arppc.exe
COMPILER_INCLUDES := -I$(WIND_BASE)/target/h

#------------------------------ Include/Lib Path ------------------------------

MATLAB_INCLUDES :=                    -I$(MATLAB_ROOT)\simulink\include
MATLAB_INCLUDES := $(MATLAB_INCLUDES) -I$(MATLAB_ROOT)\extern\include
MATLAB_INCLUDES := $(MATLAB_INCLUDES) -I$(MATLAB_ROOT)\rtw\c\src
MATLAB_INCLUDES := $(MATLAB_INCLUDES) -I$(MATLAB_ROOT)\rtw\c\src\ext_mode\common
# Additional file include paths


MATLAB_INCLUDES := $(MATLAB_INCLUDES) -IC:\DOCUME~1\mcl\Desktop\CSENTE~1\HMIs\models\simulink\NLPID_nidll_vxworks_rtw
MATLAB_INCLUDES := $(MATLAB_INCLUDES) -IC:\DOCUME~1\mcl\Desktop\CSENTE~1\HMIs\models\simulink
MATLAB_INCLUDES := $(MATLAB_INCLUDES) -I$(MATLAB_ROOT)\toolbox\dspblks\include

INCLUDE := -I$(RELATIVE_PATH_TO_ANCHOR) $(MATLAB_INCLUDES) $(MODELREF_INC_PATH) -I$(SIT_ROOT)/$(SIT_VERSION)/ModelInterface/ $(COMPILER_INCLUDES) -I.
ifneq "$(SHARED_SRC_DIR)" ""
INCLUDE := $(INCLUDE) -I$(SHARED_SRC_DIR)
endif

#Adjust include paths for VxWorks/make
INCLUDE                  := $(subst \,/,$(INCLUDE))

RTM_CC_OPTS := -DUSE_RTMODEL
LOG_SRC:=
NIDLL_SRC:=nidll_main.c

#----------------- Compiler and Linker Options --------------------------------

# Optimization Options
#   Set  OPT_OPTS:=-Zd  for debugging
OPT_OPTS := $(DEFAULT_OPT_OPTS)

# General User Options

USE_REBUILT_RTW_LIB_FILES := 1

# Other User Options
CC_OPTS := $(OPT_OPTS) $(OPTS) $(RTM_CC_OPTS)

OS_CFLAGS := -mcpu=603 -mstrict-align -mno-implicit-fp
OS_CFLAGS := $(OS_CFLAGS) -Wall -mlongcall \
	-export-all -DCPU=$(CPU) -DTOOL_FAMILY=gnu -DTOOL=gnu -D_WRS_KERNEL
OS_CPPFLAGS := $(OS_CFLAGS) -ansi -MD -MP
BUILD_CFLAGS = -g
BUILD_CPPFLAGS = $(BUILD_CFLAGS)

ifeq "$(MODELREF_TARGET_TYPE)" "NONE"
CC_OPTS := $(CC_OPTS) -DNI_ROOTMODEL_$(MODEL)
endif

CPP_REQ_DEFINES := -DMODEL=$(MODEL) -DRT -DNUMST=$(NUMST) \
		  -DTID01EQ=$(TID01EQ) -DNCSTATES=$(NCSTATES) \
		  -DMT=$(MULTITASKING) -DHAVESTDIO -DNATIONAL_INSTRUMENTS_SIT \
		  -DVXWORKS

CFLAGS := $(OS_CFLAGS) $(BUILD_CFLAGS) $(CC_OPTS) $(CPP_REQ_DEFINES) $(USER_INCLUDES) \
	 $(cflags) $(cvarsdll)

CPPFLAGS := $(OS_CPPFLAGS) $(BUILD_CPPFLAGS) $(CPP_OPTS) $(CC_OPTS) $(CPP_REQ_DEFINES) $(USER_INCLUDES) \
	 $(cflags) $(cvarsdll) /GX
LDFLAGS  := $(CFLAGS)

#----------------------------- Source Files -----------------------------------

#DLL
ifeq "$(MODELREF_TARGET_TYPE)" "NONE"
PRODUCT   := $(MODEL).out

REQ_SRCS  := $(MODEL).c $(MODULES) $(NIDLL_SRC) rt_sim.c \
	    $(SOLVER) $(LOG_SRC)

#Model Reference Target
else
PRODUCT   := $(MODELLIB)
REQ_SRCS  := $(MODULES)
endif

SRCS := $(REQ_SRCS) $(USER_SRCS) $(S_FUNCTIONS)
OBJS_CPP_UPPER := $(SRCS:.CPP=.o)
OBJS_CPP_LOWER := $(OBJS_CPP_UPPER:.cpp=.o)
OBJS_C_UPPER := $(OBJS_CPP_LOWER:.C=.o)
OBJS := $(OBJS_C_UPPER:.c=.o)
SHARED_OBJS := $(SHARED_SRC:.c*=.o)

# ------------------------- Additional Libraries ------------------------------

LIBS :=


LIBS := $(subst \,/,$(LIBS))
#--------------------------------- Rules --------------------------------------

ifeq "$(MODELREF_TARGET_TYPE)" "NONE"
#--- Stand-alone model ---
$(PRODUCT) : create_nidll_code create_lib_dir $(OBJS) $(SHARED_LIB) $(LIBS) $(MODELREF_LINK_LIBS)
	@echo \#\#\# Linking ...
	rm -f "$@" ctdt.c;nmppc $(OBJS) | tclsh $(WIND_BASE)/host/resource/hutils/tcl/munch.tcl -c ppc > ctdt.c
	$(CC) $(LDFLAGS) -fdollars-in-identifiers -Wall $(INCLUDE)-DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -o ctdt.o -c ctdt.c
	$(CC) -r -nostdlib -Wl,-X -T $(WIND_BASE)/target/h/tool/gnu/ldscripts/link.OUT -o "$@" $(OBJS) $(LIBPATH) $(SHARED_LIB) $(LIBS) $(MODELREF_LINK_LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS)
	rm -f ctdt.c ctdt.o
	@echo $(BUILD_SUCCESS) $@ in directory:
	@pwd
	@echo
else
#--- Model reference RTW Target ---
$(PRODUCT) : create_lib_dir $(OBJS) $(LIBS)
	echo ### Linking ...
	rm -f "$@" ctdt.c;nmppc $(OBJS) | tclsh $(WIND_BASE)/host/resource/hutils/tcl/munch.tcl -c ppc > ctdt.c
	$(CC) $(LDFLAGS) -fdollars-in-identifiers -Wall $(INCLUDE)-DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -o ctdt.o -c ctdt.c
	$(CC) -r -nostdlib -Wl,-X -T $(WIND_BASE)/target/h/tool/gnu/ldscripts/link.OUT -o "$@" $(OBJS) $(LIBPATH) $(LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS)
	rm -f ctdt.c ctdt.o
	echo $(BUILD_SUCCESS) static library $(MODELLIB)
endif

# Copy files.
create_nidll_code :
	cp $(SIT_ROOT)/$(SIT_VERSION)/ModelInterface/tmw/$(NIDLL_SRC) ./$(NIDLL_SRC)
	cp $(SIT_ROOT)/$(SIT_VERSION)/ModelInterface/tmw/model_info.h ./model_info.h
	@chmod a+rw ./model_info.h
 
# Create the lib directory if it doesn't exist
create_lib_dir:
	@if [ ! -d "$(SIT_LIB_DIR)" ]; then\
		echo mkdir -p $(SIT_LIB_DIR);\
		mkdir -p $(SIT_LIB_DIR);\
	fi


nidll_main.o : ./$(NIDLL_SRC)
	@echo \#\#\# Compiling $<
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

%.o :$(MATLAB_ROOT)/rtw/c/src/%.c
	@echo \#\#\# Compiling $<
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

# Additional sources

%.o:$(MATLAB_ROOT)\toolbox\rtw\dspblks\c\dspsvd/%.c
	@echo \#\#\# Compiling $(subst \,/,$<)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $(subst \,/,$<)

%.o:$(MATLAB_ROOT)\toolbox\rtw\dspblks\c\dspendian/%.c
	@echo \#\#\# Compiling $(subst \,/,$<)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $(subst \,/,$<)

%.o:$(MATLAB_ROOT)\rtw\c\src/%.c
	@echo \#\#\# Compiling $(subst \,/,$<)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $(subst \,/,$<)



%.o:$(MATLAB_ROOT)\toolbox\rtw\dspblks\c\dspsvd/%.cpp
	@echo \#\#\# Compiling $(subst \,/,$<)
	$(CC) $(CPPFLAGS) $(INCLUDE) -o $@ -c $(subst \,/,$<)

%.o:$(MATLAB_ROOT)\toolbox\rtw\dspblks\c\dspendian/%.cpp
	@echo \#\#\# Compiling $(subst \,/,$<)
	$(CC) $(CPPFLAGS) $(INCLUDE) -o $@ -c $(subst \,/,$<)

%.o:$(MATLAB_ROOT)\rtw\c\src/%.cpp
	@echo \#\#\# Compiling $(subst \,/,$<)
	$(CC) $(CPPFLAGS) $(INCLUDE) -o $@ -c $(subst \,/,$<)




$(SIT_LIB_DIR)/%.o:$(MATLAB_ROOT)\toolbox\rtw\dspblks\c\dspsvd/%.c
	@echo \#\#\# Compiling $(subst \,/,$<)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $(subst \,/,$<)

$(SIT_LIB_DIR)/%.o:$(MATLAB_ROOT)\toolbox\rtw\dspblks\c\dspendian/%.c
	@echo \#\#\# Compiling $(subst \,/,$<)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $(subst \,/,$<)

$(SIT_LIB_DIR)/%.o:$(MATLAB_ROOT)\rtw\c\src/%.c
	@echo \#\#\# Compiling $(subst \,/,$<)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $(subst \,/,$<)



$(SIT_LIB_DIR)/%.o:$(MATLAB_ROOT)\toolbox\rtw\dspblks\c\dspsvd/%.cpp
	@echo \#\#\# Compiling $(subst \,/,$<)
	$(CC) $(CPPFLAGS) $(INCLUDE) -o $@ -c $(subst \,/,$<)

$(SIT_LIB_DIR)/%.o:$(MATLAB_ROOT)\toolbox\rtw\dspblks\c\dspendian/%.cpp
	@echo \#\#\# Compiling $(subst \,/,$<)
	$(CC) $(CPPFLAGS) $(INCLUDE) -o $@ -c $(subst \,/,$<)

$(SIT_LIB_DIR)/%.o:$(MATLAB_ROOT)\rtw\c\src/%.cpp
	@echo \#\#\# Compiling $(subst \,/,$<)
	$(CC) $(CPPFLAGS) $(INCLUDE) -o $@ -c $(subst \,/,$<)



# Look in simulink/src helper files

%.o:$(MATLAB_ROOT)/simulink/src/%.c
	@echo \#\#\# Compiling $<
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

%.o:$(MATLAB_ROOT)/simulink/src/%.cpp
	@echo \#\#\# Compiling $<
	$(CC) $(CPPFLAGS) $(INCLUDE) -o $@ -c $<

# Put these rule last, otherwise nmake will check toolboxes first

%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	@echo \#\#\# Compiling $<
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.cpp
	@echo \#\#\# Compiling $<
	$(CC) $(CPPFLAGS) $(INCLUDE) -o $@ -c $<

%.o : %.cpp
	@echo \#\#\# Compiling $<
	$(CC) $(CPPFLAGS) $(INCLUDE) -o $@ -c $<

$(MODEL).o : $(MODEL).c
	@echo \#\#\# Compiling the source $(MODEL)
	$(CC) $(CFLAGS) $(INCLUDE) -DRVE -o $@ -c $<

%.o : %.c
	@echo \#\#\# Compiling $<
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

ifneq "$(SHARED_LIB)" ""
$(SHARED_LIB) : $(SHARED_SRC)
	@echo \#\#\# Creating $@
	$(CC) $(CFLAGS) $(INCLUDE) -c $?
	cp $(patsubst %.cpp,%.o,$(?F:.c=.o)) $(SHARED_SRC_DIR)
	$(AR) cr $@ $(SHARED_OBJS)
	@echo \#\#\# $@ Created
endif

# Libraries:








#----------------------------- Dependencies -----------------------------------

$(OBJS) : $(MAKEFILE) rtw_proj.tmw
