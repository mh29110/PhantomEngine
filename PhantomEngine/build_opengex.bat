@echo off
git submodule update --init Dependencies\src\opengex
mkdir Dependencies\build\opengex
pushd Dependencies\build\opengex
rm -rf *
cmake -DCMAKE_INSTALL_PREFIX=..\..\ -G "Visual Studio 15 2017" ..\..\src\opengex
# cmake -DCMAKE_INSTALL_PREFIX=..\..\ -G "Visual Studio 15 2017 Win64" -Thost=x64 ..\..\src\opengex
cmake --build . --config debug --target install
popd

pause