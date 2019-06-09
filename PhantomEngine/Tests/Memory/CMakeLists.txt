
set(MEM_SRC "./src/")
file (GLOB_RECURSE  MEM_SRC 
					"${MEM_SRC}/*.h"
					"${MEM_SRC}/*.cpp"
					)
#message("My source files: " ${MEM_SRC})



add_executable (ZMemoryMgr main.cpp  ${MEM_SRC})