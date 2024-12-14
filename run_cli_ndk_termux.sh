echo "Termux NDK shell detected, running normally"
#export LD_LIBRARY_PATH=$(pwd)/build/install/lib
export LD_LIBRARY_PATH=$(pwd)/android_sdk/android-ndk-r27b/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/lib/aarch64-linux-android:$LD_LIBRARY_PATH
./build_install/bin/emu_main_cli
