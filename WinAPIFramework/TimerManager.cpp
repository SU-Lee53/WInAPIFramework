#include "pch.h"
#include "TimerManager.h"

using namespace std;

BOOL TimerManager::Initialize(HWND hWnd)
{
	m_hWnd = hWnd;
    m_Timers.clear();
    return 0;
}

UINT_PTR TimerManager::AddTimer(UINT nElapsec, TIMERPROC timerProc)
{
	unique_ptr<Timer> pTimer = make_unique<Timer>();   
	pTimer->Create(++m_nTimers, nElapsec, timerProc);
	m_Timers.insert(move(pTimer));
    return m_nTimers;
}

BOOL TimerManager::KillTimer(UINT_PTR& nTimerID)
{
	BOOL bResult = TRUE;

	auto it = find_if(m_Timers.begin(), m_Timers.end(), [&](const unique_ptr<Timer>& timer) { return timer->m_nTimerID == nTimerID; });
    if (it != m_Timers.end())
    {
        (*it)->Kill();
		m_Timers.erase(it);
    }
    else
    {
		bResult = FALSE;
    }

    return bResult;
}

BOOL TimerManager::KillAllTimers()
{
	for (auto& timer : m_Timers)
	{
		timer->Kill();
    }

	m_Timers.clear();

    return TRUE;
}

BOOL TimerManager::SetTimer(UINT_PTR& nTimerID)
{
    BOOL bResult = TRUE;

    auto it = find_if(m_Timers.begin(), m_Timers.end(), [&](const unique_ptr<Timer>& timer) { return timer->m_nTimerID == nTimerID; });
    if (it != m_Timers.end())
    {
        bResult = (*it)->Set(m_hWnd);
    }
    else
    {
        bResult = FALSE;
    }

    return bResult;
}