set -e -o pipefail

if $(am --help 2>&1 | grep -q -i "to-intent-uri") ; then
  echo "Android detected"
  if [[ -d /data/data/com.termux/files/usr ]] ; then
    echo "Termux shell detected, building apk"
    exec ./build_termux.sh
  else
    echo "Non-Termux shell detected, build might fail"
    echo "building..."
    export CC=clang
    export CXX=clang++
    cmake -DCMAKE_BUILD_TYPE=Release -S . -B build
  fi
elif [[ -d /data/data/com.termux.nix/files/usr ]] ; then
  echo "Android Termux Nix shell detected"
  echo "building..."
  export CC=clang
  export CXX=clang++
  cmake -DCMAKE_BUILD_TYPE=Release -DTERMUX_NIX=1 -S . -B build
else
  echo "Non-Android shell detected"
  echo "building..."
  export CC=clang
  export CXX=clang++
  cmake -DCMAKE_BUILD_TYPE=Release -S . -B build
fi
cmake --build build
cmake --install build --prefix=$(pwd)/build_install
echo "built"
#ls -l --color build/{install,install/*}
