cmake_minimum_required(VERSION 3.16)


set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

project(lib_6502)

add_library(nanovg cli/nanovg/src/nanovg.c)
target_include_directories(nanovg PUBLIC cli/nanovg/include)

add_library(simplelock cli/simplelock.c)
target_include_directories(simplelock PUBLIC cli/include)

add_library(simplethread cli/simplethread.c)
target_include_directories(simplethread PUBLIC cli/include)

add_library(handlemap cli/handlemap.c)
target_include_directories(handlemap PUBLIC cli/include)
target_link_libraries(handlemap PRIVATE simplelock)

add_subdirectory(vrEmu6502)
add_subdirectory(src)
#add_subdirectory(cli)
if (ANDROID AND NOT TERMUX)
  add_subdirectory(jni)
endif()
