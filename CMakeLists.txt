cmake_minimum_required(VERSION 3.16)


set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

project(lib_6502)

add_subdirectory(vrEmu6502)
add_subdirectory(src)
add_subdirectory(cli)
if (ANDROID)
  add_subdirectory(jni)
else()
endif()
