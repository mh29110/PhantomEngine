# git submodule update --init Dependencies\src\libjpeg
mkdir Dependencies/build/libjpeg
pushd Dependencies/build/libjpeg
# rm -rf *
cmake -DCMAKE_INSTALL_PREFIX=../../Darwin  ../../src/libjpeg
cmake --build . --config release --target install
popd

pause


