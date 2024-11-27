cmake_minimum_required(VERSION 3.18.8)

project("emu_main_jni")

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

find_package(game-activity REQUIRED CONFIG)

target_link_libraries(emu_main_jni
	emu_main
        android
        game-activity::game-activity
        EGL
        GLESv3
        jnigraphics
        log
)

add_executable(executable__emu_main_jni_client.so jni_client.cpp)
