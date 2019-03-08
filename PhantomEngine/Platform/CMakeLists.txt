add_subdirectory(Empty)

IF(OS_WINDOWS)
	add_subdirectory(Windows)
ELSEIF(OS_MACOS)
	add_subdirectory(Macos)
ENDIF(OS_WINDOWS)