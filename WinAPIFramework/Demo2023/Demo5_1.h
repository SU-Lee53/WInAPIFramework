#pragma once
#include "../Application.h"

class TextBox;
class Caret;
class GameBoard;
class Bitmap;

class Demo5_1 : public Application
{
public:
	Demo5_1() {}
	virtual ~Demo5_1() {}

public:
	virtual BOOL Initialize() override;
	virtual void Update() override;
	virtual void Draw(HDC hDC) override;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	void OnCreate(HWND hWnd);
	void HandleMenu(WORD param);

	
public:
	void ProcessKeyboard();
	void ProcessMouse();

public:
	void ResetGame();

private:
	std::array<BitmapRect, 4> m_Bitmaps = {};	// 0번이 기준임
	int m_drawMode = SRCCOPY;
	int m_Seleted = 0;

	RECT m_mainRect = C_RECT(0, 0, m_AppDesc.wndSize.width, m_AppDesc.wndSize.height);	// 0번의 RECT

	BOOL m_bFullscreen = FALSE;
	BOOL m_bMove = FALSE;
	ULONGLONG m_ullPrevMoveTick = 0;
	ULONGLONG m_ullMoveTick = 100;

};

