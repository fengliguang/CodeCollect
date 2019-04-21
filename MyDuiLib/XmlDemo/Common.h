#ifndef _COMMON_H_
#define _COMMON_H_

#define WIN32_LEAN_AND_MEAN	
#define _CRT_SECURE_NO_DEPRECATE

#include <windows.h>
#include <objbase.h>
#include "..\DuiLib\UIlib.h"
using namespace DuiLib;

#ifdef _DEBUG
#pragma comment(lib, "..\\Common\\DuiLib_d.lib")
#else
#pragma comment(lib, "..\\Common\\DuiLib.lib")
#endif

#endif