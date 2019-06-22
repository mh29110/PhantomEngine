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
							${OPENGEX_LIBRARY} 
							${OPENDDL_LIBRARY}
							${JPGE_LIBRARY}
                            ${FREETYPE_LIBRARY}
                        )
elseif(OS_MACOS)

#MESSAGE( STATUS "jpeg: " ${JPGE_LIBRARY} )

	add_executable(Dota3DOpengl DefaultGame.cpp MacOpenGLApplicationConfig.cpp)
    target_link_libraries(Dota3DOpengl 
                            PhantomCore
                            PlatformInterface
                            OpenGLRHI
					    	${OPENGL_LIBRARIES} 
        					libc++.dylib
					    	${EXTRA_LIBS}
                            ${OPENGEX_LIBRARY} 
                            ${OPENDDL_LIBRARY}
                            ${JPGE_LIBRARY}
                            ${FREETYPE_LIBRARY}
                        )
endif()
# copy resource to execute dir (debug directory)
add_custom_command(TARGET Dota3DOpengl PRE_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory
${CMAKE_SOURCE_DIR}/Assets   $<TARGET_FILE_DIR:Dota3DOpengl>)
