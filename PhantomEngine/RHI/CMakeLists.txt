IF(WIN32)
    add_subdirectory(OpenGL)
    # add_subdirectory(D2d)
    # add_subdirectory(D3d)
ELSEIF(UNIX)
    IF(APPLE)
        # Apple specific code
        add_subdirectory(Metal)
    ENDIF(APPLE)
ELSE()
    # Empty
    add_subdirectory(Empty)
ENDIF(WIN32)

