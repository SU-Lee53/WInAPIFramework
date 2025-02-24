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

	static std::wstring GenerateFormattedWString(LPCTSTR fmt, ...)
	{
		WCHAR lpOut[100];

		va_list fmtArgs;
		va_start(fmtArgs, fmt);

		::_vsnwprintf_s(lpOut, _countof(lpOut), _TRUNCATE, fmt, fmtArgs);

		va_end(fmtArgs);

		std::wstring res(lpOut);
		return res;
	}
	static std::string GenerateFormattedString(LPCSTR fmt, ...)
	{
		CHAR lpOut[100];

		va_list fmtArgs;
		va_start(fmtArgs, fmt);

		::_vsnprintf_s(lpOut, _countof(lpOut), fmt, fmtArgs);


		va_end(fmtArgs);

		std::string res(lpOut, _countof(lpOut));
		return res;
	}

	void CheckGDIUsage() 
	{
		DWORD processID = GetCurrentProcessId();
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, processID);
		if (hProcess) {
			DWORD gdiCount = GetGuiResources(hProcess, GR_GDIOBJECTS);
			std::cout << "GDI Objects: " << gdiCount << std::endl;
			CloseHandle(hProcess);
		}
	}
};