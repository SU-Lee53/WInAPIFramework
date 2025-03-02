#pragma once
#include "../Application.h"

class Demo1_1 : public Application
{
public:
	Demo1_1() {}
	virtual ~Demo1_1() {}

public:
	virtual BOOL Initialize() override;

	static LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

private:
	void _DrawText(const std::wstring& wstrOutText, int posX, int posY);

};

