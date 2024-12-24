cmake_minimum_required(VERSION 3.16)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

project(lib_6502)

include(./build_root.cmake)

build_root_init(${CMAKE_CURRENT_SOURCE_DIR}/cmake/packages ${CMAKE_CURRENT_BINARY_DIR}/BUILD_ROOT)

build_root_add_cmake_package(${CMAKE_CURRENT_SOURCE_DIR}/imgui_fonts . imgui_fonts
    "" # no extra c flags
    "" # no extra cxx flags
    "" # no extra configure flags
    imgui_fonts
    include ""
    lib
    libimgui_fonts.dll
    libimgui_fonts.a
    libimgui_fonts.dylib
    ""
    ""
    ""
)

build_root_add_cmake_package(${CMAKE_CURRENT_SOURCE_DIR}/harfbuzz-ft . harfbuzz_ft
    "" # no extra c flags
    "" # no extra cxx flags
    "" # no extra configure flags
    harfbuzz
    include harfbuzz/hb.h
    lib
    libharfbuzz.dll
    libharfbuzz.a
    libharfbuzz.dylib
    ""
    ""
    ""
)

build_root_add_cmake_package(${CMAKE_CURRENT_SOURCE_DIR}/harfbuzz-ft . harfbuzz_ft
    "" # no extra c flags
    "" # no extra cxx flags
    "" # no extra configure flags
    freetype
    include/freetype2 ft2build.h
    lib
    libfreetype.dll
    libfreetype.a
    libfreetype.dylib
    ""
    ""
    ""
)

build_root_add_cmake_package(${CMAKE_CURRENT_SOURCE_DIR}/libyaml . libyaml
    "" # no extra c flags
    "" # no extra cxx flags
    "" # no extra configure flags
    libyaml
    include yaml.h
    lib
    libyaml.dll
    libyaml.a
    libyaml.dylib
    ""
    ""
    ""
)

build_root_add_cmake_package(${CMAKE_CURRENT_SOURCE_DIR}/capstone . capstone
    "" # no extra c flags
    "" # no extra cxx flags
    "" # no extra configure flags
    capstone
    include capstone/capstone.h
    lib
    libcapstone.dll
    libcapstone.a
    libcapstone.dylib
    ""
    ""
    ""
)

build_root_add_cmake_package(${CMAKE_CURRENT_SOURCE_DIR}/keystone . keystone
    "" # no extra c flags
    "" # no extra cxx flags
    "" # no extra configure flags
    keystone
    include keystone/keystone.h
    lib
    libkeystone.dll
    libkeystone.a
    libkeystone.dylib
    ""
    ""
    ""
)

add_library(imgui_freetype
  imgui/misc/freetype/imgui_freetype.cpp
)
target_include_directories(imgui_freetype PUBLIC imgui imgui/misc/freetype)
target_link_libraries(imgui_freetype PUBLIC freetype harfbuzz)
install(TARGETS imgui_freetype DESTINATION lib)

add_library(imgui
  imgui/imgui.cpp
  imgui/imgui_draw.cpp
  imgui/imgui_tables.cpp
  imgui/imgui_widgets.cpp
)
if (ANDROID)
  add_library(imgui_backend STATIC
    imgui/backends/imgui_impl_android.cpp
    imgui/backends/imgui_impl_opengl3.cpp
  )
  target_include_directories(imgui_backend PUBLIC imgui imgui/backends)
endif()
target_link_libraries(imgui PUBLIC imgui_fonts imgui_freetype imgui_backend)
install(TARGETS imgui DESTINATION lib)

add_library(nanovg cli/nanovg/src/nanovg.c)
target_include_directories(nanovg PUBLIC cli/nanovg/include)
install(TARGETS nanovg DESTINATION lib)

add_library(simplelock cli/simplelock.c)
target_include_directories(simplelock PUBLIC cli/include)
install(TARGETS simplelock DESTINATION lib)

add_library(simplethread cli/simplethread.c)
target_include_directories(simplethread PUBLIC cli/include)
install(TARGETS simplethread DESTINATION lib)

add_library(handlemap cli/handlemap.c)
target_include_directories(handlemap PUBLIC cli/include)
target_link_libraries(handlemap PRIVATE simplelock)
install(TARGETS handlemap DESTINATION lib)

add_subdirectory(vrEmu6502)
add_subdirectory(src)
#add_subdirectory(cli)
if (ANDROID AND NOT TERMUX)
  add_subdirectory(jni)
endif()
