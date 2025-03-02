#pragma once
#include "../Application.h"

class TextBox;
class Caret;

class Demo2_8 : public Application
{
public:
	Demo2_8() {}
	virtual ~Demo2_8() {}

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
	void ProcessEnter();				// DONE
	void ProcessBackSpace();			// DONE
	void ProcessEscape();				// DONE
	void ProcessTab();					// DONE
	void ProcessArrow(WPARAM wParam);	// DONE
	void ProcessDelete();				// DONE
	void ProcessHome();					// DONE
	void ProcessEnd();					// DONE
	void ProcessInsert();				// DONE
	void ProcessChar(WPARAM wParam);	// DONE
	void ProcessF1();					// DONE

	// Process Funtions for Demo2_8
	void ProcessF2();			
	void ProcessF3();					// DONE
	void ProcessF4();					// DONE
	void ProcessPageUp();				// DONE
	void ProcessPageDown();				// DONE
	void ProcessPlus();					// DONE
	void ProcessMinus();				// DONE

private:
	std::wstring RemoveBlank(const std::wstring& input);
	std::wstring WrapWord(const std::wstring& input);

private:
	std::shared_ptr<Caret> m_pCaret = nullptr;
	std::array<std::wstring, 10> m_wstrTextArr = {};
	std::array<UINT, 10> m_uiTextSizeArr = {};
	std::shared_ptr<TextBox> m_pInputTextBox = nullptr;

	WndPosition m_CaretPos = { 0,0 };

	const UINT MAX_LINE_SIZE = 80;
	const WndPosition m_Offset = { 20, 20 };

	std::array<std::wstring, 10> m_wstrPasswordArr = {};

	BOOL m_bWrapWordMode = FALSE;
	BOOL m_bRemoveBlankMode = FALSE;
	BOOL m_bPasswordMode = FALSE;
	BOOL m_bUpperMode = FALSE;
	BOOL m_bOverwrite = FALSE;
};

