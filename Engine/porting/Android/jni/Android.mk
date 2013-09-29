LOCAL_PATH:= $(call my-dir)


# ---------------------
include $(CLEAR_VARS)
#
DEBUG_FLAGS		:=
#DEBUG_FLAGS		+=	-DDEBUG_MODIFIER
#DEBUG_FLAGS		+=	-DDEBUG_PERFORMANCE
#DEBUG_FLAGS		+=	-DDEBUG_MEMORY
#DEBUG_FLAGS		+=	-DDEBUG_LUA
DEBUG_FLAGS		+=	-DDEBUG_NULLTASK
DEBUG_FLAGS		+=	-DDEBUG_MENU

ifeq ($(TARGET_ARCH),arm)
  LOCAL_LDLIBS	:= -L$(LOCAL_PATH)/../obj/local/armeabi -lcurl
endif

ifeq ($(TARGET_ARCH),x86)
  LOCAL_LDLIBS	:= -L$(LOCAL_PATH)/../obj/local/x86 -lcurl
endif

ifdef ($(USE_LUAJIT))
  LOCAL_LDLIBS  += -lluajit-5.1
endif

# basic libraries
LOCAL_LDLIBS    += -llog -lGLESv1_CM -ldl -lz -lOpenSLES

# OpenGL ES 2.0/3.0 support
ifdef ($(USE_GLES2))
  LOCAL_LDLIBS	+=	-lGLESv2
  DEBUG_FLAGS	+=	-DOPENGL2
endif
ifdef ($(USE_GLES3))
  LOCAL_LDLIBS	+=	-lGLESv3
  DEBUG_FLAGS	+=	-DOPENGL3
endif

# for freetype2
LOCAL_LDLIBS    += -lfreetype2

# all directories contain .h files is regarded as include dir
LOCAL_C_INCLUDES :=	$(ANDROID_NDK_ROOT)/platforms/android-9/arch-$(TARGET_ARCH)/usr/include/
LOCAL_C_INCLUDES +=	$(shell find ./jni -regex '.*\.h$$' | sed 's/\/[^\/]*$$//' | sort | uniq)

# all *.c/*.cpp files under src dirs are listed for building
SRC_DIRS    := ./jni/include
SRC_DIRS    += ./jni/libs
SRC_DIRS    += ./jni/source
SRC_DIRS    += ./jni/custom
SRC_DIRS    += ./jni/Android
SRC_DIRS    += ./jni/UserTask 
SRC_FILES   :=	$(shell find $(SRC_DIRS) -name "*.c" -or -name "*.cpp")

LOCAL_SRC_FILES	:=	$(subst ./jni/,,$(SRC_FILES))

ENGINE_GITHASH  := $(shell git log --pretty=format:%h -1)
# force refresh engine hash
$(shell touch ./jni/Android/KLBPlatformMetrics.cpp)

LOCAL_CFLAGS    := -DDEBUG -DLUA_ANSI -DIOAPI_NO_64 $(DEBUG_FLAGS) -DENGINE_GITHASH='"$(ENGINE_GITHASH)"'
LOCAL_CPPFLAGS  := -fexceptions -fno-rtti
LOCAL_MODULE    := libGame

ifeq ($(TARGET_ARCH),arm)
# notice: these assembly files (*.s) generate compile-time warnings under Clang but they are harmless.
  LOCAL_SRC_FILES += \
	./libs/Tremolo/bitwiseARM.s \
	./libs/Tremolo/dpen.s \
	./libs/Tremolo/floor1ARM.s \
	./libs/Tremolo/mdctARM.s
  LOCAL_CFLAGS += -D_ARM_ASSEM_

  LOCAL_ARM_MODE  := arm
  LOCAL_ARM_NEON  := true
  TARGET_ARCH_ABI := armeabi-v7a
  LOCAL_CFLAGS    += -O3 -mcpu=cortex-a8 -mfloat-abi=softfp -fPIC -march=armv7-a -ffunction-sections -funwind-tables -fstack-protector -fno-short-enums
else
  LOCAL_CFLAGS += -DONLY_C
endif
					

include $(BUILD_SHARED_LIBRARY)
# ---------------------


# ---------------------
include $(CLEAR_VARS)

ifeq ($(TARGET_ARCH),arm)
  LOCAL_ARM_MODE  := arm
  LOCAL_ARM_NEON  := true
  TARGET_ARCH_ABI := armeabi-v7a
endif

LOCAL_MODULE    := libjniproxy
LOCAL_C_INCLUDES := ./jni/proxy
LOCAL_CFLAGS    := -Werror
LOCAL_SRC_FILES := proxy/jniproxy.cpp
LOCAL_LDLIBS    := -llog

include $(BUILD_SHARED_LIBRARY)
# ---------------------

