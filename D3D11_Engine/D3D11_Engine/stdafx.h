#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

//Include 
#include <Windows.h>
#include <xaudio2.h>

#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include <map>
#include <vector>
#include <tuple>
#include <list>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <functional>

#include <fcntl.h>
#include <io.h>
#include <math.h>
#include <pdh.h>
#include <psapi.h>
#include <stdarg.h>
#include <stdlib.h>
#include <tchar.h>
#include <timeapi.h>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include "Math.h"

//Linking D3D11
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

//Process Warning C4316	
#include "AlignedAllocationPolicy.h"
	
//Memory Leak Checker
#if defined(_DEBUG) | defined(DEBUG) 
#define DEBUG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

using namespace DirectX;
using namespace std;
using namespace std::experimental::filesystem::v1;


//DELETE Macro
#define SAFE_DELETE(p)  \
	{                   \
		if (p) {        \
			delete (p); \
			(p) = 0;    \
		}               \
	}

#define SAFE_DELETE_ARRAY(p) \
	{                        \
		if (p) {             \
			delete[](p);     \
			(p) = 0;         \
		}                    \
	}

#define SAFE_RELEASE(p)     \
	{                       \
		if (p) {            \
			(p)->Release(); \
			(p) = 0;        \
		}                   \
	}
