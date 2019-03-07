add_subdirectory(Empty)

IF(Windows)
	add_subdirectory(Windows)
ELSEIF(MACOS)
	add_subdirectory(Macos)
ENDIF(Windows)