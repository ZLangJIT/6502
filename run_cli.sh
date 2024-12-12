if $(am --help 2>&1 | grep -q -i "to-intent-uri") ; then
  echo "Android detected"
  if [[ -d /data/data/com.termux/files/usr ]] ; then
    echo "Termux shell detected, running from apk"
    exec ./run_cli_termux.sh
  fi
fi
echo "Non-Termux shell detected, running normally"
LD_LIBRARY_PATH=$(pwd)/build/install/lib ./build/install/bin/emu_main_cli
