#pragma once
class Utils
{
public:
	static void ShowError()
	{
		DWORD error = GetLastError();
		char buffer[256];
		sprintf_s(buffer, 256, "Error occured : code %lu\n", error);
		OutputDebugStringA(buffer);
		__debugbreak();
	}
};

