#pragma once
#include "../Application.h"

enum DEMO63_MODE
{
	DEMO63_MODE_DRAW_ROUTE,
	DEMO63_MODE_FOLLOW_ROUTE,
	DEMO63_MODE_FOLLOW_ROUTE_REVERSE,
	DEMO63_MODE_STOP
};

enum DEMO63_SHAPE
{
	DEMO63_SHAPE_ELLIPSE,
	DEMO63_SHAPE_RECTANGLE
};

class Demo6_3 : public Application
{
public:
	Demo6_3() {}
	virtual ~Demo6_3() {}

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
	void DrawRoute(HDC hDC);
	void DrawShape(HDC hDC);
	void UpdateShapePos();

	void SetDiagShowState(BOOL b) { m_bDiagShown = FALSE; }
	std::array<std::wstring, 3> GetTexts() { return m_TextArr; }
	void SetSelected(int idx) { m_curTextIndex = idx; }
	void SetShapeColor(COLORREF color) { m_shapeColor = color; }

	void SetDemoMode(DEMO63_MODE mode) { m_curMode = mode; }
	void SetShape(DEMO63_SHAPE mode) { m_curShape = mode; }
	void ResetRoute() { m_RoutePoints.clear(); }

private:
	ModalessDialog m_diag = {};
	BOOL m_bDiagShown = FALSE;

	std::vector<POINT> m_RoutePoints = {};
	std::array<std::wstring,3> m_TextArr = 
	{
		L"Hello",
		L"TUKorea",
		L"Windows"
	};
	int m_curTextIndex = 0;

	DEMO63_MODE m_curMode = DEMO63_MODE_DRAW_ROUTE;
	DEMO63_SHAPE m_curShape = DEMO63_SHAPE_ELLIPSE;
	COLORREF m_shapeColor = RGB(0, 0, 0);

	const static int MAX_POINT_COUNT = 7;

private:
	std::shared_ptr<shapes::Ellipse> m_pCircle = nullptr;
	std::shared_ptr<shapes::Rectangle> m_pRect = nullptr;

	POINT m_beginPoint = {};
	POINT m_endPoint = {};
	int m_curBeginPointIndex = 0;
	int m_curLineMovingProgress = 0;
	POINT m_curPos;

public:
	void ResetAnimVariables()
	{
		m_curBeginPointIndex = 0;
		m_curLineMovingProgress = 0;
	}

private:
	BOOL m_bDiagRectShown = FALSE;
	BOOL m_bDiagRectDirection = TRUE;	// T : ¿À¸¥ÂÊ, F : ¿ÞÂÊ
	RECT m_DiagRect = C_RECT(0, 350, 50, 400);
	POINT m_offset = { 0,0 };

public:
	BOOL GetDiagRectShow() { return m_bDiagRectShown; }
	void SetDiagRectShow(BOOL show) { m_bDiagRectShown = show; }
	void DrawDialogRect(HWND hDlg);

};

