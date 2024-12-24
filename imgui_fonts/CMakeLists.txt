cmake_minimum_required(VERSION 3.16)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

project(imgui_fonts)

set(EMBEDDED_FONT_IN_PATH ${CMAKE_CURRENT_SOURCE_DIR}/fonts)
set(EMBEDDED_FONT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/generated)

if (NOT EXISTS ${EMBEDDED_FONT_PATH})
  function(embed_ttf outdir infile symbolname)
      message("embed_ttf ${outdir} ${infile} > ${symbolname}")
      add_custom_command(
          OUTPUT ${outdir}/${symbolname}.c
          COMMAND $<TARGET_FILE:imgui_ttf_font_binary_to_compressed_c> -u8 ${infile} ${symbolname} > ${outdir}/${symbolname}.c
          DEPENDS ${infile} imgui_ttf_font_binary_to_compressed_c
      )
  endfunction()
  add_executable(imgui_ttf_font_binary_to_compressed_c fonts/binary_to_compressed_c.cpp)
  file(MAKE_DIRECTORY ${EMBEDDED_FONT_PATH})
  embed_ttf(${EMBEDDED_FONT_PATH} ${EMBEDDED_FONT_IN_PATH}/Cousine-Regular.ttf cousine_regular_ttf)
  embed_ttf(${EMBEDDED_FONT_PATH} ${EMBEDDED_FONT_IN_PATH}/DroidSans.ttf droid_sans_ttf)
  embed_ttf(${EMBEDDED_FONT_PATH} ${EMBEDDED_FONT_IN_PATH}/Karla-Regular.ttf karla_regular_ttf)
  embed_ttf(${EMBEDDED_FONT_PATH} ${EMBEDDED_FONT_IN_PATH}/ProggyClean.ttf proggy_clean_ttf)
  embed_ttf(${EMBEDDED_FONT_PATH} ${EMBEDDED_FONT_IN_PATH}/ProggyTiny.ttf proggy_tiny_ttf)
  embed_ttf(${EMBEDDED_FONT_PATH} ${EMBEDDED_FONT_IN_PATH}/Roboto-Medium.ttf roboto_medium_ttf)
endif()

add_library(imgui_fonts
  ${EMBEDDED_FONT_PATH}/cousine_regular_ttf.c
  ${EMBEDDED_FONT_PATH}/droid_sans_ttf.c
  ${EMBEDDED_FONT_PATH}/karla_regular_ttf.c
  ${EMBEDDED_FONT_PATH}/proggy_clean_ttf.c
  ${EMBEDDED_FONT_PATH}/proggy_tiny_ttf.c
  ${EMBEDDED_FONT_PATH}/roboto_medium_ttf.c
)
install(TARGETS imgui_fonts DESTINATION lib)
