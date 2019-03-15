
if(OS_WINDOWS)
    
    add_library(OpenGLRHI
        OpenGLGraphicsManager.cpp
        ${PROJECT_SOURCE_DIR}/Dependencies/src/glad/src/glad_wgl.c
	)

elseif(OS_MACOS)
	add_library(OpenGLRHI
        OpenGLGraphicsManager.cpp
        ${PROJECT_SOURCE_DIR}/Dependencies/src/glad/src/glad.c
	)
    
endif(OS_WINDOWS)

target_include_directories(OpenGLRHI PRIVATE "${PROJECT_SOURCE_DIR}/Dependencies/src/glad/include")

