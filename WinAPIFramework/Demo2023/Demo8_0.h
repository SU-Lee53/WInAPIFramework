#pragma once
#include "../Application.h"

enum DEMO71_SHAPE_TYPE
{
	DEMO71_SHAPE_TYPE_ELLIPSE = 0,
	DEMO71_SHAPE_TYPE_RECTANGLE,
	DEMO71_SHAPE_TYPE_TRIANGLE
};

class Demo8_0 : public Application
{
public:
	Demo8_0() {}
	virtual ~Demo8_0() {}

public:
	virtual BOOL Initialize() override;

	void OnPaint();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	void OnCreate(HWND hWnd);
	void HandleMenu(WORD param);

public:
	void ProcessKeyboard();
	void ProcessMouse();

};

