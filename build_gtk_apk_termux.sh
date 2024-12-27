set -e -o pipefail

echo "building..."
. ndk_profile.sh
apt install ed

cd Graphics-Tool-Kit
GRADLE_FILE=build.gradle
#.kts
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
find ~/.gradle -name 'aapt2-*-linux.jar' -type f | xargs -I{} jar -uvf {} -C $ANDROID_SDK_HOME/build-tools/35.0.0 aapt2 || true

echo "GRADLE: building ..."
if ! ./gradlew build --console rich --configuration-cache --build-cache ; then
  echo "cleaning up..."
  mv version_old version
  mv local.properties.old local.properties
  mv app/${GRADLE_FILE}.old app/${GRADLE_FILE}
  exit 1
fi

echo "cleaning up..."
mv local.properties.old local.properties
mv app/${GRADLE_FILE}.old app/${GRADLE_FILE}
cd ..
