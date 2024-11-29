cmake_minimum_required(VERSION 3.16)

include(CheckSymbolExists)

add_library(vrEmu6502)
target_sources(vrEmu6502 PRIVATE vrEmu6502.c)
target_sources(vrEmu6502 PUBLIC vrEmu6502.h)

if (BUILD_SHARED_LIBS)
  if (WIN32)
    target_compile_definitions(vrEmu6502 PUBLIC -DVR_EMU_6502_COMPILING_DLL)
  endif()
else()
  target_compile_definitions(vrEmu6502 PUBLIC -DVR_EMU_6502_STATIC)
endif()

target_include_directories(vrEmu6502 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

install(FILES vrEmu6502.h DESTINATION include)
install(TARGETS vrEmu6502 DESTINATION lib)
