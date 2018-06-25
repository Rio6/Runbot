cmake_minimum_required(VERSION 2.6)
project(runbot)
set(VERSION 0.2)

# Set flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O2 -Wall")

# Add sources
file(GLOB sources "src/*.cpp")
add_executable(${PROJECT_NAME} ${sources})

# Include
include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/include)

# Libraries for windows
if(${CMAKE_SYSTEM_NAME} MATCHES Windows)
    target_link_libraries(${PROJECT_NAME} mingw32 SDL2main)
    SET(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -mwindows")
endif()

# Find libraries
include(FindPkgConfig)
find_package(PkgConfig REQUIRED)

pkg_check_modules(SDL2 REQUIRED sdl2 SDL2_image SDL2_mixer)
include_directories(${SDL2_INCLUDES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

# Configs
option(USE_VSYNC "Enable V-SYNC" ON)
set(BIN_DIR "${CMAKE_INSTALL_PREFIX}/bin" CACHE PATH "Binary path")
set(DATA_DIR "${CMAKE_INSTALL_PREFIX}/share/${PROJECT_NAME}" CACHE STRING "Asset path")
configure_file(include/config.h.in include/config.h)

# Install
install(TARGETS ${PROJECT_NAME} DESTINATION ${BIN_DIR})
install(DIRECTORY assets/ DESTINATION ${DATA_DIR})
