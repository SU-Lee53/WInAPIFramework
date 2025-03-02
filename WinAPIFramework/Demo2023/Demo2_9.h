#pragma once
#include "../Application.h"

class TextBox;
class Caret;

class Demo2_9 : public Application
{
public:
	Demo2_9() {}
	virtual ~Demo2_9() {}

public:
	virtual BOOL Initialize() override;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	void OnCreate(HWND hWnd);
	void OnPaint();
	void OnChar(HWND hWnd, WPARAM wParam, LPARAM lParam);
	void OnKeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

private:
	void ProcessKeyboard(WPARAM wParam);

private:
	std::shared_ptr<shapes::Polygon> m_pHourGlass = nullptr;
	std::shared_ptr<shapes::Polygon> m_pPentagon = nullptr;
	std::shared_ptr<shapes::Ellipse> m_pPie = nullptr;
	std::shared_ptr<shapes::Polygon> m_pTriangle = nullptr;

	std::shared_ptr<shapes::Rectangle> m_pRectangle = nullptr;

	UINT m_Seleted = 0;
};

