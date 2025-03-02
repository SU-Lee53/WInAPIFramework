#include "pch.h"
#include "Core.h"

// Demos
#include "Demo0.h"
#include "Demo2023/Demo8_0.h"
#include "Demo2023/Demo8_1.h"

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#endif

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);
	//_CrtSetBreakAlloc(175);
#endif _DEBUG

	CoreDesc desc;
	{
		desc.hInstance = hInstance;
		desc.hWnd = NULL;
		desc.app = std::make_shared<Demo8_1>();
	}

	CORE.RunWndProgram(desc);

#ifdef _DEBUG
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	//_CrtDumpMemoryLeaks();
#endif _DEBUG

	return 0;
}