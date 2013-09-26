#
# FreeType2 prebuilt static C++ library
#

__WAS_PATH := $(LOCAL_PATH)
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := freetype2_prebuilt_static
LOCAL_SRC_FILES := ../obj/local/$(TARGET_ARCH_ABI)/libfreetype2.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../include

include $(PREBUILT_STATIC_LIBRARY)

LOCAL_PATH := $(__WAS_PATH)
