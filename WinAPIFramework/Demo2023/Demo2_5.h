#pragma once
#include "../Application.h"

class TextBox;
class Caret;

// ĳ���� �̿��� �޸��� �����
// - Caret�� �ִ� �޸����� �ۼ�
// - �޸����� 10���α���, �� ���� �ִ� 30�� ���� ���� ����
// - �����츦 ���� ���� ��ܿ� ĳ���� �����̰� �ִ�.�� ��ġ�������� ���ڸ� �Է��Ѵ�.
// - ���ڰ� 30�� �̻� �Ǹ� ���� �ٷ� ��������.ĳ���� ���� ��������.
// - ���ڿ��� 10���� �� ����, ĳ���� ù ��, ù ��°�� �̵��ؼ� �ٽ� �Է��� �� �ִ�.ù �ٷ� �̵��Ͽ� �Է��ϸ� ������ �ִ� ���� ���� ����Ⱑ �ȴ�.
// - ���� Ű �ܿ�
// - ����Ű : ĳ���� �Ʒ��� �� ������ �̵��ϰ� �̵��� �ڸ��� �ٽ� �Է��� �� �ִ�.
// - �齺���̽� : ĳ���� �� ĭ ������ �̵��ϰ� �� �ڸ��� �ٽ� ���ڸ� �Է��� �� �ִ�.ù �� �� ���� ��ġ������ ������ �̵��� �� ����.

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

