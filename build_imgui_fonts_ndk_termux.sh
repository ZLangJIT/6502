set -e -o pipefail

echo "building..."
. ndk_profile.sh

cd imgui_fonts

if [[ -d generated ]] ; then
  echo "removing generated fonts"
  rm -rf generated
  echo "removed generated fonts"
fi

cmake -DCMAKE_BUILD_TYPE=Release -S . -B build \
    -DCMAKE_TOOLCHAIN_FILE="${ANDROID_NDK}/build/cmake/android.toolchain.cmake" \
    -DANDROID_ABI="arm64-v8a" \
    -DANDROID_PLATFORM=android-35 \
    -DTERMUX=1 \
    -DBUILD_SHARED_LIBS=OFF

cmake --build build

rm -rf build

echo "built"
