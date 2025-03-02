#pragma once
#include "../Application.h"

class TextBox;
class Caret;

enum BOARD_DRAW_MODE
{
	BOARD_DRAW_MODE_SMALL = 0,
	BOARD_DRAW_MODE_MEDIUM,
	BOARD_DRAW_MODE_LARGE
};

enum SHAPE_TYPE
{
	SHAPE_TYPE_RECTANGLE = 0,
	SHAPE_TYPE_ELLIPSE,
	SHAPE_TYPE_TRIANGLE,
	SHAPE_TYPE_NONE
};

class Demo2_12 : public Application
{
public:
	Demo2_12() {}
	virtual ~Demo2_12() {}

public:
	virtual BOOL Initialize() override;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	void OnCreate(HWND hWnd);
	void OnPaint();
	void OnChar(HWND hWnd, WPARAM wParam, LPARAM lParam);
	void OnKeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

	void ProcessChar(WPARAM wParam);

private:
	void ProcessS();	// DONE
	void ProcessM();	// DONE
	void ProcessL();	// DONE

	void ProcessE();
	void ProcessT();
	void ProcessR();
	void ProcessC();
	void ProcessD();
	void ProcessP();
	void ProcessQ();
	void ProcessNum(WPARAM wParam);

	void ProcessArrow(WPARAM wParam);
	void ProessPlus();
	void ProcessMinus();

private:
	void DrawBoard(HDC hDC);
	void DrawShapes(HDC hDC);

private:
	std::shared_ptr<shapes::Rectangle> m_pBoardRect = nullptr;
	std::vector<std::shared_ptr<Shapes>> m_pShapes = {};
	std::array<SHAPE_TYPE, 10> m_ShapeTypes = {};
	std::array<COLORREF, 10> m_ColorStored = {};

	size_t m_Selected = 0;

	std::wstring m_wstrErr = L"";

	BOARD_DRAW_MODE m_DrawMode = BOARD_DRAW_MODE_MEDIUM;
	LONG m_lBoardSize = 0;
	LONG m_nRowCols = 0;

	BOOL m_bColorChanged = FALSE;
};

