cmake_minimum_required (VERSION 3.1)
set (CMAKE_C_STANDARD 11)
set (CMAKE_CXX_STANDARD 11)

# Check platforms
IF(UNIX)
    IF(APPLE)
        set(MYGE_TARGET_PLATFORM "Darwin")
        set(OS_MACOS 1)
    ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES Android)
        set(MYGE_TARGET_PLATFORM "Android")
        set(ANDROID 1)
        set(OS_ANDROID 1)
    ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
        set(MYGE_TARGET_PLATFORM "FreeBSD")
        include_directories("/usr/local/include")
        set(BSD 1)
        set(OS_BSD 1)
    ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES Emscripten)
        set(MYGE_TARGET_PLATFORM "Emscripten")
        set(WA 1)
        set(OS_WEBASSEMBLY 1)
        unset (USE_ISPC)
    ELSE(LINUX)
        set(MYGE_TARGET_PLATFORM "Linux")
        set(OS_LINUX 1)
    ENDIF(APPLE)
ELSEIF(WIN32)
    set(MYGE_TARGET_PLATFORM "Windows")
        set(OS_WINDOWS 1)
ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES Psp2)
    set(MYGE_TARGET_PLATFORM "PSP2")
    set(PSP2 1)
    set(OS_PSP2 1)
ENDIF(UNIX)

IF (CMAKE_BUILD_TYPE STREQUAL Debug)
    ADD_DEFINITIONS(-D_DEBUG)
ENDIF()

project (PhantomEngine)
include_directories("${PROJECT_SOURCE_DIR}/PhantomCore/src/common")
include_directories("${PROJECT_SOURCE_DIR}/PhantomCore/src/graphics")
include_directories("${PROJECT_SOURCE_DIR}/PhantomCore/src/interface")
include_directories("${PROJECT_SOURCE_DIR}/PhantomCore/src/maths")
include_directories("${PROJECT_SOURCE_DIR}/PhantomCore/src/utils")
include_directories("${PROJECT_SOURCE_DIR}/PhantomCore/src/parser")
include_directories("${PROJECT_SOURCE_DIR}/Dependencies/GLFW/include")
include_directories("${PROJECT_SOURCE_DIR}/Platform/${MYGE_TARGET_PLATFORM}") # 根据平台来决定include
include_directories("${PROJECT_SOURCE_DIR}/Dependencies/src/glad/include")

include_directories("${PROJECT_SOURCE_DIR}/RHI/")

# config in .h file
include_directories(${PROJECT_SOURCE_DIR})
configure_file(${PROJECT_SOURCE_DIR}/projectConfig.h.in ${PROJECT_SOURCE_DIR}/projectConfig.h)



find_package(OpenGL REQUIRED)

if(OS_WINDOWS)
    link_directories("${PROJECT_SOURCE_DIR}/Dependencies/GLFW/lib-vc2015")
elseif(OS_MACOS)
	INCLUDE_DIRECTORIES ( /System/Library/Frameworks )
	FIND_LIBRARY(COCOA_LIBRARY Cocoa)
	FIND_LIBRARY(IOKit_LIBRARY IOKit)
	FIND_LIBRARY(COREVIDEO_LIB NAMES CoreVideo)
    FIND_LIBRARY(METAL_LIB NAMES Metal)
    FIND_LIBRARY(METALKIT_LIB NAMES MetalKit)

    
    MARK_AS_ADVANCED (COCOA_LIBRARY
    				IOKit_LIBRARY
    				COREVIDEO_LIB
                    OPENGL_LIBRARIES
                    METAL_LIB)
    SET(EXTRA_LIBS ${COCOA_LIBRARY} ${IOKit_LIBRARY} ${COREVIDEO_LIB} ${OPENGL_LIBRARIES} 
                    ${METAL_LIB}  ${METALKIT_LIB})

    link_directories("${PROJECT_SOURCE_DIR}/Dependencies/GLFW/lib-mac")
    
endif(OS_WINDOWS)



add_subdirectory(PhantomCore)
add_subdirectory(sample)
add_subdirectory(Platform)
add_subdirectory(RHI)
add_subdirectory(Game)



