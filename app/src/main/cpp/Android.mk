LOCAL_PATH := $(call my-dir)

include $(LOCAL_PATH)/libs.mk

include $(CLEAR_VARS)

LOCAL_CFLAGS += -Wall -Wno-unused-parameter -Wno-unused-function -Wno-sign-compare -Wno-uninitialized -Wno-unused-command-line-argument -g -DOS_LINUX

LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := demo485

DIRS = .

INC  = $(foreach dir,$(DIRS),$(LOCAL_PATH)/$(dir))
SRC  = $(foreach dir,$(DIRS),$(wildcard $(LOCAL_PATH)/$(dir)/*.c))
SRC += $(foreach dir,$(DIRS),$(wildcard $(LOCAL_PATH)/$(dir)/*.cpp))

LOCAL_SRC_FILES := $(SRC:$(LOCAL_PATH)/%=%)

LOCAL_C_INCLUDES := $(INC) $(LOCAL_PATH)/include

#LOCAL_LDFLAGS := -pie -fPIE

LOCAL_STATIC_LIBRARIES := libmisc libtinyxml

include $(BUILD_SHARED_LIBRARY)
