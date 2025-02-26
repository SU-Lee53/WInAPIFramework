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

// msimg32
#pragma comment (lib, "msimg32.lib")

// atlImage
#include <atlimage.h>

// Additional User Headers
#include "Define.h"
#include "Types.h"
#include "WinObjWrapper.h"
#include "RandomGenerator.h"

// Resources
#include "resource.h"

// Manager
#include "TimerManager.h"
#include "InputManager.h"
#include "TimeManager.h"

// Cores
#include "Core.h"

// Shapes
#include "Pixel.h"
#include "Line.h"
#include "Ellipse.h"
#include "Rectangle.h"
#include "Polygon.h"

#include "Bitmap.h"
#include "GameObject.h"
#include "Animation.h"
#include "Image.h"
#include "Dialog.h"

// Utils
#include "Utils.h"

// Debugs
#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

#include <cassert>

#endif _DEBUG