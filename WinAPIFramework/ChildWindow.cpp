#include "pch.h"
#include "ChildWindow.h"

ATOM ChildWindow::Register(ChildWindowDesc desc,HWND parentHwnd, WNDPROC wndProc)
{
	m_Desc = desc;
	m_wndProc = wndProc;
	m_parentHwnd = parentHwnd;

	WNDCLASSEX wndClass;
	ZeroMemory(&wndClass, sizeof(wndClass));
	{
		wndClass.cbSize = sizeof(wndClass);
		wndClass.style = CS_HREDRAW | CS_VREDRAW;
		wndClass.lpfnWndProc = m_wndProc;
		wndClass.cbClsExtra = 0;
		wndClass.cbWndExtra = 0;
		wndClass.hInstance = CUR_HINSTANCE;
		wndClass.hIcon = ::LoadIcon(NULL, m_Desc.wndIcon);
		wndClass.hCursor = ::LoadCursor(NULL, m_Desc.wndCursor);
		wndClass.hbrBackground = (HBRUSH)::GetStockObject(m_Desc.backgroundColor);
		wndClass.lpszMenuName = NULL;
		wndClass.lpszClassName = m_Desc.className.c_str();
		wndClass.hIconSm = LoadIcon(NULL, m_Desc.wndIconSmall);
	}

	return RegisterClassExW(&wndClass);
}

BOOL ChildWindow::Create(int cmdShow)
{
	BOOL bResult = TRUE;

	RECT rect{ 0, 0, m_Desc.wndSize.width , m_Desc.wndSize.height };

	if (m_Desc.menuName == 0)
		AdjustWindowRect(&rect, m_Desc.wndStyle, FALSE);
	else
		AdjustWindowRect(&rect, m_Desc.wndStyle, TRUE);


	int windowWidth = rect.right - rect.left;
	int windowHeight = rect.bottom - rect.top;

	m_hWnd = ::CreateWindow(
		m_Desc.className.c_str(),
		m_Desc.wndName.c_str(),
		m_Desc.wndStyle,
		m_Desc.wndPosition.x,
		m_Desc.wndPosition.y,
		windowWidth,
		windowHeight,
		m_parentHwnd,
		NULL,
		CUR_HINSTANCE,
		NULL
	);

	if (m_Desc.menuName != 0)
	{
		HMENU hMenu = LoadMenu(CUR_HINSTANCE, MAKEINTRESOURCE(m_Desc.menuName));
		SetMenu(m_hWnd, hMenu);
	}


	bResult = ::ShowWindow(m_hWnd, cmdShow);
	bResult = ::UpdateWindow(m_hWnd);

	return bResult;
}
