#pragma once

#ifdef TARGET_MS_WIN32

//Disable unused WIN32 features, macros, typedefs etc...
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define NOATOM

//Expose GLFW to native WINAPI
#define GLFW_EXPOSE_NATIVE_WIN32

//Include standard library
#include <source_location>
#include <string>
#include <filesystem>
#include <sstream>
#include <vector>
#include <map>
#include <exception>

//Include Windows headers
#include <Windows.h>
#include <windowsx.h>
#include <wrl.h>

//Include DirectX headers
#include <d3d12.h>
#include <Xinput.h>
#include <d3dcompiler.h>
#include <dxgi1_6.h>
#include <d3dx12.h>
#include <d3d11.h>

//Include GLFW headers
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#endif