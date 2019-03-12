#include_directories("${PROJECT_SOURCE_DIR}/Platform/Empty")
add_executable(Dota3DOpengl DefaultGame.cpp)

# copy resource to execute dir (debug directory)
add_custom_command(TARGET Dota3DOpengl PRE_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory
${CMAKE_SOURCE_DIR}/Assets   $<TARGET_FILE_DIR:Dota3DOpengl>)


if(OS_WINDOWS)

 	 # copy resource to execute dir (debug mode)
    add_custom_command(TARGET Dota3DOpengl PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Assets   "${PROJECT_BINARY_DIR}/Game/Dota3DOpengl")



	 target_link_libraries(Dota3DOpengl 
                            PhantomCore
                            PlatformInterface
							${OPENGL_LIBRARIES} 
                            OpenGLRHI
                        )
elseif(OS_MACOS)
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

target_include_directories(Dota3DOpengl PRIVATE "${PROJECT_SOURCE_DIR}/External/src/glad/include")
