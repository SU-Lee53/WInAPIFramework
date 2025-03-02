#pragma once
#include "../Application.h"

enum DEMO71_SHAPE_TYPE
{
	DEMO71_SHAPE_TYPE_ELLIPSE = 0,
	DEMO71_SHAPE_TYPE_RECTANGLE,
	DEMO71_SHAPE_TYPE_TRIANGLE
};

class Demo7_1 : public Application
{
public:
	Demo7_1() {}
	virtual ~Demo7_1() {}

public:
	virtual BOOL Initialize() override;

	void OnPaint();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK DrawChildProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static VOID CALLBACK AnimTimer(HWND hWnd, UINT message, UINT_PTR nElapse, DWORD);

public:
	void OnCreate(HWND hWnd);
	void HandleMenu(WORD param);

public:
	void ProcessKeyboard();
	void ProcessMouse();

public:
	void InitChildButtons(HWND hWnd);

public:
	// Draw Proc Functions
	void OnDrawWindowPaint();

public:
	// Button Processing
	void ProcessShapeButton(WPARAM wParam);
	void ProcessSizeButton(WPARAM wParam);
	void ProcessColorButton(WPARAM wParam);
	void ProcessChatting(WPARAM wParam);

	void UpdateBallPos();
	void DrawBall(HDC hDC);

private:
	DEMO71_SHAPE_TYPE m_shape = DEMO71_SHAPE_TYPE_ELLIPSE;
	COLORREF m_color = RGB(255, 0, 0);

	std::shared_ptr<shapes::Ellipse> m_pEllipse = nullptr;
	std::shared_ptr<shapes::Rectangle> m_pRect = nullptr;
	std::shared_ptr<shapes::Polygon> m_pTriangle = nullptr;
	std::vector<POINT> m_triPoints =
	{
		POINT{0, -250},
		POINT{250, 250},
		POINT{-250, 250}
	};

	POINT m_ballPos = {};
	float m_ballAnimDegree = 0;
	UINT_PTR m_animTimerID = 0;

private:
	// Childs
	std::shared_ptr<class ChildWindow> m_pDrawWindow = nullptr;

	std::shared_ptr<class ChildButton> m_pShapeGroupBox		= nullptr;
	std::shared_ptr<class ChildButton> m_pRadioEllipse		= nullptr;
	std::shared_ptr<class ChildButton> m_pRadioRectangle	= nullptr;
	std::shared_ptr<class ChildButton> m_pRadioTriangle		= nullptr;

	std::shared_ptr<class ChildButton> m_pSizeGroupBox		= nullptr;
	std::shared_ptr<class ChildButton> m_pRadioSmall		= nullptr;
	std::shared_ptr<class ChildButton> m_pRadioMedium		= nullptr;
	std::shared_ptr<class ChildButton> m_pRadioLarge		= nullptr;

	std::shared_ptr<class ChildButton> m_pColorGroupBox		= nullptr;
	std::shared_ptr<class ChildButton> m_pRadioRed			= nullptr;
	std::shared_ptr<class ChildButton> m_pRadioGreen		= nullptr;
	std::shared_ptr<class ChildButton> m_pRadioBlue			= nullptr;
	
	std::shared_ptr<class ChildEdit>	m_pEditChatWrite	= nullptr;
	std::shared_ptr<class ChildEdit>	m_pEditChatOut		= nullptr;
	std::shared_ptr<class ChildButton>	m_pButtonChatting	= nullptr;

	std::shared_ptr<class ChildButton> m_pButtonMove		= nullptr;
	std::shared_ptr<class ChildButton> m_pButtonPlus		= nullptr;
	std::shared_ptr<class ChildButton> m_pButtonMinus		= nullptr;
	std::shared_ptr<class ChildButton> m_pButtonStop		= nullptr;

};

