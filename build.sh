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
    apt install wget cmake
    if [[ ! -e android-ndk-r27b-aarch64.zip ]] ; then
      echo "downloading ndk ..."
      wget https://github.com/lzhiyong/termux-ndk/releases/download/android-ndk/android-ndk-r27b-aarch64.zip
    fi
    if [[ ! -e ndk ]] ; then
      mkdir ndk
      cd ndk
      echo "extracting ndk ..."
      unzip ../android-ndk-r27b-aarch64.zip
      if [[ -e ../android-ndk-r27b-aarch64.zip ]] ; then
        rm ../android-ndk-r27b-aarch64.zip
      fi
      cd ..
    fi
    export ANDROID_NDK_HOME=$(pwd)/ndk/android-ndk-r27b
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
