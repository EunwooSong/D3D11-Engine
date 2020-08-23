#pragma once

//Linking D3D11
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

//Include 
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include <iostream>
#include <random>
#include <map>
#include <vector>
#include <list>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <functional>

//Process Warning C4316
#include "AlignedAllocationPolicy.h"

using namespace DirectX;
using namespace std;
using namespace std::experimental::filesystem::v1;

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
