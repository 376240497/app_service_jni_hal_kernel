LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE :=simplecdevtest 

LOCAL_CFLAGS += -Wno-unused-const-variable -Wno-unused-variable -Wno-unused-parameter

LOCAL_SRC_FILES := \
    test.c \

include $(BUILD_EXECUTABLE)
