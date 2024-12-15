set -e -o pipefail

apt update
apt upgrade -y
apt install -y python patchelf autoconf

export ANDROID_HOME=$(pwd)/android_sdk/android-sdk
export ANDROID_NDK=$(pwd)/android_sdk/android-ndk-r27b
export ANDROID_SDK=$ANDROID_HOME
export ANDROID_SDK_HOME=$ANDROID_SDK
export ANDROID_NDK_HOME=$ANDROID_NDK
export PATH=$ANDROID_SDK/build-tools/35.0.0:$PATH
export PATH=$ANDROID_SDK/cmdline-tools/latest/bin:$PATH
export PATH=$ANDROID_SDK/platform-tools:$PATH
export PATH=$ANDROID_SDK/cmake/bin:$PATH
export PATH=$ANDROID_NDK/prebuilt/linux-x86_64/bin:$PATH
export PATH=$ANDROID_NDK/toolchains/llvm/prebuilt/linux-aarch64/bin:$PATH
export PREFIX=$ANDROID_NDK/toolchains/llvm/prebuilt/linux-aarch64/sysroot/usr

pip install hexabyte
