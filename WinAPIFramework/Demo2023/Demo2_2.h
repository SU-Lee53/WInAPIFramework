#pragma once
#include "../Application.h"

class TextBox;

class Demo2_2 : public Application
{
public:
	Demo2_2() {}
	virtual ~Demo2_2() {}

public:
	virtual BOOL Initialize() override;

	static LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

public:
	void OnPaint();

private:
	std::vector<std::shared_ptr<TextBox>> m_pTextboxs = {};

};

