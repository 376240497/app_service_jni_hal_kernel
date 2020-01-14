
LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := naruto.c

LOCAL_PROPRIETARY_MODULE := true

LOCAL_MODULE_RELATIVE_PATH := hw

LOCAL_SHARED_LIBRARIES := liblog libhardware

LOCAL_MODULE := naruto.default

LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)

