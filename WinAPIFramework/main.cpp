#include "pch.h"
#include "Core.h"

// Demos
#include "Demo0.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	CoreDesc desc;
	{
		desc.hInstance = hInstance;
		desc.hWnd = NULL;
		desc.app = std::make_shared<Demo0>();
	}

	CORE.BeginWndProgram(desc);

	return 0;
}