#pragma once
#include "../Application.h"

class TextBox;

class Demo2_3 : public Application
{
public:
	Demo2_3() {}
	virtual ~Demo2_3() {}

public:
	virtual BOOL Initialize() override;

	static LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

public:
	void OnPaint();

private:
	std::shared_ptr<TextBox> m_pResultText;

};

