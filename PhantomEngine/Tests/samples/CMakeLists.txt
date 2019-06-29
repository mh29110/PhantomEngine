# 生成可执行文件

set(DIR_SRCS "./src/")
file (GLOB_RECURSE  SOURCES 
					"${DIR_SRCS}/*.h"
					"${DIR_SRCS}/*.cpp"
					)
#message("My source files: " ${SOURCES})

add_executable (Zsample ${SOURCES}  )
