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

	// WndProc will be in each application

	CoreDesc& GetDesc() { return m_Desc; }

private:
	CoreDesc m_Desc;

};

