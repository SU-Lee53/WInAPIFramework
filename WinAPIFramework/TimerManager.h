#pragma once
#include "Timer.h"

class TimerManager
{
	DECLARE_SINGLE(TimerManager);

public:
	BOOL Initialize(HWND hWnd);

public:
	UINT_PTR AddTimer(UINT nElapse, TIMERPROC timerProc = NULL);
	BOOL KillTimer(UINT_PTR& nTimerID);
	BOOL KillAllTimers();
	BOOL SetTimer(UINT_PTR& nTimerID);

private:
	HWND m_hWnd = nullptr;
	std::unordered_set<std::unique_ptr<Timer>> m_Timers;
	UINT_PTR m_nTimers = 0;
};
