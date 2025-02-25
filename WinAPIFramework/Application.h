#pragma once
#include "TextBox.h"

enum APP_RUN_MODE
{
	APP_RUN_MODE_WNDPROC,
	APP_RUN_MODE_GAME_LOOP
};

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
	int menuName = 0;

	APP_RUN_MODE appRunMode = APP_RUN_MODE_WNDPROC;

	int backgroundColor = WHITE_BRUSH;
};

class Application : public std::enable_shared_from_this<Application>
{
public:
	Application() {}
	virtual ~Application() {}

public:
	virtual BOOL Initialize() = 0;
	virtual void Update() { if (m_AppDesc.appRunMode == APP_RUN_MODE_WNDPROC) __debugbreak(); };
	virtual void Draw(HDC hDC) { if (m_AppDesc.appRunMode == APP_RUN_MODE_WNDPROC) __debugbreak(); };
	virtual void Destroy();

	void DrawCoord(HDC hDC)
	{
		// µð¹ö±×¿ë ÁÂÇ¥Âï±â
		for (int i = 0; i < (m_AppDesc.wndSize.width / 100) + 1; i++)
		{
			TextBox::DrawFormattedString(hDC, { (ULONG)(i * 100), 0 }, L"%d", i * 100);
		}

		for (int i = 0; i < (m_AppDesc.wndSize.height / 100) + 1; i++)
		{
			TextBox::DrawFormattedString(hDC, { 0, (ULONG)(i * 100) }, L"%d", i * 100);
		}
	}

public:
	WNDPROC GetWndProc() { return m_pProcFunction; }
	AppDesc& GetAppDesc() { return m_AppDesc; }

protected:
	WNDPROC m_pProcFunction = nullptr;
	AppDesc m_AppDesc = {};

protected:
	HDC BeginAppPaint(HWND hWnd = CUR_HWND);
	BOOL EndAppPaint(HWND hWnd = CUR_HWND);

	HDC BeginDC(HWND hWnd);
	BOOL EndDC(HWND hWnd, HDC hDC);

public:
	BOOL BeginDoubleBuffering(HWND hWnd);
	BOOL EndDoubleBuffering(HWND hWnd);

	BOOL DrawDoubleBuffering(HWND hWnd);

	HDC GetBackBuffer() { return m_hMemDC; }

protected:
	// Win object resources
	PaintResource m_PaintResource = {};

private:
	// Double Buffering Resources
	RECT m_Rect = {};
	HDC m_hCurDC = nullptr;
	HDC m_hMemDC = nullptr;
	HBITMAP m_hMemBitmap = nullptr;
	HBITMAP m_hOldBitmap = nullptr;

};