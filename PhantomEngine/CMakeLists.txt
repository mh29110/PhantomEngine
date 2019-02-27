cmake_minimum_required (VERSION 3.1)
set (CMAKE_C_STANDARD 11)
set (CMAKE_CXX_STANDARD 11)
project (PhantomEngine)
include_directories("${PROJECT_SOURCE_DIR}/PhantomCore")

add_subdirectory(PhantomCore)
