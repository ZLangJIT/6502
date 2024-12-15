#!/bin/bash

## set ndk home
## NDK_HOME=

PWD=$(pwd)
ARCH_TARGETS="arm64-v8a"

SOURCE_PATH=${PWD}/keystone
BUILD_PATH=${PWD}/_keystone_builds_android

if [[ ! -d keystone ]] ; then
  git clone --depth=1 https://github.com/keystone-engine/keystone.git keystone
fi

for ARCH_TARGET in ${ARCH_TARGETS}
do
    TARGET_BUILD_PATH=${BUILD_PATH}/${ARCH_TARGET}/build
    echo "~: Building ${ARCH_TARGET} :~"
    echo "~: Path: ${TARGET_BUILD_PATH} :~"

    mkdir -p ${TARGET_BUILD_PATH}
    cd ${TARGET_BUILD_PATH}

    cmake -DBUILD_LIBS_ONLY=1 -DBUILD_SHARED_LIBS=0 ${SOURCE_PATH} -G "Unix Makefiles" \
    -DCMAKE_SYSTEM_NAME=Android \
    -DCMAKE_SYSTEM_VERSION=35 \
    -DCMAKE_ANDROID_NDK=${NDK_HOME} \
    -DCMAKE_ANDROID_ARCH_ABI=${ARCH_TARGET} \
    -DCMAKE_ANDROID_STL_TYPE=c++_static \
    -DCMAKE_BUILD_TYPE=Release

    make -j8

    cd -

    cp ${TARGET_BUILD_PATH}/llvm/lib/libkeystone.a ${BUILD_PATH}/${ARCH_TARGET}
    echo "Binary built ${BUILD_PATH}/${ARCH_TARGET}/libkeystone.a"
done


SOURCE_PATH=${PWD}/capstone
BUILD_PATH=${PWD}/_capstone_builds_android

if [[ ! -d capstone ]] ; then
  git clone --depth=1 https://github.com/capstone-engine/capstone capstone
fi

for ARCH_TARGET in ${ARCH_TARGETS}
do
    TARGET_BUILD_PATH=${BUILD_PATH}/${ARCH_TARGET}/build
    echo "~: Building ${ARCH_TARGET} :~"
    echo "~: Path: ${TARGET_BUILD_PATH} :~"

    mkdir -p ${TARGET_BUILD_PATH}
    cd ${TARGET_BUILD_PATH}

    cmake -DBUILD_LIBS_ONLY=1 -DBUILD_SHARED_LIBS=0 ${SOURCE_PATH} -G "Unix Makefiles" \
    -DCMAKE_SYSTEM_NAME=Android \
    -DCMAKE_SYSTEM_VERSION=35 \
    -DCMAKE_ANDROID_NDK=${NDK_HOME} \
    -DCMAKE_ANDROID_ARCH_ABI=${ARCH_TARGET} \
    -DCMAKE_ANDROID_STL_TYPE=c++_static \
    -DCMAKE_BUILD_TYPE=Release

    make -j8

    cd -

    cp ${TARGET_BUILD_PATH}/libcapstone.a ${BUILD_PATH}/${ARCH_TARGET}
    echo "Binary built ${BUILD_PATH}/${ARCH_TARGET}/libcapstone.a"
    cp ${TARGET_BUILD_PATH}/cstool ${BUILD_PATH}/${ARCH_TARGET}
    echo "Binary built ${BUILD_PATH}/${ARCH_TARGET}/cstool"
done
