add_library(OpenGLRHI
        OpenGLGraphicsManager.cpp
        ${PROJECT_SOURCE_DIR}/Dependencies/src/glad/src/glad_wgl.c
)
target_include_directories(OpenGLRHI PRIVATE "${PROJECT_SOURCE_DIR}/Dependencies/src/glad/include")

