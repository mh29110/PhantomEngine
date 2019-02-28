# 生成可执行文件
add_executable (sample main.cpp)



if(WINDOWS)
	# copy dll
    add_custom_command(TARGET sample 
    POST_BUILD COMMAND 
    ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/Dependencies/GLEW/bin/Release/Win32" "$<TARGET_FILE_DIR:sample>")

	target_link_libraries(  sample 
							PhantomCore 
							opengl32.lib 
							glew32.lib
							glfw3.lib)

elseif(MACOS)

    target_link_libraries(sample  
    	PhantomCore 
    	${OPENGL_LIBRARIES} 
        libGLEW.a
    	${EXTRA_LIBS}
    	libglfw3.a
    )
endif()
