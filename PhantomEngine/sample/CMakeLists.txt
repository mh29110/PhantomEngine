# 生成可执行文件
add_executable (sample main.cpp  )


if(OS_WINDOWS)

	target_link_libraries(  sample 
						)
	
elseif(OS_MACOS)

    target_link_libraries(sample  
                        )
endif()

# target_include_directories(sample PRIVATE "${PROJECT_SOURCE_DIR}/Dependencies/src/glad/include")
