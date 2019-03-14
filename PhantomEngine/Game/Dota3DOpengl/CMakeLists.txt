#include_directories("${PROJECT_SOURCE_DIR}/Platform/Empty")




if(OS_WINDOWS)
	add_executable(Dota3DOpengl DefaultGame.cpp WindowsOpenGLApplicationConfig.cpp)
 	 # copy resource to execute dir (debug mode)
    add_custom_command(TARGET Dota3DOpengl PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Assets   "${PROJECT_BINARY_DIR}/Game/Dota3DOpengl")



	 target_link_libraries(Dota3DOpengl 
                            PhantomCore
                            PlatformInterface
							${OPENGL_LIBRARIES} 
                            OpenGLRHI
							 #${OPENDDL_LIBRARY}
							 #${OPENGEX_LIBRARY}
                        )
elseif(OS_MACOS)
	add_executable(Dota3DOpengl DefaultGame.cpp WindowsOpen123GLApplicationConfig.cpp)
    target_link_libraries(Dota3DOpengl 
                            PhantomCore
                            PlatformInterface
                            libglfw3.a
                            OpenGLRHI
					    	${OPENGL_LIBRARIES} 
        					libc++.dylib
					    	${EXTRA_LIBS}
                        )
endif()
# copy resource to execute dir (debug directory)
add_custom_command(TARGET Dota3DOpengl PRE_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory
${CMAKE_SOURCE_DIR}/Assets   $<TARGET_FILE_DIR:Dota3DOpengl>)
