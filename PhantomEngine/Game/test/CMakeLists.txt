add_executable(ZOgexParserTest OgexParserTest.cpp)
target_link_libraries(ZOgexParserTest 
						PhantomCore 
						${OPENGEX_LIBRARY} 
						${OPENDDL_LIBRARY} 
				    	${EXTRA_LIBS}  # mac库
							${JPGE_LIBRARY}
						)

#add_executable(SceneObjectTest SceneObjectTest.cpp)
#target_link_libraries(SceneObjectTest Common ${XG_LIBRARY})
#__add_xg_platform_dependencies(SceneObjectTest)
#add_test(NAME TEST_SceneObject COMMAND SceneObjectTest)

# copy resource to execute dir (debug directory)
add_custom_command(TARGET ZOgexParserTest PRE_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory
${CMAKE_SOURCE_DIR}/Assets   $<TARGET_FILE_DIR:ZOgexParserTest>)


if(OS_WINDOWS)

 	 # copy resource to execute dir (debug mode)
    add_custom_command(TARGET ZOgexParserTest PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Assets   "${PROJECT_BINARY_DIR}/Game/test")
endif()

