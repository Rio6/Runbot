
# Uncomment this if you're using STL in your project
# See CPLUSPLUS-SUPPORT.html in the NDK documentation for more information
#APP_STL := stlport_static 
APP_STL := c++_shared
APP_CPPFLAGS += -std=gnu++14 -fexceptions -frtti -Wno-parentheses

APP_ABI := armeabi armeabi-v7a x86 x86_64

# Min SDK level
APP_PLATFORM=android-14

