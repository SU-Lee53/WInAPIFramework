#pragma once
#include "Application.h"

class Demo0 : public Application
{
public:
	Demo0() {}
	virtual ~Demo0() {}

public:
	virtual BOOL Initialize() override;

	static LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

};

