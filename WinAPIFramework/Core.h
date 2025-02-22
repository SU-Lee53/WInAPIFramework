#pragma once

struct CoreDesc
{
	HINSTANCE hInstance = 0;
	HWND hWnd = 0;
	std::shared_ptr<class Application> app = nullptr;
};

class Core
{
	DECLARE_SINGLE(Core);

public:
	WPARAM RunWndProgram(const CoreDesc& appDesc);
	ATOM MyRegisterClass();
	BOOL InitInstance(int cmdShow);

	void Update();
	void Draw();

	// WndProc will be in each application

	CoreDesc& GetDesc() { return m_Desc; }
	WndSize& GetWindowSize() { return m_WindowSize; }

private:
	CoreDesc m_Desc;

	// Cache window size
	WndSize m_WindowSize = {};

};

