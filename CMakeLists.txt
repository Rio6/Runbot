cmake_minimum_required(VERSION 2.6)
project(runbot)
set(${PROJECT_NAME}_VERSION 0.1)

# Set flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O2 -Wall")

# Add sources
file(GLOB sources "src/*.cpp")
add_executable(${PROJECT_NAME} ${sources})

if(CMAKE_CROSSCOMPILING AND ${CMAKE_SYSTEM_NAME} MATCHES Windows)
    target_link_libraries(${PROJECT_NAME} mingw32 SDL2main)
endif()

# Find libraries
include(FindPkgConfig)
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2 SDL2_image SDL2_mixer)
include_directories(include ${SDL2_INCLUDES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

# Configs
configure_file(include/config.h.in include/config.h)
option(USE_VSYNC "Enable V-SYNC" ON)
