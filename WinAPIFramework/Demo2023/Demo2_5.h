#pragma once
#include "../Application.h"

class TextBox;
class Caret;

// 캐럿을 이용한 메모장 만들기
// - Caret이 있는 메모장을 작성
// - 메모장은 10라인까지, 한 줄은 최대 30자 까지 저장 가능
// - 윈도우를 띄우면 좌측 상단에 캐럿이 깜빡이고 있다.그 위치에서부터 문자를 입력한다.
// - 문자가 30자 이상 되면 다음 줄로 내려간다.캐럿도 같이 내려간다.
// - 문자열이 10줄이 다 차면, 캐럿이 첫 줄, 첫 번째로 이동해서 다시 입력할 수 있다.첫 줄로 이동하여 입력하면 기존에 있던 문자 위에 덮어쓰기가 된다.
// - 문자 키 외에
// - 엔터키 : 캐럿이 아랫줄 맨 앞으로 이동하고 이동된 자리에 다시 입력할 수 있다.
// - 백스페이스 : 캐럿을 한 칸 앞으로 이동하고 그 자리에 다시 문자를 입력할 수 있다.첫 줄 맨 앞의 위치에서는 앞으로 이동할 수 없다.

class Demo2_5 : public Application
{
public:
	Demo2_5() {}
	virtual ~Demo2_5() {}

public:
	virtual BOOL Initialize() override;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	void OnCreate(HWND hWnd);
	void OnPaint();
	void OnChar(HWND hWnd, WPARAM wParam, LPARAM lParam);

	void WriteOnBack(WPARAM wParam);
	void Overwrite(WPARAM wParam);

private:
	std::shared_ptr<Caret> m_pCaret = nullptr;
	std::array<std::wstring, 10> m_pTextArr = {};
	std::shared_ptr<TextBox> m_pInputTextBox = nullptr;

	UINT m_uiCurLine = 0;
	UINT m_uiOverwriteIndex = 0;

	WndPosition m_CaretPos = { 0,0 };

	const UINT MAX_LINE_SIZE = 30;
	const WndPosition m_Offset = { 20, 20 };

	BOOL m_bOverwrite = FALSE;
};

