# 生成可执行文件
add_executable (sample main.cpp   ${PROJECT_SOURCE_DIR}/Dependencies/src/glad/src/glad.c)

find_package(OpenGL REQUIRED)
# copy resource to execute dir (debug directory)
add_custom_command(TARGET sample PRE_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory
${CMAKE_SOURCE_DIR}/assets   $<TARGET_FILE_DIR:sample>)


if(OS_WINDOWS)
	# copy dll
    #add_custom_command(TARGET sample 
    #POST_BUILD COMMAND 
    #${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/Dependencies/GLEW/bin/Release/Win32" "$<TARGET_FILE_DIR:sample>"
    #)

    # copy resource to execute dir (debug mode)
    add_custom_command(TARGET sample PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets   "${PROJECT_BINARY_DIR}/sample")

	target_link_libraries(  sample 
							PhantomCore 
							${OPENGL_LIBRARIES}
							glfw3.lib)
	
elseif(OS_MACOS)

    target_link_libraries(sample  
    	PhantomCore 
    	${OPENGL_LIBRARIES} 
        libc++.dylib
    	${EXTRA_LIBS}
    	libglfw3.a
    )
endif()

target_include_directories(sample PRIVATE "${PROJECT_SOURCE_DIR}/Dependencies/src/glad/include")
