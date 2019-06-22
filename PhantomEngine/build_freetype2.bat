@echo off
# git submodule update --init Dependencies\src\freetype2100
mkdir Dependencies\build\freetype2100
pushd Dependencies\build\freetype2100
rm -rf *
cmake -DCMAKE_INSTALL_PREFIX=..\..\Windows\ -G "Visual Studio 15 2017" ..\..\src\freetype2100
# cmake -DCMAKE_INSTALL_PREFIX=..\..\Windows\ -G "Visual Studio 15 2017 Win64" -Thost=x64 ..\..\src\freetype2100
cmake --build . --config debug --target install
popd

# 注意： 这里freeType2 install后是放在对应Platform下<Windows>的freetype2文件夹中，
# 由于FreeType中使用了特殊的宏定义所以手动把Include文件夹向上<..>提了一级。
# http://www.voidcn.com/article/p-gmewnpkh-yn.html
pause