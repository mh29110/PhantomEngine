# 1. 首先确定平台，并设置平台标识字符串如下
----------------------------------begin--------------------------------
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
	ENDIF(UNIX
---------------------------------end ---------------------------------
# 2. 设置变量= 平台依赖目录  比如windows的依赖目录为 Dependencies/Windows
	set(PHANTOM_DEPENDENCIES_ROOT ${PROJECT_SOURCE_DIR}/Dependencies/${PHANTOM_TARGET_PLATFORM}/)
	# list(APPEND CMAKE_MODULE_PATH "${PHANTOM_DEPENDENCIES_ROOT}cmake")
	include_directories("${PHANTOM_DEPENDENCIES_ROOT}")
	include_directories("${PHANTOM_DEPENDENCIES_ROOT}include") # 各平台下头文件，参考opengex install流程


set(PHANTOM_DEPENDENCIES_LIBRARY_PATH ${PHANTOM_DEPENDENCIES_ROOT}lib/)
set(PHANTOM_DEPENDENCIES_EXTERNAL_FRAMEWORK_PATH ${PHANTOM_DEPENDENCIES_ROOT}framework/)
# 3. 查询对应平台类库并在之后使用
	find_library(XG_LIBRARY xg PATHS ${PHANTOM_DEPENDENCIES_LIBRARY_PATH} NO_CMAKE_FIND_ROOT_PATH NO_SYSTEM_ENVIRONMENT_PATH)
	find_library(OPENDDL_LIBRARY OpenDDL PATHS ${PHANTOM_DEPENDENCIES_LIBRARY_PATH} NO_CMAKE_FIND_ROOT_PATH NO_SYSTEM_ENVIRONMENT_PATH)
	find_library(OPENGEX_LIBRARY OpenGEX PATHS ${PHANTOM_DEPENDENCIES_LIBRARY_PATH} NO_CMAKE_FIND_ROOT_PATH NO_SYSTEM_ENVIRONMENT_PATH)
	MESSAGE( STATUS "OPENDDL_LIBRARY: " ${OPENDDL_LIBRARY} )
	MESSAGE( STATUS "OPENGEX_LIBRARY: " ${OPENGEX_LIBRARY} )
