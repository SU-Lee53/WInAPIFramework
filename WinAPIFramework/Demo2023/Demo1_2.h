#pragma once
#include "../Application.h"

class Demo1_2 : public Application
{
public:
	Demo1_2() {}
	virtual ~Demo1_2() {}

public:
	virtual BOOL Initialize() override;

	static LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

private:
	void _DrawText(const std::wstring& wstrOutText, int posX, int posY);

};

