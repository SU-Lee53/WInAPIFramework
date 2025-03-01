#pragma once

class ChildControls
{
public:
	ChildControls() {}
	virtual ~ChildControls() {}


protected:
	HWND m_parentHwnd = 0;
	HWND m_hWnd = 0;
	RECT m_drawRect = {};
};

enum CHILD_BUTTON_TYPE
{
	CHILD_BUTTON_TYPE_BUTTON = BS_PUSHBUTTON,
	CHILD_BUTTON_TYPE_CHECK = BS_AUTOCHECKBOX,
	CHILD_BUTTON_TYPE_RADIO = BS_AUTORADIOBUTTON,
	CHILD_BUTTON_TYPE_GROUPBOX = BS_GROUPBOX
};

class ChildButton : public ChildControls
{
public:
	ChildButton() {}
	virtual ~ChildButton() {}

	BOOL Create(HWND parentHwnd, RECT drawRect, const std::wstring& showText, CHILD_BUTTON_TYPE type, int controlID);

private:
	const std::wstring m_wstrClassname = L"button";
	std::wstring m_showText = L"";
	int m_controlID = 0;
	CHILD_BUTTON_TYPE m_buttonType = CHILD_BUTTON_TYPE_BUTTON;
};

class ChildList : public ChildControls
{
public:
	ChildList() {}
	virtual ~ChildList() {}

	BOOL Create(HWND parentHwnd, RECT drawRect, const std::wstring& showText, int controlID, int listStyle = LBS_STANDARD);

	void AddString(const std::wstring& wstr);
	void InsertString(const std::wstring& wstr, int idx);
	void DeleteString(int idx);
	int GetCount();
	int GetCurrentSelected();
	void SetCurrentSelected(int idx);

private:
	const std::wstring m_wstrClassname = L"listbox";
	std::wstring m_showText = L"";
	int m_controlID = 0;


};

class ChildCombo : public ChildControls
{
public:
	ChildCombo() {}
	virtual ~ChildCombo() {}

	BOOL Create(HWND parentHwnd, RECT drawRect, const std::wstring& showText, int controlID, int comboStyle = CBS_DROPDOWN);

	void AddString(const std::wstring& wstr);
	void DeleteString(int idx);
	int GetCount();
	int GetCurrentSelected();
	void SetCurrentSelected(int idx);

private:
	const std::wstring m_wstrClassname = L"combobox";
	std::wstring m_showText = L"";
	int m_controlID = 0;


};

class ChildEdit : public ChildControls
{
public:
	ChildEdit() {}
	virtual ~ChildEdit() {}

	BOOL Create(HWND parentHwnd, RECT drawRect, const std::wstring& showText, int controlID, int editStyle = 0);

	std::wstring GetTextFromEdit();

private:
	const std::wstring m_wstrClassname = L"edit";
	std::wstring m_showText = L"";
	int m_controlID = 0;

};

enum CHILD_SCROLL_TYPE
{
	CHILD_SCROLL_TYPE_HORZ = SBS_HORZ,
	CHILD_SCROLL_TYPE_VERT = SBS_VERT
};

class ChildScrollBar : public ChildControls
{
public:
	ChildScrollBar() {}
	virtual ~ChildScrollBar() {}

	BOOL Create(HWND parentHwnd, RECT drawRect, const std::wstring& showText, CHILD_SCROLL_TYPE type, int controlID);

	BOOL SetScrollBarRange(int nMinPos, int nMaxPos, int nBar = SB_CTL, BOOL bRedraw = TRUE);
	int SetScrollBarPos(int nPos, int nBar = SB_CTL, BOOL bRedraw = TRUE);

private:
	const std::wstring m_wstrClassname = L"scrollbar";
	std::wstring m_showText = L"";
	int m_controlID = 0;

};

