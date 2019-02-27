set(HEADERS "${PROJECT_SOURCE_DIR}/PhantomCore/src/graphics/window.h")

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SAMPLE_SRCS 变量
aux_source_directory(. DIR_SAMPLE_SRCS)


# 生成可执行文件
add_executable (sample ${DIR_SAMPLE_SRCS} ${HEADERS})



if(WINDOWS)
	target_link_libraries(sample PhantomCore opengl32.lib glfw3.lib)

elseif(MACOS)
    target_link_libraries(sample  
    	PhantomCore 
    	${OPENGL_LIBRARIES} 
    	${EXTRA_LIBS}
    	libglfw3.a
    )
endif()
