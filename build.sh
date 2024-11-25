set -e -o pipefail

cd vrEmu6502
echo "building..."
cmake -DCMAKE_BUILD_TYPE=Release -S . -B build
cmake --build build
cmake --install build --prefix=$(pwd)/build/install
echo "built"
ls -l --color
ls -l --color build/install
