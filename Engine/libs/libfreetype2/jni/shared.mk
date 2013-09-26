#
# FreeType2 prebuilt shared C++ library
#

__WAS_PATH := $(LOCAL_PATH)
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := freetype2_prebuilt_shared
LOCAL_SRC_FILES := ../libs/$(TARGET_ARCH_ABI)/libfreetype2.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../include

include $(PREBUILT_SHARED_LIBRARY)

LOCAL_PATH := $(__WAS_PATH)
