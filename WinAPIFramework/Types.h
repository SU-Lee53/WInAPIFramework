#pragma once

struct WndSize
{
	DWORD width = 0;
	DWORD height = 0;
};

struct WndPosition
{
	union
	{
		DWORD x;
		DWORD row;
	};

	union
	{
		DWORD y;
		DWORD col;
	};
};

struct PenInfo
{
	int style = PS_SOLID;
	int width = 1;
	COLORREF color = RGB(0,0,0);
};