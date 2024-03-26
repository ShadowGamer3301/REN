cmake_minimum_required(VERSION 3.15)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

option(BUILD_MS_WIN32 "Build REN for Microsoft Windows 10/11" ON)
option(BUILD_MS_XBOX "Build REN for Microsoft Xbox (2001)" OFF)
option(BUILD_GNU_LINUX "Build REN for GNU Linux" OFF)
option(BUILD_NINTENDO_GAMECUBE "Build REN for Nintendo GameCube" OFF)

project(REN VERSION 1.0)
project(Editor VERSION 1.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

if(BUILD_MS_WIN32)
	set(CMAKE_TOOLCHAIN_FILE "toolchain/mswin.cmake")

	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/MSWIN/LIB)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/MSWIN/LIB)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/MSWIN/BIN)

	add_compile_definitions(TARGET_MS_WIN32 UNICODE)
	link_directories(BEFORE "vendor/lib")
	include_directories(BEFORE "vendor/include" "Core/src")

	project(OsProber VERSION 1.0)
	add_subdirectory(OsProber)
endif()

if(BUILD_GNU_LINUX)
	set(CMAKE_TOOLCHAIN_FILE "toolchain/linux.cmake")

	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/GNU/LIB)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/GNU/LIB)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/GNU/BIN)

	add_compile_definitions(TARGET_GNU_LINUX)
endif()

add_subdirectory(Core)
add_subdirectory(Editor)