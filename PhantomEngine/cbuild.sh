mkdir -p build
pushd build
# cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake -DCMAKE_OSX_ARCHITECTURES=x86_64 -DCMAKE_BUILD_TYPE=Debug -G "Xcode" ..
# make 
popd