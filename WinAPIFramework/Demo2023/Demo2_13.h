#pragma once
#include "../Application.h"

class TextBox;
class Caret;

class Demo2_13 : public Application
{
public:
	Demo2_13() {}
	virtual ~Demo2_13() {}

public:
	virtual BOOL Initialize() override;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	void OnCreate(HWND hWnd);
	void OnPaint();
	void OnChar(HWND hWnd, WPARAM wParam, LPARAM lParam);
	void OnKeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

private:
	void ProcessChar(WPARAM wParam);

private:
	void ResetGame();
	void QuitGame();

private:
	std::vector<std::shared_ptr<Shapes>> m_pHangBase = {};
	std::vector<std::shared_ptr<Shapes>> m_pHangMan = {};

	decltype(m_pHangMan)::size_type m_FailCount = 0;

	std::shared_ptr<TextBox> m_pTextBox = nullptr;
	std::wstring m_wstrOutput = L"";

	BOOL m_bShowAnswser = FALSE;

private:
	std::array<std::wstring, 10> m_Words =
	{
		L"HELLO",
		L"WORLD",
		L"APPLE",
		L"HANGMAN",
		L"WINDOWS",
		L"PROGRAM",
		L"VISUAL",
		L"STUDIO",
		L"DEVELOPER",
		L"MICROSOFT"
	};

	decltype(m_Words)::size_type m_WordSelected = 0;
	BOOL m_bGameEnded = FALSE;
	BOOL m_bGameWin = FALSE;
};

