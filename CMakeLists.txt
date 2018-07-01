cmake_minimum_required(VERSION 2.6)
project(runbot)
set(VERSION 0.3.1)

# Set flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O2 -Wall")

# Add sources
file(GLOB sources "src/*.cpp")
add_executable(${PROJECT_NAME} ${sources})

# Include
include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/include)

if(${CMAKE_SYSTEM_NAME} MATCHES Windows)
    # Libraries for windows
    target_link_libraries(${PROJECT_NAME} mingw32 SDL2main)
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static -mwindows")
    # Application icon
    add_custom_command(OUTPUT runbot.ico COMMAND convert -resize 256x256 ${CMAKE_SOURCE_DIR}/runbot.png runbot.ico DEPENDS ${CMAKE_SOURCE_DIR}/runbot.png)
    add_custom_command(OUTPUT icon.rc COMMAND echo 0 ICON runbot.ico > icon.rc DEPENDS runbot.ico)
    add_custom_command(OUTPUT icon.o COMMAND ${CMAKE_RC_COMPILER} -i icon.rc -O coff -o icon.o DEPENDS icon.rc)
    add_custom_target(icon DEPENDS icon.o)
    add_dependencies(${PROJECT_NAME} icon)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_BINARY_DIR}/icon.o)
endif()

# Find libraries
include(FindPkgConfig)
find_package(PkgConfig REQUIRED)

pkg_check_modules(SDL2 REQUIRED sdl2 SDL2_image SDL2_mixer)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

if(${CMAKE_SYSTEM_NAME} MATCHES Windows)
    # Libraries for static linking SDL
    target_link_libraries(${PROJECT_NAME} m dinput8 dxguid dxerr8 user32 gdi32 winmm imm32 ole32 oleaut32 shell32 version uuid)
endif()

# Configs
option(USE_VSYNC "Enable V-SYNC" ON)
set(DATA_DIR "${CMAKE_INSTALL_PREFIX}/share/${PROJECT_NAME}" CACHE STRING "Asset path")
configure_file(include/config.h.in include/config.h)

# Install
install(TARGETS ${PROJECT_NAME} DESTINATION "bin")
install(DIRECTORY assets/ DESTINATION ${DATA_DIR})
install(FILES runbot.desktop DESTINATION "share/applications")
install(FILES runbot.png DESTINATION "share/pixmaps")
