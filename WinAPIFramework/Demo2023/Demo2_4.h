#pragma once
#include "../Application.h"

class TextBox;
class Caret;

class Demo2_4 : public Application
{
public:
	Demo2_4() {}
	virtual ~Demo2_4() {}

public:
	virtual BOOL Initialize() override;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	void OnCreate(HWND hWnd);
	void OnPaint();
	void OnChar(HWND hWnd, WPARAM wParam, LPARAM lParam);

	void ProcessInput();

private:
	std::shared_ptr<TextBox> m_pInputText = nullptr;
	std::shared_ptr<TextBox> m_pResultText = nullptr;
	std::shared_ptr<Caret> m_pCaret = nullptr;

	std::wstring m_wstrInput = L"";
	std::wstring m_wstrOutput = L"";
	UINT m_nChars = 0;

	UINT m_xPos = 0;
	UINT m_yPos = 0;
};

