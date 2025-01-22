#pragma once

// ���� include
#include<Windows.h>
#include<assert.h>
#include<tchar.h>
#include<memory>

#include<vector>
#include<list>
#include<map>
#include<unordered_map>
#include<set>
#include<unordered_set>
#include<string>

#include<algorithm>
#include<ctime>

#define _USE_MATH_DEFINES
#include<math.h>
#include<functional>

// DX
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include <DirectXMath.h>
#include <DirectXTex/DirectXTex.h>
#include <DirectXTex/DirectXTex.inl>
#include <DirectXPackedVector.h>
#include <DirectXCollision.h>

// ���� lib
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "msimg32.lib") // transparent �� blt�� ���
#pragma comment(lib, "fmod_vc.lib") 
#pragma comment(lib, "fmodL_vc.lib")

// ���� using
using std::vector;
using std::map;
using std::wstring;
using std::string;

using namespace DirectX;
using namespace Microsoft::WRL;

// My Header
#include "Define.h"
#include "Enums.h"
#include "Struct.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#ifdef _DEBUG
#pragma comment(lib, "DirectXTex\\DirectXTex_debug.lib")
#else
#pragma comment(lib, "DirectXTex\\DirectXTex.lib")
#endif


// ���� define
#define PI 3.14159265f
#define SCREEN_WIDTH  1024
#define SCREEN_HEIGHT 1024
#define CHECK(p) 	assert(SUCCEEDED(p));

// ������ �ܼ�â
#ifdef _DEBUG
#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)
#define malloc(s) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
#endif
#include<iostream>

using std::cout;
using std::endl;