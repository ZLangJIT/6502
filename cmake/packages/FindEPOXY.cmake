# Try to find the EPOXY library
#
# If successful, the following variables will be defined:
# EPOXY_INCLUDE_DIR
# EPOXY_LIBRARIES
# EPOXY_FOUND
#
# additionally exposes the following target:
# epoxy

find_package(PkgConfig QUIET)
pkg_check_modules(PC_GLOB QUIET epoxy)

set(CMAKE_FIND_DEBUG_MODE TRUE)

find_path(EPOXY_INCLUDE_DIRS NAMES epoxy/gl.h epoxy/egl.h
  PATHS ${LLVM_BUILD_ROOT__ROOTFS}/include ${LLVM_BUILD_ROOT__ROOTFS}/usr/include
  NO_DEFAULT_PATH
  NO_PACKAGE_ROOT_PATH
  NO_CMAKE_PATH
  NO_CMAKE_ENVIRONMENT_PATH
  NO_SYSTEM_ENVIRONMENT_PATH
  NO_CMAKE_SYSTEM_PATH
  NO_CMAKE_FIND_ROOT_PATH
)
find_library(EPOXY_LIBRARIES NAMES libepoxy.so
  PATHS ${LLVM_BUILD_ROOT__ROOTFS}/lib ${LLVM_BUILD_ROOT__ROOTFS}/usr/lib
  NO_DEFAULT_PATH
  NO_PACKAGE_ROOT_PATH
  NO_CMAKE_PATH
  NO_CMAKE_ENVIRONMENT_PATH
  NO_SYSTEM_ENVIRONMENT_PATH
  NO_CMAKE_SYSTEM_PATH
  NO_CMAKE_FIND_ROOT_PATH
)

set(CMAKE_FIND_DEBUG_MODE FALSE)

if(EPOXY_INCLUDE_DIRS AND (EXISTS "${EPOXY_INCLUDE_DIRS}/epoxy/gl.h" OR EXISTS "${EPOXY_INCLUDE_DIRS}/epoxy/egl.h"))
  set(EPOXY_VERSION_STRING "1.0")
else()
  set(EPOXY_INCLUDE_DIRS "")
  set(EPOXY_LIBRARIES "")
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(EPOXY
                                  FOUND_VAR
                                    EPOXY_FOUND
                                  REQUIRED_VARS
                                    EPOXY_INCLUDE_DIRS
                                    EPOXY_LIBRARIES
                                  VERSION_VAR
                                    EPOXY_VERSION_STRING)
mark_as_advanced(EPOXY_INCLUDE_DIRS EPOXY_LIBRARIES)

message(STATUS "EPOXY: found :        ${EPOXY_FOUND}")
message(STATUS "EPOXY: include_dirs : ${EPOXY_INCLUDE_DIRS}")
message(STATUS "EPOXY: lib :          ${EPOXY_LIBRARIES}")
message(STATUS "EPOXY: version :      ${EPOXY_VERSION_STRING}")

if (EPOXY_FOUND AND NOT TARGET epoxy)
  add_library(epoxy UNKNOWN IMPORTED)
  set_target_properties(epoxy PROPERTIES IMPORTED_LOCATION ${EPOXY_LIBRARIES})
  target_include_directories(epoxy INTERFACE ${EPOXY_INCLUDE_DIRS})
  if (EXISTS "${EPOXY_INCLUDE_DIRS}/epoxy/gl.h")
    target_compile_definitions(epoxy INTERFACE HAVE_EPOXY_GL_H)
  endif()
  if (EXISTS "${EPOXY_INCLUDE_DIRS}/epoxy/egl.h")
    target_compile_definitions(epoxy INTERFACE HAVE_EPOXY_EGL_H)
  endif()
  set(EPOXY_TARGET epoxy)
endif()
