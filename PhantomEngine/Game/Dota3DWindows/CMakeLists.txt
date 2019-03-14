#include_directories("${PROJECT_SOURCE_DIR}/Platform/Empty")
add_executable(Dota3DWindows DefaultGame.cpp WindowsApplicationConfig.cpp)

# copy resource to execute dir (debug directory)
add_custom_command(TARGET Dota3DWindows PRE_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory
${CMAKE_SOURCE_DIR}/Assets   $<TARGET_FILE_DIR:Dota3DWindows>)


if(OS_WINDOWS)

 	 # copy resource to execute dir (debug mode)
    add_custom_command(TARGET Dota3DWindows PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Assets   "${PROJECT_BINARY_DIR}/Game/Dota3DWindows")



	 target_link_libraries(Dota3DWindows 
                            PlatformInterface
                        )
endif()

