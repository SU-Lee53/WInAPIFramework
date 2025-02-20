#include "pch.h"
#include "Caret.h"

BOOL Caret::Create(HWND hWnd, HBITMAP hBitmap, int nWidth, int nHeight)
{
	m_CurrentWndHandle = hWnd;
	m_hBitmap = hBitmap;
	m_width = nWidth;
	m_height = nHeight;

	return ::CreateCaret(m_CurrentWndHandle, m_hBitmap, m_width, m_height);
}

BOOL Caret::Show(HWND hWnd)
{
	BOOL bResult = TRUE;
	if (hWnd == NULL)
	{
		bResult = ::ShowCaret(m_CurrentWndHandle);
	}
	else
	{
		m_CurrentWndHandle = hWnd;
		bResult = ::ShowCaret(m_CurrentWndHandle);
	}

	return bResult;
}

BOOL Caret::SetPos(int x, int y)
{
	return ::SetCaretPos(x, y);
}

BOOL Caret::GetPos(LPPOINT lpPoint)
{
	return GetCaretPos(lpPoint);
}

BOOL Caret::SetBlinkTime(UINT mMSeconds)
{
	return SetCaretBlinkTime(mMSeconds);
}

UINT Caret::GetBlinkTime()
{
	return GetCaretBlinkTime();
}

BOOL Caret::Hide(HWND hWnd)
{
	BOOL bResult = TRUE;
	if (hWnd == NULL)
	{
		bResult = ::HideCaret(m_CurrentWndHandle);
	}
	else
	{
		m_CurrentWndHandle = hWnd;
		bResult = ::HideCaret(m_CurrentWndHandle);
	}

	return bResult;
}

BOOL Caret::Destroy()
{
	return ::DestroyCaret();
}
