#pragma once
#include "../Application.h"

class TextBox;
class Caret;

class Demo2_11 : public Application
{
public:
	Demo2_11() {}
	virtual ~Demo2_11() {}

public:
	virtual BOOL Initialize() override;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	void OnCreate(HWND hWnd);
	void OnPaint();
	void OnChar(HWND hWnd, WPARAM wParam, LPARAM lParam);
	void OnKeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

private:
	void ProcessArrow(WPARAM wParam);
	void ProcessPlus();
	void ProcessMinus();
	void ProcessF1();
	void ProcessF2();	
	void ProcessP();
	void ProcessN();
	void ProcessA();

	void ProcessChar(WPARAM wParam);

	void ProcessCommand(const std::wstring& wstrCommand, BOOL bIsFromPN);
	
private:
	std::shared_ptr<TextBox> m_pTextBox = nullptr;
	std::vector<std::shared_ptr<Shapes>> m_pShapes = {};

	std::wstring m_wstrInput = L"";
	std::wstring m_wstrErr = L"";

	std::vector<std::wstring> m_CommandRecord = {};
	std::wstring m_CommandForN = L"";
	

	const UINT MAX_SHAPE_COUNT = 10;
};

