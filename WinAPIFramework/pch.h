#pragma once

// STL
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <concepts>
#include <random>
#include <algorithm>
#include <functional>

// WinAPI
#include <Windows.h>
#include <tchar.h>

// Additional User Headers
#include "Define.h"
#include "Types.h"
#include "WinObjWrapper.h"
#include "RandomGenerator.h"

// Manager
#include "TimerManager.h"
#include "InputManager.h"

// Cores
#include "Core.h"

// Shapes
#include "Pixel.h"
#include "Line.h"
#include "Ellipse.h"
#include "Rectangle.h"
#include "Polygon.h"

// Debugs
#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

#include <cassert>

#endif _DEBUG