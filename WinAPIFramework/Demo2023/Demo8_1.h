#pragma once
#include "../Application.h"

class TextBox;
class Caret;

class Demo8_1 : public Application
{
public:
	Demo8_1() {}
	virtual ~Demo8_1() {}

public:
	virtual BOOL Initialize() override;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	void OnCreate(HWND hWnd);
	void OnPaint();
	void OnChar(HWND hWnd, WPARAM wParam, LPARAM lParam);
	void OnKeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam);


	void WriteOnBack(WPARAM wParam);
	void Overwrite(WPARAM wParam);

private:
	// Key Process
	void ProcessEnter();
	void ProcessBackSpace();
	void ProcessEscape();
	void ProcessTab();
	void ProcessArrow(WPARAM wParam);
	void ProcessDelete();
	void ProcessHome();
	void ProcessEnd();
	void ProcessInsert();
	void ProcessChar(WPARAM wParam);
	void ProcessF1();


private:
	std::shared_ptr<Caret> m_pCaret = nullptr;
	std::array<std::wstring, 10> m_wstrTextArr = {};
	std::array<UINT, 10> m_uiTextSizeArr = {};
	std::shared_ptr<TextBox> m_pInputTextBox = nullptr;

	WndPosition m_CaretPos = { 0,0 };

	const UINT MAX_LINE_SIZE = 80;
	const WndPosition m_Offset = { 20, 20 };

	BOOL m_bUpperMode = FALSE;
	BOOL m_bOverwrite = FALSE;

public:
	BOOL Save(LPWSTR filePath);
	BOOL Load(LPWSTR filePath);

	OPENFILENAME m_saveStruct;
	OPENFILENAME m_loadStruct;

	std::wstring m_wstrFile = L"";
	LPTSTR m_wstrFilter = L"text(*.txt)\0*.txt\0";
};

