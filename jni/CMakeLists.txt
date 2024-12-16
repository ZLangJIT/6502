cmake_minimum_required(VERSION 3.18.8)

project("emu_main_jni")

add_library(emu_main_jni SHARED jni.cpp)

find_package(game-activity REQUIRED CONFIG)

target_link_libraries(emu_main_jni
	emu_main
        android
        game-activity::game-activity
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