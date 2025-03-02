#pragma once
#include "../Application.h"

// 원이동은 Pass

class TextBox;
class Caret;
class GameBoard;

enum DEMO61_DRAW_MODE : UINT8
{
	DEMO61_DRAW_MODE_SIN = 1,
	DEMO61_DRAW_MODE_ZIGZAG = DEMO61_DRAW_MODE_SIN << 1,
	DEMO61_DRAW_MODE_SPRING = DEMO61_DRAW_MODE_ZIGZAG <<1,
	DEMO61_DRAW_MODE_PI = DEMO61_DRAW_MODE_SPRING << 1,
};

enum DEMO61_COLOR_MODE : UINT8
{
	DEMO61_COLOR_MODE_CYAN = 1,
	DEMO61_COLOR_MODE_MAGENTA = DEMO61_COLOR_MODE_CYAN << 1,
	DEMO61_COLOR_MODE_YELLOW = DEMO61_COLOR_MODE_MAGENTA << 1,
	DEMO61_COLOR_MODE_BLACK = DEMO61_COLOR_MODE_YELLOW << 1
};

enum DEMO61_ANIM_MODE : UINT8
{
	DEMO61_ANIM_MODE_MOVE_X = 1,
	DEMO61_ANIM_MODE_MOVE_Y = DEMO61_ANIM_MODE_MOVE_X << 1,
	DEMO61_ANIM_MODE_STOP = DEMO61_ANIM_MODE_MOVE_Y << 1,
	DEMO61_ANIM_MODE_RESET = DEMO61_ANIM_MODE_STOP << 1,
	DEMO61_ANIM_MODE_FOLLOW_TRAIL = DEMO61_ANIM_MODE_RESET << 1
};

struct SinParameters61
{
	float phase;
	float radius;
	BOOL bUp;

	void Reset()
	{
		phase = 0.f;
		radius = 100.f;
		bUp = TRUE;
	}

};

struct ZigzagParameters61
{
	float offsetX;
	float height;
	BOOL bDirection;
	BOOL bUp;

	void Reset()
	{
		offsetX = 0;
		height = 100;
		bDirection = TRUE;
		bUp = TRUE;
	}

};

struct PiParameters61
{
	float offsetX;
	float height;
	BOOL bDirection;
	BOOL bUp;

	void Reset()
	{
		offsetX = 0;
		height = 100;
		bDirection = TRUE;
		bUp = TRUE;
	}

};

struct SpringParameters61
{
	POINT center;
	float radius;
	BOOL bUp;

	void Reset()
	{
		center = POINT{ CUR_SCREEN_CENTER.x, CUR_SCREEN_CENTER.y };
		radius = 100.f;
		bUp = TRUE;
	}
};

class Demo6_1 : public Application
{
public:
	Demo6_1() {}
	virtual ~Demo6_1() {}

public:
	virtual BOOL Initialize() override;
	virtual void Update() override;
	virtual void Draw(HDC hDC) override;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static LONGLONG CALLBACK DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);


public:
	void OnCreate(HWND hWnd);
	void HandleMenu(WORD param);

public:
	void ProcessKeyboard();
	void ProcessMouse();

public:
	void DrawSin(HDC hDC);
	void DrawZigzag(HDC hDC);
	void DrawSpring(HDC hDC);
	void DrawPi(HDC hDC);

public:
	void SetDrawMode(DEMO61_DRAW_MODE mode) { m_drawMode = mode; }
	void SetColorMode(DEMO61_COLOR_MODE mode) { m_colorMode = mode; }
	void SetAnimationMode(DEMO61_ANIM_MODE mode) { m_animMode = mode; }
	void SetColorInvert(BOOL bInverted) { m_bInverted = bInverted; }


private:
	std::shared_ptr<ModalessDialog> m_pDialogBox = nullptr;

	SinParameters61 m_sin = {};
	ZigzagParameters61 m_zigzag = {};
	SpringParameters61 m_spring = {};
	PiParameters61 m_pi = {};

	UINT8 m_drawMode = DEMO61_DRAW_MODE_SIN;
	UINT8 m_colorMode = DEMO61_COLOR_MODE_BLACK;
	UINT8 m_animMode = DEMO61_ANIM_MODE_MOVE_X;
	BOOL m_bInverted = FALSE;
	COLORREF m_Color = RGB(0, 0, 0);
};

