@echo off
:: # git submodule update --init Dependencies\src\libjpeg
mkdir Dependencies\build\libjpeg
pushd Dependencies\build\libjpeg
:: rm -rf *
cmake -DCMAKE_INSTALL_PREFIX=..\..\Windows\ -G "Visual Studio 15 2017" ..\..\src\libjpeg
cmake --build . --config debug --target install
popd

pause