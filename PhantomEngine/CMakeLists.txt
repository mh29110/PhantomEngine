cmake_minimum_required (VERSION 3.1)
set (CMAKE_C_STANDARD 11)
set (CMAKE_CXX_STANDARD 11)
project (PhantomEngine)
include_directories("${PROJECT_SOURCE_DIR}/PhantomCore")
include_directories("${PROJECT_SOURCE_DIR}/Dependencies/GLFW/include")
link_directories("${PROJECT_SOURCE_DIR}/Dependencies/GLFW/lib-vc2015")

link_libraries("glfw3.lib")

add_subdirectory(PhantomCore)
add_subdirectory(sample)
