#pragma once

class TimeManager
{
	DECLARE_SINGLE(TimeManager)

public:
	void Initialize();
	void Update();

public:
	UINT32 GetFps() { return _fps; }
	float GetDeltaTime() { return _deltaTime; }

	UINT64 GetCurrent()
	{
		UINT64 currentCount;
		::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentCount));
		return currentCount;
	}

	LARGE_INTEGER* GetFrequency() { return reinterpret_cast<LARGE_INTEGER*>(&_frequency); }

private:
	UINT64	_frequency = 0;
	UINT64	_prevCount = 0;
	float	_deltaTime = 0.f;

private:
	UINT32	_frameCount = 0;
	UINT32	_fps = 0;
	float	_frameTime = 0.f;
};
