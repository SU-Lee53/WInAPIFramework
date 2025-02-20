#include "pch.h"
#include "Core.h"
#include "Application.h"
#include "Utils.h"

WPARAM Core::RunWndProgram(const CoreDesc& appDesc)
{
	m_Desc = appDesc;
	m_Desc.app->Initialize();
	RANDOM.Initialize();

	MyRegisterClass();

	if (!InitInstance(SW_SHOW))
	{
		Utils::ShowError();
		return FALSE;
	}

	MSG msg;

	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	return msg.wParam;
}

ATOM Core::MyRegisterClass()
{
	WNDCLASSEX wndClass;
	ZeroMemory(&wndClass, sizeof(wndClass));
	{
		wndClass.cbSize = sizeof(wndClass);
		wndClass.style = CS_HREDRAW | CS_VREDRAW;
		wndClass.lpfnWndProc = m_Desc.app->GetWndProc();
		wndClass.cbClsExtra = 0;
		wndClass.cbWndExtra = 0;
		wndClass.hInstance = m_Desc.hInstance;
		wndClass.hIcon = ::LoadIcon(NULL, m_Desc.app->GetAppDesc().wndIcon);
		wndClass.hCursor = ::LoadCursor(NULL, m_Desc.app->GetAppDesc().wndCursor);
		wndClass.hbrBackground = (HBRUSH)::GetStockObject(m_Desc.app->GetAppDesc().backgroundColor);
		wndClass.lpszMenuName = NULL;
		wndClass.lpszClassName = m_Desc.app->GetAppDesc().className.c_str();
		wndClass.hIconSm = LoadIcon(NULL, m_Desc.app->GetAppDesc().wndIconSmall);
	}

	return RegisterClassExW(&wndClass);
}

BOOL Core::InitInstance(int cmdShow)
{
	BOOL bResult = TRUE;

	m_Desc.hWnd = ::CreateWindow(
		m_Desc.app->GetAppDesc().className.c_str(),
		m_Desc.app->GetAppDesc().wndName.c_str(),
		m_Desc.app->GetAppDesc().wndStyle,
		m_Desc.app->GetAppDesc().wndPosition.x,
		m_Desc.app->GetAppDesc().wndPosition.y,
		m_Desc.app->GetAppDesc().wndSize.width,
		m_Desc.app->GetAppDesc().wndSize.height,
		NULL,
		NULL,
		m_Desc.hInstance,
		NULL
	);

	bResult = ::ShowWindow(m_Desc.hWnd, cmdShow);
	bResult = ::UpdateWindow(m_Desc.hWnd);

	return bResult;
}
