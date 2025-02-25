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

	static COLORREF AddColorRef(COLORREF color1, COLORREF color2)
	{
		BYTE r = min(255, GetRValue(color1) + GetRValue(color2));
		BYTE g = min(255, GetGValue(color1) + GetGValue(color2));
		BYTE b = min(255, GetBValue(color1) + GetBValue(color2));

		return RGB(r, g, b);
	}

	static inline COLORREF InvertColor(COLORREF color)
	{
		BYTE r = 255 - GetRValue(color);
		BYTE g = 255 - GetGValue(color);
		BYTE b = 255 - GetBValue(color);

		return RGB(r, g, b);
	}

};