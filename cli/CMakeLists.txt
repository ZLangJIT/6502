cmake_minimum_required(VERSION 3.18.8)

include(CheckSymbolExists)

if(UNIX AND ANDROID AND NOT TERMUX)
  add_executable(executable__x65.so x65/x65.cpp)
else()
  add_executable(x65 x65/x65.cpp)
  install(TARGETS x65 DESTINATION bin)
endif()

#add_subdirectory(ftxui)

#add_library(ui_cxx ui.cpp)
#target_link_libraries(ui_cxx PRIVATE ftxui::screen ftxui::dom ftxui::component handlemap)

#add_library(ui ui.c)
#target_link_libraries(ui PRIVATE ui_cxx handlemap)

add_library(common INTERFACE)
target_link_libraries(common INTERFACE
  vrEmu6502
  keystone
  capstone
  imgui
  nanovg
  handlemap
  simplelock
  simplethread
)

if(UNIX AND ANDROID AND NOT TERMUX)
  add_executable(executable__emu_main_cli.so main2.cpp)
  target_link_libraries(executable__emu_main_cli.so PRIVATE common EGL GLESv3 log android nativewindow)
elseif(UNIX AND ANDROID AND TERMUX)
  add_executable(emu_main_cli main.cpp)
  target_link_libraries(emu_main_cli PRIVATE common EGL GLESv3 log android nativewindow)
  install(TARGETS emu_main_cli DESTINATION bin)
elseif(UNIX AND NOT ANDROID)
  add_executable(emu_main_cli main2.cpp)
  target_link_libraries(emu_main_cli PRIVATE common EGL GLESv3)
  install(TARGETS emu_main_cli DESTINATION bin)
elseif(WINDOWS)
  add_executable(emu_main_cli main2.cpp)
  target_link_libraries(emu_main_cli PRIVATE common EGL GLESv3)
  install(TARGETS emu_main_cli DESTINATION bin)
elseif(APPLE)
  add_executable(emu_main_cli main2.cpp)
  target_link_libraries(emu_main_cli PRIVATE common EGL GLESv3)
  install(TARGETS emu_main_cli DESTINATION bin)
else()
  message(STATUS_FATAL "unknown platform")
endif()
