add_library(PlatformInterface 
	WindowsApplication.cpp
	OpenGLApplication.cpp
	Win32Timer.cpp
)

	 target_link_libraries(PlatformInterface 
                            PhantomCore
							OpenGLRHI
							D3dRHI
							D3d12
							Dxgi
							d3dcompiler 
                        )