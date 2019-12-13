LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE := narutotest
LOCAL_SRC_FILES := \
    narutotest.cpp \

LOCAL_SHARED_LIBRARIES := \
   liblog \
   libhidlbase \
   libutils \
   android.hardware.naruto@1.0 \

include $(BUILD_EXECUTABLE)
