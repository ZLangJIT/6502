dir=$(pwd)

cd /data/data/com.termux/files/home/6502-OS

apt update
apt upgrade -y
apt install -y wget pkg-config automake libtool m4 gettext openjdk-21 cups
apt remove --autoremove -y python-pip
#apt install -y python-pip
#pip install meson
. /data/data/com.termux/files/usr/etc/profile
if [[ ! -e android_sdk ]] ; then
  mkdir android_sdk
  cd android_sdk
  NDK_URL=https://github.com/lzhiyong/termux-ndk/releases/download/android-ndk/android-ndk-r27b-aarch64.zip
  SDK_URL=https://github.com/lzhiyong/termux-ndk/releases/download/android-sdk/android-sdk-aarch64.zip
  JAVA_URL=https://github.com/lzhiyong/termux-ndk/releases/download/android-openjdk/openjdk-21.0.1-aarch64.zip
  if [[ ! -e $(basename $NDK_URL) ]] ; then
    echo "downloading ndk ..."
    wget $NDK_URL
  fi
  echo "extracting ndk ..."
  unzip $(basename $NDK_URL)
  if [[ -e $(basename $NDK_URL) ]] ; then
    rm $(basename $NDK_URL)
  fi
  if [[ ! -e $(basename $SDK_URL) ]] ; then
    echo "downloading sdk ..."
    wget $SDK_URL
  fi
  echo "extracting sdk ..."
  unzip $(basename $SDK_URL)
  if [[ -e $(basename $SDK_URL) ]] ; then
    rm $(basename $SDK_URL)
  fi
  cd ..
fi

export ANDROID_HOME=$(pwd)/android_sdk/android-sdk
export ANDROID_NDK=$(pwd)/android_sdk/android-ndk-r27b
export ANDROID_SDK=$ANDROID_HOME
export ANDROID_SDK_HOME=$ANDROID_SDK
export ANDROID_NDK_HOME=$ANDROID_NDK
export PATH=$ANDROID_SDK/build-tools/35.0.0:$PATH
export PATH=$ANDROID_SDK/cmdline-tools/latest/bin:$PATH
export PATH=$ANDROID_SDK/platform-tools:$PATH
export PATH=$ANDROID_SDK/cmake/bin:$PATH
export PATH=$ANDROID_NDK/toolchains/llvm/prebuilt/linux-aarch64/bin:$PATH
export PREFIX=$ANDROID_NDK/toolchains/llvm/prebuilt/linux-aarch64/sysroot/usr

# comment these out if python fails
export PYTHONHOME=$ANDROID_NDK/toolchains/llvm/prebuilt/linux-aarch64/python3
export PYTHON_PATH=$ANDROID_NDK/toolchains/llvm/prebuilt/linux-aarch64/python3/bin/python
export LD_LIBRARY_PATH=$ANDROID_NDK/toolchains/llvm/prebuilt/linux-aarch64/python3/lib
export PATH=$PYTHONHOME/bin:$PATH
# uncomment this if python fails
#apt install -y python

export CC=clang
export CXX=clang++

cd $dir
