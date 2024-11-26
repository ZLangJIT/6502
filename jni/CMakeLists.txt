cmake_minimum_required(VERSION 3.18.8)

project("emu_main_jni")

# Gradle automatically packages shared libraries with your APK.

add_library(emu_main_jni SHARED
	jni.cpp
)

find_library(log-lib log)

find_package(game-activity REQUIRED CONFIG)

target_link_libraries(emu_main_jni
	emu_main
        android

        # The game activity
        game-activity::game-activity

        # EGL, required for configuring the display context
        EGL

        # GL ES 3, used for the sample renderer
        GLESv3

        # for AImageDecoder, to load images from resources
        jnigraphics

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib}
)
