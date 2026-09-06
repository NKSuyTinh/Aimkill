LOCAL_PATH := $(call my-dir)
MAIN_LOCAL_PATH := $(call my-dir)

LOCAL_MODULE := libdobby
LOCAL_SRC_FILES:= Tools/Dobby/libdobby.a

include $(PREBUILT_STATIC_LIBRARY)
include $(CLEAR_VARS)

include $(CLEAR_VARS)
LOCAL_MODULE    := TERMINALX_MENU
# Code optimization
# -std=c++17 is required to support AIDE app with NDK
LOCAL_CFLAGS := -Wno-error=format-security -fvisibility=hidden -ffunction-sections -fdata-sections -w
LOCAL_CFLAGS += -fno-rtti -fno-exceptions -fpermissive
LOCAL_CPPFLAGS := -Wno-error=format-security -fvisibility=hidden -ffunction-sections -fdata-sections -w -Werror -s -std=c++17
LOCAL_CPPFLAGS += -Wno-error=c++11-narrowing -fms-extensions -fno-rtti -fno-exceptions -fpermissive
LOCAL_LDFLAGS += -Wl,--gc-sections,--strip-all, -llog
LOCAL_ARM_MODE := arm

LOCAL_C_INCLUDES += $(MAIN_LOCAL_PATH)

# Here you add the cpp file
LOCAL_SRC_FILES := client.cpp \
	Tools/SOCKET/client.cpp \
	Hack/Namegun.cpp \

LOCAL_LDLIBS := -llog -landroid -lGLESv2
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := Keystone
LOCAL_SRC_FILES := Tools/KittyMemory/Deps/Keystone/libs-android/$(TARGET_ARCH_ABI)/libkeystone.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
# Here is the name of your lib.
# When you change the lib name, change also on System.loadLibrary("") under OnCreate method on StaticActivity.java
# Both must have same name
LOCAL_MODULE    := TERMINALX999

LOCAL_CFLAGS := -Wno-error=format-security -fvisibility=hidden -ffunction-sections -fdata-sections -w
LOCAL_CFLAGS += -fno-rtti -fno-exceptions -fpermissive
LOCAL_CPPFLAGS := -Wno-error=format-security -fvisibility=hidden -ffunction-sections -fdata-sections -w -Werror -s -std=c++17
LOCAL_CPPFLAGS += -Wno-error=c++11-narrowing -fms-extensions -fno-rtti -fno-exceptions -fpermissive
LOCAL_LDFLAGS += -Wl,--gc-sections,--strip-all, -llog
LOCAL_ARM_MODE := arm

LOCAL_C_INCLUDES += $(MAIN_LOCAL_PATH) \
                    $(MAIN_LOCAL_PATH)/AutoUpdate/xdl/include


# Here you add the cpp file
LOCAL_SRC_FILES := backend.cpp \
   Hack/Namegun.cpp \
   AutoUpdate/Il2Cpp.cpp \
   AutoUpdate/xdl/xdl.c \
   AutoUpdate/xdl/xdl_iterate.c \
   AutoUpdate/xdl/xdl_linker.c \
   AutoUpdate/xdl/xdl_util.c \
   AutoUpdate/xdl/xdl_lzma.c \
   Tools/KittyMemory/KittyArm64.cpp \
   Tools/KittyMemory/KittyMemory.cpp \
   Tools/KittyMemory/KittyScanner.cpp \
   Tools/KittyMemory/KittyUtils.cpp \
   Tools/KittyMemory/MemoryBackup.cpp \
   Tools/KittyMemory/MemoryPatch.cpp \
   Tools/SOCKET/server.cpp \
   Tools/Substrate/hde64.c \
   Tools/Substrate/SubstrateDebug.cpp \
   Tools/Substrate/SubstrateHook.cpp \
   Tools/Substrate/SubstratePosixMemory.cpp \

LOCAL_LDLIBS := -llog -landroid -lGLESv2
LOCAL_STATIC_LIBRARIES := libdobby Keystone
include $(BUILD_SHARED_LIBRARY)






