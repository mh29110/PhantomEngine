cmake_minimum_required (VERSION 3.1)
set (CMAKE_C_STANDARD 11)
set (CMAKE_CXX_STANDARD 11)

# Check platforms
if (CMAKE_HOST_WIN32)
    set(WINDOWS 1)
elseif(CMAKE_HOST_APPLE)
    set(MACOS 1)
elseif(CMAKE_HOST_UNIX)
    set(LINUX 1)
endif()

project (PhantomEngine)
include_directories("${PROJECT_SOURCE_DIR}/PhantomCore")
include_directories("${PROJECT_SOURCE_DIR}/Dependencies/GLFW/include")
include_directories("${PROJECT_SOURCE_DIR}/Dependencies/GLEW/include")


if(WINDOWS)
    link_directories("${PROJECT_SOURCE_DIR}/Dependencies/GLFW/lib-vc2015"
    				"${PROJECT_SOURCE_DIR}/Dependencies/GLEW/lib/Release/Win32")
   
elseif(MACOS)
	INCLUDE_DIRECTORIES ( /System/Library/Frameworks )
	FIND_LIBRARY(COCOA_LIBRARY Cocoa)
	# find_library(CoreFoundation_LIBRARY CoreFoundation)
	FIND_LIBRARY(IOKit_LIBRARY IOKit)
	FIND_LIBRARY(COREVIDEO_LIB NAMES CoreVideo)
    FIND_LIBRARY(OpenGL_LIBRARY OpenGL )

    MARK_AS_ADVANCED (COCOA_LIBRARY
    				IOKit_LIBRARY
    				COREVIDEO_LIB
                    OpenGL_LIBRARY)
    SET(EXTRA_LIBS ${COCOA_LIBRARY} ${IOKit_LIBRARY} ${COREVIDEO_LIB} ${OpenGL_LIBRARY})

    link_directories("${PROJECT_SOURCE_DIR}/Dependencies/GLFW/lib-mac")
    
    MESSAGE( STATUS "message = ${OPENGL_INCLUDE_DIR}.")
endif(WINDOWS)

add_subdirectory(PhantomCore)
add_subdirectory(sample)



