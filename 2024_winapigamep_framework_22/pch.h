#pragma once

// ���� include
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
#include<assert.h>

#include<Windows.h>
#include <wincodec.h>  

// DX
#include <d2d1.h>
#include <d2d1effects.h>
#include <wrl.h>
#include <DirectXMath.h>
using namespace DirectX;
using namespace Microsoft::WRL;

// My Header
#include "Define.h"
#include "Enums.h"
#include "Types.h"

// ���� lib
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "windowscodecs.lib")
#pragma comment(lib, "msimg32.lib") // transparent �� blt�� ���
#pragma comment(lib, "fmod_vc.lib") 
#pragma comment(lib, "fmodL_vc.lib")
#pragma comment(lib, "d2d1.lib")

// ���� using
using std::vector;
using std::map;
using std::wstring;

// ���� define
#define PI 3.14159265f
#define SCREEN_WIDTH  1024
#define SCREEN_HEIGHT 1024

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