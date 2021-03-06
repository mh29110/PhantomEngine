cmake_minimum_required (VERSION 3.1)

# Check platforms
IF(UNIX)
    IF(APPLE)
        set(PHANTOM_TARGET_PLATFORM "Darwin")
        set(OS_MACOS 1)
    ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES Android)
        set(PHANTOM_TARGET_PLATFORM "Android")
        set(ANDROID 1)
        set(OS_ANDROID 1)
    ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
        set(PHANTOM_TARGET_PLATFORM "FreeBSD")
        include_directories("/usr/local/include")
        set(BSD 1)
        set(OS_BSD 1)
    ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES Emscripten)
        set(PHANTOM_TARGET_PLATFORM "Emscripten")
        set(WA 1)
        set(OS_WEBASSEMBLY 1)
        unset (USE_ISPC)
    ELSE(LINUX)
        set(PHANTOM_TARGET_PLATFORM "Linux")
        set(OS_LINUX 1)
    ENDIF(APPLE)
ELSEIF(WIN32)
    set(PHANTOM_TARGET_PLATFORM "Windows")
        set(OS_WINDOWS 1)
ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES Psp2)
    set(PHANTOM_TARGET_PLATFORM "PSP2")
    set(PSP2 1)
    set(OS_PSP2 1)
ENDIF(UNIX)

IF (CMAKE_BUILD_TYPE STREQUAL Debug)
    ADD_DEFINITIONS(-D_DEBUG)
ENDIF()




project (PhantomEngine)

include_directories("${PROJECT_SOURCE_DIR}/PhantomCore/src")
include_directories("${PROJECT_SOURCE_DIR}/Dependencies/GLFW/include")
include_directories("${PROJECT_SOURCE_DIR}/Platform/${PHANTOM_TARGET_PLATFORM}") # 根据平台来决定include
include_directories("${PROJECT_SOURCE_DIR}/Dependencies/src/glad/include")


include_directories("${PROJECT_SOURCE_DIR}/RHI/")

# config in .h file
include_directories(${PROJECT_SOURCE_DIR})
configure_file(${PROJECT_SOURCE_DIR}/projectConfig.h.in ${PROJECT_SOURCE_DIR}/projectConfig.h)


# --------------------------------dependencies begin-------------------------------------
set(PHANTOM_DEPENDENCIES_ROOT ${PROJECT_SOURCE_DIR}/Dependencies/${PHANTOM_TARGET_PLATFORM}/)
# list(APPEND CMAKE_MODULE_PATH "${PHANTOM_DEPENDENCIES_ROOT}cmake")
include_directories("${PHANTOM_DEPENDENCIES_ROOT}")
include_directories("${PHANTOM_DEPENDENCIES_ROOT}include") # 各平台下头文件，参考opengex install流程


set(PHANTOM_DEPENDENCIES_LIBRARY_PATH ${PHANTOM_DEPENDENCIES_ROOT}lib/)
set(PHANTOM_DEPENDENCIES_EXTERNAL_FRAMEWORK_PATH ${PHANTOM_DEPENDENCIES_ROOT}framework/)

# openGex
find_library(XG_LIBRARY xg PATHS ${PHANTOM_DEPENDENCIES_LIBRARY_PATH} NO_CMAKE_FIND_ROOT_PATH NO_SYSTEM_ENVIRONMENT_PATH)
find_library(OPENDDL_LIBRARY OpenDDL PATHS ${PHANTOM_DEPENDENCIES_LIBRARY_PATH} NO_CMAKE_FIND_ROOT_PATH NO_SYSTEM_ENVIRONMENT_PATH)
find_library(OPENGEX_LIBRARY OpenGEX PATHS ${PHANTOM_DEPENDENCIES_LIBRARY_PATH} NO_CMAKE_FIND_ROOT_PATH NO_SYSTEM_ENVIRONMENT_PATH)





# 查找libjpeg库,优先使用静态库
if(MSVC)
    set( JPEG_NAMES jpeg-static )
elseif(CMAKE_COMPILER_IS_GNUCXX)
    set( JPEG_NAMES libjpeg.a)
endif()
find_library(JPGE_LIBRARY jpeg PATHS ${PHANTOM_DEPENDENCIES_LIBRARY_PATH} NO_CMAKE_FIND_ROOT_PATH NO_SYSTEM_ENVIRONMENT_PATH)
if(JPEG_FOUND)
    message(STATUS "JPEG_INCLUDE_DIR=${JPEG_INCLUDE_DIR}")
    message(STATUS "JPEG_LIBRARIES=${JPEG_LIBRARIES}")  
endif()



MESSAGE( STATUS "Freetype: my" ${JPGE_LIBRARY} )


# --------------------------------dependencies  end-------------------------------------
link_directories("${PROJECT_SOURCE_DIR}/Dependencies/${PHANTOM_TARGET_PLATFORM}/bin")

find_package(OpenGL REQUIRED)

if(OS_WINDOWS)
# freetype2   freetyped<Windows>  or  freetype<Darwin> ?
    find_library(FREETYPE_LIBRARY freetyped PATHS ${PHANTOM_DEPENDENCIES_LIBRARY_PATH} NO_CMAKE_FIND_ROOT_PATH NO_SYSTEM_ENVIRONMENT_PATH)
	
	set (CMAKE_C_STANDARD 17)
	set (CMAKE_CXX_STANDARD 17)

elseif(OS_MACOS)
    find_library(FREETYPE_LIBRARY freetype PATHS ${PHANTOM_DEPENDENCIES_LIBRARY_PATH} NO_CMAKE_FIND_ROOT_PATH NO_SYSTEM_ENVIRONMENT_PATH)
	
	set (CMAKE_C_STANDARD 11)
	set (CMAKE_CXX_STANDARD 11)

    find_package(PNG REQUIRED)
    find_package(BZIP2 REQUIRED)
    find_package(ZLIB REQUIRED)

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
                    ${METAL_LIB}  ${METALKIT_LIB}
                    ${PNG_LIBRARY}
                    ${ZLIB_LIBRARY}
                    ${BZIP2_LIBRARY})

    
endif(OS_WINDOWS)



add_subdirectory(PhantomCore)
add_subdirectory(Tests)
add_subdirectory(Platform)
add_subdirectory(RHI)
add_subdirectory(Game)



