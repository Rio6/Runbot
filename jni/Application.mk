
# Uncomment this if you're using STL in your project
# See CPLUSPLUS-SUPPORT.html in the NDK documentation for more information
#APP_STL := stlport_static 
APP_STL := c++_shared
APP_CPPFLAGS += -std=gnu++14 -fexceptions -frtti

APP_ABI := armeabi armeabi-v7a x86

# Min SDK level
APP_PLATFORM=android-14
