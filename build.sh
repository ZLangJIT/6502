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
    if [[ ! -e ndk ]] ; then
      echo "downloading ndk ..."
      wget https://github.com/lzhiyong/termux-ndk/releases/download/android-ndk/android-ndk-r27b-aarch64.zip
      mkdir ndk
      cd ndk
      echo "extracting ndk ..."
      unzip android-ndk-r27b-aarch64.zip
      cd ..
    fi
    export ANDROID_NDK_HOME=$(pwd)/ndk
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
