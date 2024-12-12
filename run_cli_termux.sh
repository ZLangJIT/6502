#LD_LIBRARY_PATH=$(pwd)/build/install/lib ./build/install/bin/emu_main_cli
cd ./apk/app/build/intermediates/merged_native_libs/release/mergeReleaseNativeLibs/out/lib/arm64-v8a
chmod +x ./executable__*
ls -l -h --color
./executable__emu_main_cli.so
