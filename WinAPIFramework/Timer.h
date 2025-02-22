#pragma once

#include <functional>
#include <unordered_set>

class Application;

class Timer
{
public:
    Timer() {};
    ~Timer() {};

public:
	BOOL Create(UINT_PTR timerID, UINT nElapse, TIMERPROC pTimeProc = NULL);
    BOOL Set(HWND hWnd);
    BOOL Kill();
    
	void SetElapse(UINT nElapse) { m_nElapse = nElapse; }
	UINT GetElapse() const { return m_nElapse; }

	void SetTimerProc(TIMERPROC pTimeProc) { m_pTimerProc = pTimeProc; }
	TIMERPROC GetTimerProc() const { return m_pTimerProc; }

    bool operator==(const Timer& other) const 
    {
        return m_nTimerID == other.m_nTimerID;
    }
   
    friend class std::hash<Timer>;
    friend class TimerManager;

private:
    UINT_PTR m_nTimerID = 0;
    UINT m_nElapse = 0; // ms
    TIMERPROC m_pTimerProc = nullptr;
};

namespace std
{
    template<>
    struct hash<Timer>
    {
        std::size_t operator()(const Timer& t) const noexcept
        {
            return std::hash<UINT_PTR>()(t.m_nTimerID);
        }
    };
}

using TIMER_ID = UINT_PTR;