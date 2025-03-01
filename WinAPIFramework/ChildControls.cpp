#include "pch.h"
#include "ChildControls.h"

// ChildButton
///////////////////////////////////////////////////////////////////////////////

BOOL ChildButton::Create(HWND parentHwnd, RECT drawRect, const std::wstring& showText, CHILD_BUTTON_TYPE type, int controlID)
{
    m_parentHwnd = parentHwnd;
    m_drawRect = drawRect;
    m_showText = showText;
    m_buttonType = type;
    m_controlID = controlID;

    int width = m_drawRect.right - m_drawRect.left;
    int height = m_drawRect.bottom - m_drawRect.top;

    int buttonStyle = type;

    m_hWnd = ::CreateWindow(m_wstrClassname.c_str(), showText.c_str(), WS_CHILD | WS_VISIBLE | buttonStyle,
        drawRect.left, drawRect.top, width, height, parentHwnd, (HMENU)controlID, CUR_HINSTANCE, NULL);

    return (BOOL)m_hWnd;
}

// ChildList
///////////////////////////////////////////////////////////////////////////////

BOOL ChildList::Create(HWND parentHwnd, RECT drawRect, const std::wstring& showText, int controlID, int listStyle)
{
    m_parentHwnd = parentHwnd;
    m_drawRect = drawRect;
    m_showText = showText;
    m_controlID = controlID;

    int width = m_drawRect.right - m_drawRect.left;
    int height = m_drawRect.bottom - m_drawRect.top;

    m_hWnd = ::CreateWindow(m_wstrClassname.c_str(), showText.c_str(), WS_CHILD | WS_VISIBLE | listStyle,
        drawRect.left, drawRect.top, width, height, parentHwnd, (HMENU)controlID, CUR_HINSTANCE, NULL);

    return (BOOL)m_hWnd;
}

void ChildList::AddString(const std::wstring& wstr)
{
    ::SendMessage(m_hWnd, LB_ADDSTRING, 0, (LPARAM)wstr.c_str());
}

void ChildList::InsertString(const std::wstring& wstr, int idx)
{
    ::SendMessage(m_hWnd, LB_INSERTSTRING, (WPARAM)idx, (LPARAM)wstr.c_str());
}

void ChildList::DeleteString(int idx)
{
    ::SendMessage(m_hWnd, LB_DELETESTRING, (WPARAM)idx, 0);
}

int ChildList::GetCount()
{
    return ::SendMessage(m_hWnd, LB_GETCOUNT, 0, 0);
}

int ChildList::GetCurrentSelected()
{
    return ::SendMessage(m_hWnd, LB_GETCURSEL, 0, 0);
}

void ChildList::SetCurrentSelected(int idx)
{
    ::SendMessage(m_hWnd, LB_SETCURSEL, (WPARAM)idx, 0);
}

// ChildCombo
///////////////////////////////////////////////////////////////////////////////

BOOL ChildCombo::Create(HWND parentHwnd, RECT drawRect, const std::wstring& showText, int controlID, int comboStyle)
{
    m_parentHwnd = parentHwnd;
    m_drawRect = drawRect;
    m_showText = showText;
    m_controlID = controlID;

    int width = m_drawRect.right - m_drawRect.left;
    int height = m_drawRect.bottom - m_drawRect.top;

    m_hWnd = ::CreateWindow(m_wstrClassname.c_str(), showText.c_str(), WS_CHILD | WS_VISIBLE | comboStyle,
        drawRect.left, drawRect.top, width, height, parentHwnd, (HMENU)controlID, CUR_HINSTANCE, NULL);

    return (BOOL)m_hWnd;
}

void ChildCombo::AddString(const std::wstring& wstr)
{
    ::SendMessage(m_hWnd, CB_ADDSTRING, 0, (LPARAM)wstr.c_str());
}

void ChildCombo::DeleteString(int idx)
{
    ::SendMessage(m_hWnd, CB_DELETESTRING, (WPARAM)idx, 0);
}

int ChildCombo::GetCount()
{
    return ::SendMessage(m_hWnd, CB_GETCOUNT, 0, 0);
}

int ChildCombo::GetCurrentSelected()
{
    return ::SendMessage(m_hWnd, CB_GETCURSEL, 0, 0);
}

void ChildCombo::SetCurrentSelected(int idx)
{
    ::SendMessage(m_hWnd, CB_SETCURSEL, (WPARAM)idx, 0);
}

// ChildEdit
///////////////////////////////////////////////////////////////////////////////

BOOL ChildEdit::Create(HWND parentHwnd, RECT drawRect, const std::wstring& showText, int controlID, int editStyle)
{
    m_parentHwnd = parentHwnd;
    m_drawRect = drawRect;
    m_showText = showText;
    m_controlID = controlID;

    int width = m_drawRect.right - m_drawRect.left;
    int height = m_drawRect.bottom - m_drawRect.top;

    m_hWnd = ::CreateWindow(m_wstrClassname.c_str(), showText.c_str(), WS_CHILD | WS_VISIBLE | WS_BORDER | editStyle,
        drawRect.left, drawRect.top, width, height, parentHwnd, (HMENU)controlID, CUR_HINSTANCE, NULL);

    return (BOOL)m_hWnd;
}

std::wstring ChildEdit::GetTextFromEdit()
{
    TCHAR str[100];
    GetDlgItemText(m_parentHwnd, m_controlID, str, 100);

    return std::wstring(str);
}

// ChildScrollBar
///////////////////////////////////////////////////////////////////////////////

BOOL ChildScrollBar::Create(HWND parentHwnd, RECT drawRect, const std::wstring& showText, CHILD_SCROLL_TYPE type, int controlID)
{
    m_parentHwnd = parentHwnd;
    m_drawRect = drawRect;
    m_showText = showText;
    m_controlID = controlID;

    int width = m_drawRect.right - m_drawRect.left;
    int height = m_drawRect.bottom - m_drawRect.top;

    m_hWnd = ::CreateWindow(m_wstrClassname.c_str(), showText.c_str(), WS_CHILD | WS_VISIBLE | WS_BORDER | type,
        drawRect.left, drawRect.top, width, height, parentHwnd, (HMENU)controlID, CUR_HINSTANCE, NULL);

    return (BOOL)m_hWnd;
}

BOOL ChildScrollBar::SetScrollBarRange(int nMinPos, int nMaxPos, int nBar, BOOL bRedraw)
{
    return ::SetScrollRange(m_hWnd, nBar, nMinPos, nMaxPos, bRedraw);
}

int ChildScrollBar::SetScrollBarPos(int nPos, int nBar, BOOL bRedraw)
{
    return SetScrollPos(m_hWnd, nBar, nPos, bRedraw);
}
