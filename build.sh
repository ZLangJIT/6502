set -e -o pipefail

echo "building..."
export CC=clang
export CXX=clang++

if $(am --help 2>&1 | grep -q -i "to-intent-uri")
  then
    echo "Android detected"
    if [[ -d /data/data/com.termux/files/usr ]]
      then
        echo "Termux shell detected"
	cmake -DCMAKE_BUILD_TYPE=Release -DTERMUX=1 -S . -B build
    else
      cmake -DCMAKE_BUILD_TYPE=Release -S . -B build
    fi
else
  cmake -DCMAKE_BUILD_TYPE=Release -S . -B build
fi
cmake --build build
cmake --install build --prefix=$(pwd)/build/install
echo "built"
ls -l --color build/{install,install/*}
