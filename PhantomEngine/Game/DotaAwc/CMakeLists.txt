#include_directories("${PROJECT_SOURCE_DIR}/Platform/Empty")
add_executable(DotaAwc DefaultGame.cpp)

# copy resource to execute dir (debug directory)
add_custom_command(TARGET DotaAwc PRE_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory
${CMAKE_SOURCE_DIR}/Assets   $<TARGET_FILE_DIR:DotaAwc>)


if(OS_WINDOWS)

 	 # copy resource to execute dir (debug mode)
    add_custom_command(TARGET DotaAwc PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Assets   "${PROJECT_BINARY_DIR}/Game/DotaAwc")



	 target_link_libraries(DotaAwc 
                            PhantomCore
                            PlatformInterface

                            D3dRHI d3d12 dxgi d3dcompiler #3d

							D2dRHI d2d1					  #2d 	
                        )
elseif(OS_MACOS)
    target_link_libraries(DotaAwc 
                            PhantomCore
                            PlatformInterface
                            libglfw3.a
					    	${OPENGL_LIBRARIES} 
        					libc++.dylib
					    	${EXTRA_LIBS}
                        )
endif()

target_include_directories(DotaAwc PRIVATE "${PROJECT_SOURCE_DIR}/External/src/glad/include")
