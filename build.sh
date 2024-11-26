set -e -o pipefail

echo "building..."
export CC=clang
export CXX=clang++
cmake -DCMAKE_BUILD_TYPE=Release -S . -B build
cmake --build build
cmake --install build --prefix=$(pwd)/build/install
echo "built"
ls -l --color build/{install,install/*}
