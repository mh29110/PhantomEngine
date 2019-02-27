set(HEADERS "${PROJECT_SOURCE_DIR}/PhantomCore/src/graphics/window.h")

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SAMPLE_SRCS 变量
aux_source_directory(. DIR_SAMPLE_SRCS)

# 生成可执行文件
add_executable (sample ${DIR_SAMPLE_SRCS} ${HEADERS})

target_link_libraries(sample glfw3.lib)
target_link_libraries(sample PhantomCore)
target_link_libraries(sample opengl32.lib)