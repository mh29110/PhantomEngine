include_directories("${PROJECT_SOURCE_DIR}/PlatformInterface")

add_executable(DotaAwc DefaultGame.cpp)

 target_link_libraries(DotaAwc 
                            PhantomCore
                            PlatformInterface
                        )

target_include_directories(DotaAwc PRIVATE "${PROJECT_SOURCE_DIR}/External/src/glad/include")
