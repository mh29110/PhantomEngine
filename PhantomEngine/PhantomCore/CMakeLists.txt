# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量


set(DIR_LIB_SRCS "./src/")
file (GLOB_RECURSE  SOURCES 
					"${DIR_LIB_SRCS}/*.h"
					"${DIR_LIB_SRCS}/*.cpp"
					${PROJECT_SOURCE_DIR}/Dependencies/src/glad/src/glad.c
					)
message("My source files: " ${SOURCES})

# 生成链接库
add_library (PhantomCore 
	${SOURCES}
)
target_include_directories(PhantomCore PRIVATE "${PROJECT_SOURCE_DIR}/Dependencies/src/glad/include")
