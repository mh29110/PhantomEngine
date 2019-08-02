mkdir build
pushd build
#cmake -G "Visual Studio 15 2017 Win64" -Thost=x64 ..
cmake -DCMAKE_BUILD_TYPE=Debug ..
popd
PAUSE