
include $(CLEAR_VARS)
LOCAL_MODULE := libmisc
LOCAL_SRC_FILES := ./libs/libmisc.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libtinyxml
LOCAL_SRC_FILES := ./libs/libtinyxml.a
include $(PREBUILT_STATIC_LIBRARY)
