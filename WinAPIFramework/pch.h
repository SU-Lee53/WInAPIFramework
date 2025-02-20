#pragma once

// STL
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <concepts>
#include <random>


// WinAPI
#include <Windows.h>
#include <tchar.h>

// Additional User Headers
#include "Define.h"
#include "Types.h"
#include "WinObjWrapper.h"
#include "RandomGenerator.h"

// Cores
#include "Core.h"


// Debugs
#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

#endif _DEBUG