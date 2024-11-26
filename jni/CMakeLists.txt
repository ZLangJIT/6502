cmake_minimum_required(VERSION 3.18.8)

project("emu_main_jni")

# Gradle automatically packages shared libraries with your APK.

add_library(emu_main_jni SHARED
	jni.cpp
        game/Pong.cpp
        #game/Cube3D.cpp
        base/RBGame.cpp
        base/RBGameObject.cpp
        base/RBColor.cpp
        base/RBRenderHelper.cpp
        base/RBRenderer.cpp
        base/RBShader.cpp
        base/RBClock.cpp
        base/RBMath.cpp
        base/RBLog.cpp
)

target_include_directories(emu_main_jni PRIVATE game base)

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
