#pragma once
#include "../Application.h"

// PASS
// 진짜 모르겠음

class Calculator62
{
public:
	Calculator62() {}
	~Calculator62() {}

	void Create(int diagMacro);
	void Show();

public:
	void Update();
	void Draw();

public:
	void ProcessR();
	void ProcessCE();
	void ProcessC();
	void ProcessBinary();
	void ProcessInverse();
	void ProcessMul10();
	void ProcessPow10();
	void ProcessDel();

public:
	void AddText(wchar_t ch) { m_wstrCalcText.push_back(ch); }
	void SetText(const std::wstring& wstr) { m_wstrCalcText = wstr; }

public:
	static LONGLONG CALLBACK CalcProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);


private:
	std::shared_ptr<ModalessDialog> m_pDialogBox = nullptr;
	std::wstring m_wstrCalcText = L"";

};


class Demo6_2 : public Application
{
public:
	Demo6_2() {}
	virtual ~Demo6_2() {}

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
	std::shared_ptr<Calculator62> GetCalculator() { return m_pCalc; }

private:
	std::shared_ptr<Calculator62> m_pCalc = nullptr;
};

