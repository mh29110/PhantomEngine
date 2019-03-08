add_subdirectory(Empty)

IF(WIN32)
	add_subdirectory(Windows)
ELSEIF(MACOS)
	add_subdirectory(Macos)
ENDIF(WIN32)