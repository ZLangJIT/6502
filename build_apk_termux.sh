set -e -o pipefail

echo "[status] building..."
. ndk_profile.sh
apt install ed

cd apk
GRADLE_FILE=build.gradle.kts
if [[ ! -e app/keystore ]] ; then
  wget -q --show-progress https://github.com/ZLangJIT/6502/releases/download/keystore/keystore -O app/keystore
fi

if [[ ! -e version ]] ; then
  wget -q --show-progress https://github.com/ZLangJIT/6502/releases/download/version/version
fi
if [[ -e version.old ]] ; then
  echo "[status] restoring version"
  mv version.old version
fi
if [[ -e local.properties.old ]] ; then
  echo "[status] restoring local.properties"
  mv local.properties.old local.properties
fi
if [[ -e app/${GRADLE_FILE}.old ]] ; then
  echo "[status] restoring app/${GRADLE_FILE}"
  mv app/${GRADLE_FILE}.old app/${GRADLE_FILE}
fi
mv version version.old
cp local.properties local.properties.old
cp app/${GRADLE_FILE} app/${GRADLE_FILE}.old

echo "[status] incrementing version from $(cat version.old) -> $(( $(cat version.old) + 1 ))"
printf "$(( $(cat version.old) + 1 ))" > version
printf '%s\n' ",s@GRADLE_VERSION_CODE@$(cat version)@g" w q | ed app/${GRADLE_FILE} || true
printf '%s\n' ",s@GRADLE_VERSION_STRING@version $(cat version) - https://github.com/ZLangJIT/6502/commits/$(git log -n 1 --format="%H")@g" w q | ed app/${GRADLE_FILE} || true
printf '%s\n' ",s@NDK_DIRECTORY@$ANDROID_NDK@g" w q | ed app/${GRADLE_FILE} || true
printf '%s\n' ",s@CMAKE_DIRECTORY@$ANDROID_SDK/cmake@g" w q | ed local.properties || true

chmod +x gradlew
echo "[status] GRADLE: configuring ..."
if ! ./gradlew build --dry-run --console rich --configuration-cache --build-cache ; then
  echo "[failed] cleaning up..."
  echo "[status] restoring version"
  mv version.old version
  echo "[status] restoring local.properties"
  mv local.properties.old local.properties
  echo "[status] restoring app/${GRADLE_FILE}"
  mv app/${GRADLE_FILE}.old app/${GRADLE_FILE}
  exit 1
fi

echo "[status] patching .jar aapt2 ..."
find ~/.gradle -name 'aapt2-*-linux.jar' -type f | xargs -I{} jar -uvf {} -C $ANDROID_SDK_HOME/build-tools/35.0.0 aapt2 || true

echo "[status] GRADLE: building ..."
if ! ./gradlew assemble --console rich --configuration-cache --build-cache ; then
  echo "[failed] cleaning up..."
  echo "[status] restoring version"
  mv version.old version
  echo "[status] restoring local.properties"
  mv local.properties.old local.properties
  echo "[status] restoring app/${GRADLE_FILE}"
  mv app/${GRADLE_FILE}.old app/${GRADLE_FILE}
  exit 1
fi

echo "[success] cleaning up..."
echo "[status] making version $(cat version.old) current"
cp version version.old
echo "[status] restoring local.properties"
mv local.properties.old local.properties
echo "[status] restoring app/${GRADLE_FILE}"
mv app/${GRADLE_FILE}.old app/${GRADLE_FILE}
cd ..
