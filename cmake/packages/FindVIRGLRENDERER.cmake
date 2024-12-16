# Try to find the VIRGLRENDERER library
#
# If successful, the following variables will be defined:
# VIRGLRENDERER_INCLUDE_DIR
# VIRGLRENDERER_LIBRARIES
# VIRGLRENDERER_FOUND
#
# additionally exposes the following target:
# virglrenderer

find_package(EPOXY REQUIRED)

find_package(PkgConfig QUIET)
pkg_check_modules(PC_GLOB QUIET VIRGLRENDERER)

set(CMAKE_FIND_DEBUG_MODE FALSE)

find_path(VIRGLRENDERER_INCLUDE_DIRS NAMES virgl/virgl-version.h
  PATHS ${LLVM_BUILD_ROOT__ROOTFS}/include ${LLVM_BUILD_ROOT__ROOTFS}/usr/include
  NO_DEFAULT_PATH
  NO_PACKAGE_ROOT_PATH
  NO_CMAKE_PATH
  NO_CMAKE_ENVIRONMENT_PATH
  NO_SYSTEM_ENVIRONMENT_PATH
  NO_CMAKE_SYSTEM_PATH
  NO_CMAKE_FIND_ROOT_PATH
)
find_library(VIRGLRENDERER_LIBRARIES NAMES libvirglrenderer.so
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

if(VIRGLRENDERER_INCLUDE_DIRS AND EXISTS "${VIRGLRENDERER_INCLUDE_DIRS}/virgl/virgl-version.h" AND EXISTS "${VIRGLRENDERER_INCLUDE_DIRS}/virgl/virglrenderer.h")
  FILE(STRINGS "${VIRGLRENDERER_INCLUDE_DIRS}/virgl/virgl-version.h" VIRGLRENDERER_version_major_str REGEX "^#define[ \t]+VIRGL_MAJOR_VERSION[ \t]+\(.+\)")
  FILE(STRINGS "${VIRGLRENDERER_INCLUDE_DIRS}/virgl/virgl-version.h" VIRGLRENDERER_version_minor_str REGEX "^#define[ \t]+VIRGL_MINOR_VERSION[ \t]+\(.+\)")
  FILE(STRINGS "${VIRGLRENDERER_INCLUDE_DIRS}/virgl/virgl-version.h" VIRGLRENDERER_version_micro_str REGEX "^#define[ \t]+VIRGL_MICRO_VERSION[ \t]+\(.+\)")

  STRING(REGEX REPLACE "^#define[ \t]+VIRGL_MAJOR_VERSION[ \t]+\\\(([^\)]+)\\\).*" "\\1" VIRGL_MAJOR_VERSION "${VIRGLRENDERER_version_major_str}")
  STRING(REGEX REPLACE "^#define[ \t]+VIRGL_MINOR_VERSION[ \t]+\\\(([^\)]+)\\\).*" "\\1" VIRGL_MINOR_VERSION "${VIRGLRENDERER_version_minor_str}")
  STRING(REGEX REPLACE "^#define[ \t]+VIRGL_MICRO_VERSION[ \t]+\\\(([^\)]+)\\\).*" "\\1" VIRGL_MICRO_VERSION "${VIRGLRENDERER_version_micro_str}")
  
  STRING(CONCAT VIRGLRENDERER_VERSION_STRING ${VIRGL_MAJOR_VERSION} "." ${VIRGL_MINOR_VERSION} "." ${VIRGL_MICRO_VERSION})
else()
  set(VIRGLRENDERER_INCLUDE_DIRS "")
  set(VIRGLRENDERER_LIBRARIES "")
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(VIRGLRENDERER
                                  FOUND_VAR
                                    VIRGLRENDERER_FOUND
                                  REQUIRED_VARS
                                    VIRGLRENDERER_INCLUDE_DIRS
                                    VIRGLRENDERER_LIBRARIES
                                  VERSION_VAR
                                    VIRGLRENDERER_VERSION_STRING)
mark_as_advanced(VIRGLRENDERER_INCLUDE_DIRS VIRGLRENDERER_LIBRARIES)

message(STATUS "VIRGLRENDERER: found :        ${VIRGLRENDERER_FOUND}")
message(STATUS "VIRGLRENDERER: include_dirs : ${VIRGLRENDERER_INCLUDE_DIRS}")
message(STATUS "VIRGLRENDERER: lib :          ${VIRGLRENDERER_LIBRARIES}")
message(STATUS "VIRGLRENDERER: version :      ${VIRGLRENDERER_VERSION_STRING}")

if (VIRGLRENDERER_FOUND AND NOT TARGET virglrenderer)
  add_library(virglrenderer UNKNOWN IMPORTED)
  set_target_properties(virglrenderer PROPERTIES IMPORTED_LOCATION ${VIRGLRENDERER_LIBRARIES})
  target_include_directories(virglrenderer INTERFACE ${VIRGLRENDERER_INCLUDE_DIRS})
  target_compile_definitions(virglrenderer INTERFACE HAVE_VIRGL_VERSION_H)
  target_compile_definitions(virglrenderer INTERFACE HAVE_VIRGLRENDERER_H)
  target_link_libraries(virglrenderer INTERFACE epoxy)
  set(VIRGLRENDERER_TARGET virglrenderer)
endif()
