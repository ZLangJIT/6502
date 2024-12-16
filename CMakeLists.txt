cmake_minimum_required(VERSION 3.16)


set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

project(lib_6502)

include(./build_root.cmake)

build_root_init(${CMAKE_CURRENT_SOURCE_DIR}/cmake/packages ${CMAKE_CURRENT_BINARY_DIR}/BUILD_ROOT)

build_root_add_cmake_package(${CMAKE_CURRENT_SOURCE_DIR}/libyaml . libyaml
    "" # no extra c flags
    "" # no extra cxx flags
    "" # no extra configure flags
    YAML
    include yaml.h
    lib
    libyaml.dll
    libyaml.a
    libyaml.dylib
    ""
    ""
    ""
)

build_root_add_cmake_package(${CMAKE_CURRENT_SOURCE_DIR}/keystone . keystone
    "" # no extra c flags
    "" # no extra cxx flags
    "" # no extra configure flags
    keystone
    include keystone.h
    lib
    libkeystone.dll
    libkeystone.a
    libkeystone.dylib
    ""
    ""
    ""
)

build_root_add_cmake_package(${CMAKE_CURRENT_SOURCE_DIR}/capstone . capstone
    "" # no extra c flags
    "" # no extra cxx flags
    "" # no extra configure flags
    capstone
    include capstone.h
    lib
    libcapstone.dll
    libcapstone.a
    libcapstone.dylib
    ""
    ""
    ""
)

if (false)
add_executable(imgui_ttf_font_binary_to_compressed_c
  imgui/misc/fonts/binary_to_compressed_c.cpp
)

function(embed_ttf infile symbolname outfile)
    message("embed_ttf ${infile} ${symbolname} ${outfile}")
    add_custom_command(
        OUTPUT
            ${outfile}
        COMMAND $<TARGET_FILE:imgui_ttf_font_binary_to_compressed_c> -u8 ${infile} ${symbolname} > ${outfile}
        DEPENDS
            ${infile}
            imgui_ttf_font_binary_to_compressed_c
    )
endfunction()

set(EMBEDDED_FONT_IN_PATH ${CMAKE_CURRENT_SOURCE_DIR}/imgui/misc/fonts)
set(EMBEDDED_FONT_PATH ${CMAKE_CURRENT_BINARY_DIR}/generated/imgui/fonts)

file(MAKE_DIRECTORY ${EMBEDDED_FONT_PATH})

embed_ttf(${EMBEDDED_FONT_IN_PATH}/Cousine-Regular.ttf cousine_regular_ttf
  ${EMBEDDED_FONT_PATH}/cousine_regular_ttf.c
)

embed_ttf(${EMBEDDED_FONT_IN_PATH}/DroidSans.ttf droid_sans_ttf
  ${EMBEDDED_FONT_PATH}/droid_sans_ttf.c
)

embed_ttf(${EMBEDDED_FONT_IN_PATH}/Karla-Regular.ttf karla_regular_ttf
  ${EMBEDDED_FONT_PATH}/karla_regular_ttf.c
)

embed_ttf(${EMBEDDED_FONT_IN_PATH}/ProggyClean.ttf proggy_clean_ttf
  ${EMBEDDED_FONT_PATH}/proggy_clean_ttf.c
)

embed_ttf(${EMBEDDED_FONT_IN_PATH}/ProggyTiny.ttf proggy_tiny_ttf
  ${EMBEDDED_FONT_PATH}/proggy_tiny_ttf.c
)

embed_ttf(${EMBEDDED_FONT_IN_PATH}/Roboto-Medium.ttf roboto_medium_ttf
  ${EMBEDDED_FONT_PATH}/roboto_medium_ttf.c
)

add_library(imgui_fonts
  ${EMBEDDED_FONT_PATH}/cousine_regular_ttf.c
  ${EMBEDDED_FONT_PATH}/droid_sans_ttf.c
  ${EMBEDDED_FONT_PATH}/karla_regular_ttf.c
  ${EMBEDDED_FONT_PATH}/proggy_clean_ttf.c
  ${EMBEDDED_FONT_PATH}/proggy_tiny_ttf.c
  ${EMBEDDED_FONT_PATH}/roboto_medium_ttf.c
)
install(TARGETS imgui_fonts DESTINATION lib)

add_library(imgui
  imgui/imgui.cpp
  imgui/imgui_draw.cpp
  imgui/imgui_tables.cpp
  imgui/imgui_widgets.cpp
  imgui/misc/freetype/imgui_freetype.cpp
)
target_include_directories(imgui PUBLIC imgui imgui/misc/freetype)
target_link_libraries(imgui PUBLIC imgui_fonts freetype harfbuzz)
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
endif()
