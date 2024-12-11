set -e -o pipefail

echo "building..."
export CC=clang
export CXX=clang++

if $(am --help 2>&1 | grep -q -i "to-intent-uri") ; then
  echo "Android detected"
  if [[ -d /data/data/com.termux/files/usr ]] ; then
    echo "Termux shell detected"
    apt update
    apt upgrade
    #apt install cmake clang mesa-dev
    apt install wget
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
      if [[ ! -e $(basename $JAVA_URL) ]] ; then
        echo "downloading java ..."
        wget $JAVA_URL
      fi
      echo "extracting java ..."
      unzip $(basename $JAVA_URL)
      if [[ -e $(basename $JAVA_URL) ]] ; then
        rm $(basename $JAVA_URL)
      fi
      cd ..
    fi
    export JAVA_HOME=$(pwd)/android_sdk/java
    export ANDROID_SDK_HOME=$(pwd)/android_sdk/android-sdk
    export ANDROID_NDK_HOME=$(pwd)/android_sdk/android-ndk-r27b
    export PYTHONHOME=$(ANDROID_NDK_HOME)/toolchains/llvm/prebuilt/linux-aarch64/python3
    export LD_LIBRARY_PATH=$(ANDROID_NDK_HOME)/toolchains/llvm/prebuilt/linux-aarch64/python3/lib
    cmake -DCMAKE_BUILD_TYPE=Release -DTERMUX=1 -S . -B build
  else
    echo "Non-Termux shell detected, build might fail"
    cmake -DCMAKE_BUILD_TYPE=Release -S . -B build
  fi
elif [[ -d /data/data/com.termux.nix/files/usr ]] ; then
  echo "Android Termux Nix shell detected"
  cmake -DCMAKE_BUILD_TYPE=Release -DTERMUX_NIX=1 -S . -B build
else
  echo "Non-Android shell detected"
  cmake -DCMAKE_BUILD_TYPE=Release -S . -B build
fi
cmake --build build
cmake --install build --prefix=$(pwd)/build/install
echo "built"
#ls -l --color build/{install,install/*}
