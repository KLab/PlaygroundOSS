#
# FreeType2 static and shared C++ libraries
#

LOCAL_PATH := $(call my-dir)

SRC_PATH := ../src

FT2_SRC_FILES := \
	$(SRC_PATH)/autofit/autofit.c \
	$(SRC_PATH)/base/basepic.c \
	$(SRC_PATH)/base/ftapi.c \
	$(SRC_PATH)/base/ftbase.c \
	$(SRC_PATH)/base/ftbbox.c \
	$(SRC_PATH)/base/ftbitmap.c \
	$(SRC_PATH)/base/ftdbgmem.c \
	$(SRC_PATH)/base/ftdebug.c \
	$(SRC_PATH)/base/ftglyph.c \
	$(SRC_PATH)/base/ftinit.c \
	$(SRC_PATH)/base/ftpic.c \
	$(SRC_PATH)/base/ftstroke.c \
	$(SRC_PATH)/base/ftsynth.c \
	$(SRC_PATH)/base/ftsystem.c \
	$(SRC_PATH)/cff/cff.c \
	$(SRC_PATH)/pshinter/pshinter.c \
	$(SRC_PATH)/psnames/psnames.c \
	$(SRC_PATH)/raster/raster.c \
	$(SRC_PATH)/sfnt/sfnt.c \
	$(SRC_PATH)/smooth/smooth.c \
	$(SRC_PATH)/truetype/truetype.c

FT2_CFLAGS := \
	-DANDROID_NDK \
	-DFT2_BUILD_LIBRARY=1

FT2_INCLUDES := \
	$(LOCAL_PATH)/../include \
	$(LOCAL_PATH)/../src

# $(LOCAL_PATH)/include_all \

include $(CLEAR_VARS)

LOCAL_MODULE := freetype2_static
LOCAL_MODULE_FILENAME := libfreetype2

LOCAL_CFLAGS := $(FT2_CFLAGS)
LOCAL_C_INCLUDES := $(FT2_INCLUDES)
LOCAL_SRC_FILES := $(FT2_SRC_FILES)

LOCAL_LDLIBS := -ldl -llog

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := freetype2_shared
LOCAL_MODULE_FILENAME := libfreetype2

LOCAL_CFLAGS := $(FT2_CFLAGS)
LOCAL_C_INCLUDES := $(FT2_INCLUDES)
LOCAL_SRC_FILES := $(FT2_SRC_FILES)

LOCAL_LDLIBS := -ldl -llog

include $(BUILD_SHARED_LIBRARY)
