set -e -o pipefail

apt install gradle wget ed aapt aapt2 android-tools apksigner d8 dex2jar xz-utils
. ~/../usr/etc/profile
if [[ ! -e android_sdk ]] ; then
  mkdir android_sdk
fi

export ANDROID_HOME=$(pwd)/android_sdk

if [[ ! -e android_sdk/tools ]] ; then
  if [[ -e tmp ]] ; then
    rm -rf tmp
  fi
  mkdir tmp
  cd tmp

  echo "downloading platform tools..."
  wget --no-verbose --show-progress https://github.com/AndroidIDEOfficial/androidide-tools/releases/download/v34.0.4/platform-tools-34.0.4-aarch64.tar.xz

  echo "downloading build tools..."
  wget --no-verbose --show-progress https://github.com/AndroidIDEOfficial/androidide-tools/releases/download/v34.0.4/build-tools-34.0.4-aarch64.tar.xz

  echo "downloading cmdline-tools..."
  wget --no-verbose --show-progress https://github.com/AndroidIDEOfficial/androidide-tools/releases/download/sdk/cmdline-tools.tar.xz

  echo "extracting platform tools..."
  tar -xf platform-tools-34.0.4-aarch64.tar.xz
  mv platform-tools ../android_sdk/platform-tools

  echo "extracting build tools..."
  tar -xf build-tools-34.0.4-aarch64.tar.xz
  mv build-tools ../android_sdk/build-tools

  echo "extracting cmdline-tools..."
  tar -xf cmdline-tools.tar.xz
  mv cmdline-tools/latest ../android_sdk/tools

  #echo "installing sdk cmdline-tools..."
  #yes | cmdline-tools/latest/bin/sdkmanager --verbose --install "cmdline-tools;latest" --sdk_root=$(pwd)/../android_sdk || true
  #rm -rf cmdline-tools

  export PATH=$ANDROID_HOME/tools/bin:$PATH

  cd ..
  rm -rf tmp
else
  export PATH=$ANDROID_HOME/tools/bin:$PATH
fi

echo "accepting all licenses"
yes | sdkmanager --licenses --sdk_root=$(pwd)/android_sdk > /dev/null 2>&1 || true

cd apk
if [[ ! -e app/keystore ]] ; then
  wget -q --show-progress https://github.com/ZLangJIT/6502/releases/download/keystore/keystore -O app/keystore
fi

if [[ ! -e version ]] ; then
  wget -q --show-progress https://github.com/ZLangJIT/6502/releases/download/version/version
fi
if [[ -e version.old ]] ; then
  mv version.old version
fi
if [[ -e app/build.gradle.kts.old ]] ; then
  mv app/build.gradle.kts.old app/build.gradle.kts
fi
mv version version_old
cp app/build.gradle.kts app/build.gradle.kts.old
printf "$(( $(cat version_old) + 1 ))" > version
printf '%s\n' ",s@GRADLE_VERSION_CODE@$(cat version)@g" w q | ed app/build.gradle.kts || true
printf '%s\n' ",s@GRADLE_VERSION_STRING@version $(cat version) - https://github.com/ZLangJIT/6502/commits/$(git log -n 1 --format="%H")@g" w q | ed app/build.gradle.kts || true
if ! ./gradlew build --console rich --configuration-cache --build-cache ; then
  mv version_old version
  mv app/build.gradle.kts.old app/build.gradle.kts
  exit 1
fi
cd ..

