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
	add_executable( Dota3DOpengl 
                    # MACOSX_BUNDLE #资源打进包内
                    DefaultGame.cpp 
                    MacOpenGLApplicationConfig.cpp
                    Main.metallib)

# metal shader lib begin 
    set(SHADER_SOURCES
        base
        pbr.vert pbr.frag
    )

    foreach(SHADER IN LISTS SHADER_SOURCES)
        add_custom_command(OUTPUT ${SHADER}.air
        COMMAND xcrun -sdk macosx metal -g -MO -c ${PROJECT_SOURCE_DIR}/Assets/Assets/Resources/shaders/Metal/${SHADER}.metal -o ${SHADER}.air
        COMMENT "Compile ${SHADER}.metal --> ${SHADER}.air"
        DEPENDS ${PROJECT_SOURCE_DIR}/Assets/Assets/Resources/shaders/Metal/${SHADER}.metal
    )

    list(APPEND AIRS ${SHADER}.air)
    endforeach(SHADER)

    add_custom_command(OUTPUT Main.metalar
        COMMAND xcrun -sdk macosx metal-ar rcv Main.metalar ${AIRS}
        COMMENT "Archive ${AIRS} --> Main.metalar"
        DEPENDS ${AIRS}
    )

    add_custom_command(OUTPUT Main.metallib
        COMMAND xcrun -sdk macosx metallib Main.metalar -split-module-without-linking -o Debug/Main.metallib
        COMMENT "Compile Editor.metalar --> Main.metallib"
        DEPENDS Main.metalar
    )

    add_custom_target(PhantomShaderLibrary
        DEPENDS Main.metallib
    )

    add_dependencies(Dota3DOpengl PhantomShaderLibrary)

    set(RESOURCE_FILES
        Main.metallib
    )

    set_target_properties(Dota3DOpengl PROPERTIES
        RESOURCE "${RESOURCE_FILES}"
    )
# metal shader lib end 

    
    target_link_libraries(Dota3DOpengl 
                            PhantomCore
                            PlatformInterface
                            MetalRHI
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
