PROJECT_NAME := ivhw_gameoflife_ani
TARGET_EXEC := $(PROJECT_NAME).exe

PROJECT_ROOT:=./
SRC_ROOT:=$(PROJECT_ROOT)src/
PYTHON_ROOT:=c:/Python38_32/

CPP_SRCS:=\
$(SRC_ROOT)$(PROJECT_NAME).cpp


INC_DIRS:=\
-I$(PROJECT_ROOT)include \
-I$(PYTHON_ROOT)include \
-I$(PYTHON_ROOT)Lib/site-packages/numpy/core/include

LIB_PYTHON_DIR:=c:/Python38_32
LIB_PYTHON:=python38

TOOLCHAIN_PREFIX := mingw32-
TOOLCHAIN_ROOT := C:/MinGW/bin
CXX := $(TOOLCHAIN_ROOT)/$(TOOLCHAIN_PREFIX)g++
CC := $(TOOLCHAIN_ROOT)/$(TOOLCHAIN_PREFIX)gcc
AR := $(TOOLCHAIN_ROOT)/$(TOOLCHAIN_PREFIX)ar

CPPFLAGS:=-std=gnu++11

LDFLAGS:=-L$(LIB_PYTHON_DIR)
LIB_GCC:=-lm -lgcc

#build target
$(TARGET_EXEC): $(CPP_SRCS)
	@echo target: $(TARGET_EXEC)
	@echo include dir: $(INC_DIRS)
	@echo c++ source: $(CPP_SRCS)
	$(CXX) $(CPPFLAGS) $(LDFLAGS) $(INC_DIRS) $(LIB_GCC) $(CPP_SRCS) -o $@ -l$(LIB_PYTHON)


clean:
	@rm -f $(TARGET_EXEC)