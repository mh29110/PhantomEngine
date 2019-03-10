#include_directories("${PROJECT_SOURCE_DIR}/Platform/Empty")

add_executable(DotaAwc DefaultGame.cpp)

 target_link_libraries(DotaAwc 
                            PhantomCore
                            PlatformInterface
                            libglfw3.a
					    	${OPENGL_LIBRARIES} 
        					libc++.dylib
					    	${EXTRA_LIBS}
                        )

target_include_directories(DotaAwc PRIVATE "${PROJECT_SOURCE_DIR}/External/src/glad/include")
