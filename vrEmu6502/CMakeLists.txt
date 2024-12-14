cmake_minimum_required(VERSION 3.18.8)


set(CMAKE_C_STANDARD 11)

project(vrEmu6502)

if(MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

include(CTest)

add_subdirectory(src)

add_subdirectory(test)
