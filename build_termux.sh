set -e -o pipefail

echo "building..."
apt update
apt upgrade
apt install wget ed
apt install openjdk-21 cups
. $PREFIX/etc/profile
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
#export PYTHONHOME=$ANDROID_NDK/toolchains/llvm/prebuilt/linux-aarch64/python3
#export LD_LIBRARY_PATH=$ANDROID_NDK/toolchains/llvm/prebuilt/linux-aarch64/python3/lib
export PATH=$ANDROID_SDK/build-tools/35.0.0:$PATH
export PATH=$ANDROID_SDK/cmdline-tools/latest/bin:$PATH
export PATH=$ANDROID_SDK/platform-tools:$PATH
export PATH=$ANDROID_SDK/cmake/bin:$PATH
export PATH=$ANDROID_NDK/toolchains/llvm/prebuilt/linux-aarch64/bin:$PATH
#export PATH=$JAVA_HOME/bin:$PATH

cd apk
GRADLE_FILE=build.gradle.kts
if [[ ! -e app/keystore ]] ; then
  wget -q --show-progress https://github.com/ZLangJIT/6502/releases/download/keystore/keystore -O app/keystore
fi

if [[ ! -e version ]] ; then
  wget -q --show-progress https://github.com/ZLangJIT/6502/releases/download/version/version
fi
if [[ -e version.old ]] ; then
  mv version.old version
fi
if [[ -e local.properties.old ]] ; then
  mv local.properties.old local.properties
fi
if [[ -e app/${GRADLE_FILE}.old ]] ; then
  mv app/${GRADLE_FILE}.old app/${GRADLE_FILE}
fi
mv version version_old
cp local.properties local.properties.old
cp app/${GRADLE_FILE} app/${GRADLE_FILE}.old

printf "$(( $(cat version_old) + 1 ))" > version
printf '%s\n' ",s@GRADLE_VERSION_CODE@$(cat version)@g" w q | ed app/${GRADLE_FILE} || true
printf '%s\n' ",s@GRADLE_VERSION_STRING@version $(cat version) - https://github.com/ZLangJIT/6502/commits/$(git log -n 1 --format="%H")@g" w q | ed app/${GRADLE_FILE} || true
printf '%s\n' ",s@NDK_DIRECTORY@$ANDROID_NDK@g" w q | ed app/${GRADLE_FILE} || true
printf '%s\n' ",s@CMAKE_DIRECTORY@$ANDROID_SDK/cmake@g" w q | ed local.properties || true

chmod +x gradlew
echo "GRADLE: configuring ..."
if ! ./gradlew build --dry-run --console rich --configuration-cache --build-cache ; then
  echo "cleaning up..."
  mv version_old version
  mv local.properties.old local.properties
  mv app/${GRADLE_FILE}.old app/${GRADLE_FILE}
  exit 1
fi
echo "patching .jar aapt2 ..."
find ~/.gradle -name 'aapt2-*-linux.jar' -type f | xargs -I{} jar -uvf {} -C $ANDROID_SDK_HOME/build-tools/35.0.0 aapt2
echo "GRADLE: building ..."
if ! ./gradlew build --console rich --configuration-cache --build-cache ; then
  echo "cleaning up..."
  mv version_old version
  mv local.properties.old local.properties
  mv app/${GRADLE_FILE}.old app/${GRADLE_FILE}
  exit 1
fi
echo "cleaning up..."
mv version_old version
mv local.properties.old local.properties
mv app/${GRADLE_FILE}.old app/${GRADLE_FILE}
cd ..
