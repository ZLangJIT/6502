cmake_minimum_required(VERSION 3.18.8)

project("emu_main_jni")

if (true)

# Diligent Engine exposes the following macros:
#
# PLATFORM_WIN32
# PLATFORM_UNIVERSAL_WINDOWS
# PLATFORM_ANDROID
# PLATFORM_LINUX
# PLATFORM_MACOS
# PLATFORM_IOS
# PLATFORM_TVOS

include_directories(WINAPI_KERNEL)

set(DILIGENT_NO_VULKAN TRUE CACHE BOOL "don't need vulkan")
set(DILIGENT_NO_FORMAT_VALIDATION TRUE CACHE BOOL "don't need format validation")

if(WIN32)
    if(${CMAKE_SYSTEM_NAME} STREQUAL "WindowsStore")
        add_definitions(-DPLATFORM_UNIVERSAL_WINDOWS)
    else()
        add_definitions(-DPLATFORM_WIN32)
    endif()
else()
    if(${CMAKE_SYSTEM_NAME} STREQUAL "Android")
        add_definitions(-DPLATFORM_ANDROID)
    elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
        add_definitions(-DPLATFORM_LINUX)
    elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
        if(IOS)
            add_definitions(-DPLATFORM_IOS)
        else()
            add_definitions(-DPLATFORM_MACOS)
        endif()
    elseif(${CMAKE_SYSTEM_NAME} STREQUAL "iOS")
        add_definitions(-DPLATFORM_IOS)
    elseif(${CMAKE_SYSTEM_NAME} STREQUAL "tvOS")
        add_definitions(-DPLATFORM_TVOS)
    else()
        message(FATAL_ERROR "Unsupported platform")
    endif()
endif(WIN32)

if(PLATFORM_MACOS OR PLATFORM_IOS OR PLATFORM_TVOS)
    add_definitions(-DPLATFORM_APPLE)
endif()

add_subdirectory(MultiTouch)

add_library(emu_main_jni SHARED AppInstance/native-lib.cpp)

target_link_libraries(
    emu_main_jni
	      emu_main
	      MultiTouch
        android
        EGL
        GLESv3
        jnigraphics
        log
        imgui
        nanovg
        handlemap
        simplelock
        simplethread
)

target_include_directories(emu_main_jni PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
else()
add_library(emu_main_jni SHARED jni.cpp)

find_package(game-activity REQUIRED CONFIG)

target_link_libraries(emu_main_jni
	emu_main
        game-activity::game-activity
        android
        EGL
        GLESv3
        jnigraphics
        log
        keystone
        capstone
        imgui
        nanovg
        handlemap
        simplelock
        simplethread
)

add_executable(executable__emu_main_jni_client.so jni_client.cpp)
target_link_libraries(executable__emu_main_jni_client.so PRIVATE
        android
        EGL
        GLESv3
        log
        keystone
        capstone
        imgui
        nanovg
        handlemap
        simplelock
        simplethread
)
endif()
