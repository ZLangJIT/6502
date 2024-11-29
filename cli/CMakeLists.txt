cmake_minimum_required(VERSION 3.18.8)

include(CheckSymbolExists)

add_executable(emu_main_cli)
target_sources(emu_main_cli PRIVATE main.cpp)
target_link_libraries(emu_main_cli PRIVATE emu_main EGL GLESv3)
install(TARGETS emu_main_cli DESTINATION bin)
