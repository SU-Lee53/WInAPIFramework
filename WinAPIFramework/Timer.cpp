#include "pch.h"
#include "Timer.h"

BOOL Timer::Create(UINT_PTR timerID, UINT nElapse, TIMERPROC pTimeProc)
{
	m_nTimerID = timerID;
	m_nElapse = nElapse;
	m_pTimerProc = pTimeProc;

	return TRUE;
}

BOOL Timer::Set(HWND hWnd)
{
	UINT_PTR uiResult = ::SetTimer(hWnd, m_nTimerID, m_nElapse, m_pTimerProc);

	if (uiResult == 0)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL Timer::Kill()
{
	::KillTimer(NULL, m_nTimerID);
	return 0;
}
