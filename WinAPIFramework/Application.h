#pragma once

struct AppDesc
{
	WndSize wndSize = { 800, 600 };
	WndPosition wndPosition = { 0,0 };

	DWORD wndStyle = WS_OVERLAPPEDWINDOW;

	LPWSTR wndIcon = IDI_APPLICATION;
	LPWSTR wndIconSmall = IDI_APPLICATION;
	LPWSTR wndCursor = IDC_ARROW;

	std::wstring className = L"WndProgram";
	std::wstring wndName = L"";
	std::wstring menuName = L"";

	int backgroundColor = WHITE_BRUSH;
};

class Application
{
public:
	Application() {}
	virtual ~Application() {}

public:
	virtual BOOL Initialize() = 0;
	
public:
	WNDPROC GetWndProc() { return m_pProcFunction; }
	AppDesc& GetAppDesc() { return m_AppDesc; }

protected:
	WNDPROC m_pProcFunction = nullptr;
	AppDesc m_AppDesc = {};

protected:
	// Win object resources
	PaintResource m_PaintResource = {};
};