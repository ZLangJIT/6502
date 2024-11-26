cmake_minimum_required(VERSION 3.18.8)

include(CheckSymbolExists)

add_library(emu_main)
target_sources(emu_main PRIVATE main.cpp)
target_link_libraries(emu_main PRIVATE vrEmu6502)
if (NOT ANDROID)
  install(FILES emu.h DESTINATION include)
  install(TARGETS emu_main DESTINATION lib)
endif()
