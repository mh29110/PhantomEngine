#!/bin/bash
git submodule update --init Dependencies/src/opengex
mkdir -p Dependencies/build/opengex
cd Dependencies/build/opengex
cmake -DCMAKE_INSTALL_PREFIX=../.. ../../src/opengex
cmake --build . --config release --target install

