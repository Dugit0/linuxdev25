rm -rf build
mkdir build && cd build
cmake -DENABLE_COVERAGE=ON -DBUILD_SHARED_LIBS=ON ..
cmake --build .
make coverage
