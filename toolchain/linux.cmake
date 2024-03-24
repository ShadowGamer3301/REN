set(CMAKE_SYSTEM_NAME LINUX)
set(CMAKE_SYSTEM_PROCESSOR AMD64)
set(CMAKE_MAKE_PROGRAM "/bin/make")

if(UNIX)
	set(CMAKE_C_COMPILER "/bin/gcc")
	set(CMAKE_CXX_COMPILER "/bin/clang++")
endif()