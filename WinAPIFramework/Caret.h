#pragma once

class Caret
{
public:
	Caret() {}
	~Caret() {}

public:
	BOOL Create(HWND hWnd, HBITMAP hBitmap, int nWidth, int nHeight);
	BOOL Show(HWND hWnd = NULL);
	BOOL SetPos(int x, int y);
	BOOL GetPos(LPPOINT lpPoint);
	BOOL SetBlinkTime(UINT mMSeconds);
	UINT GetBlinkTime();
	BOOL Hide(HWND hWnd = NULL);
	BOOL Destroy();


private:
	HWND m_CurrentWndHandle = NULL;
	HBITMAP m_hBitmap = NULL;
	int m_width = 0;
	int m_height = 0;
};

