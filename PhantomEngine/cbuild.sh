mkdir -p build
pushd build
cmake .. -DCMAKE_BUILD_TYPE=Debug

make 
popd