// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

using namespace std;

#include <iostream>
#include <fstream>
#include <vector>
#include <direct.h>
#include <string>

// TODO: reference additional headers your program requires here
#include <d3d11.h>
#include <d3dx11.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")
#include <d3dcompiler.h>
#include <atlstr.h>
#include "HelperStructs.h"
#include "WindowSize.h"
#include "graphics_device_interface.h"
#include "HelperStructs.h"
#include "Model.h"
#include "Entity.h"
#include "Camera.h"
#include "VoxelMap.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
