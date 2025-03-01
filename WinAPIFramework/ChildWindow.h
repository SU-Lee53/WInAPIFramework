#pragma once

struct ChildWindowDesc
{
	WndSize wndSize = { 800, 600 };
	WndPosition wndPosition = { 0,0 };

	DWORD wndStyle = WS_CHILD | WS_VISIBLE | WS_BORDER | WS_THICKFRAME;

	LPWSTR wndIcon = IDI_APPLICATION;
	LPWSTR wndIconSmall = IDI_APPLICATION;
	LPWSTR wndCursor = IDC_ARROW;

	std::wstring className = L"Child";
	std::wstring wndName = L"";
	int menuName = 0;

	int backgroundColor = WHITE_BRUSH;
};

class ChildWindow
{
public:
	ChildWindow() {}
	~ChildWindow() {}

	ATOM Register(ChildWindowDesc desc, HWND parentHwnd, WNDPROC wndProc);
	BOOL Create(int cmdShow = SW_SHOW);

	HWND GetHwnd() { return m_hWnd; }
	ChildWindowDesc GetDesc() { return m_Desc; }

private:
	HWND m_parentHwnd = 0;
	HWND m_hWnd = 0;
	WNDPROC m_wndProc = NULL;
	ChildWindowDesc m_Desc = {};

};
