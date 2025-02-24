#include "pch.h"
#include "Core.h"
#include "Application.h"
#include "Utils.h"

WPARAM Core::RunWndProgram(const CoreDesc& appDesc)
{
	// Init Zone 1
	{
		m_Desc = appDesc;
		m_Desc.app->Initialize();
		RANDOM.Initialize();
	}

	m_WindowSize = WndSize{ m_Desc.app->GetAppDesc().wndSize.width, m_Desc.app->GetAppDesc().wndSize.height };

	MyRegisterClass();

	if (!InitInstance(SW_SHOW))
	{
		Utils::ShowError();
		return FALSE;
	}

	MSG msg = {};
	
	// Init Zone 2
	{
		INPUT.Initialize();
		TIME.Initialize();
	}

	if (m_Desc.app->GetAppDesc().appRunMode == APP_RUN_MODE_WNDPROC)
	{
		while (GetMessage(&msg, 0, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	else if (m_Desc.app->GetAppDesc().appRunMode == APP_RUN_MODE_GAME_LOOP)
	{
		while (msg.message != WM_QUIT)
		{
			if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				// Game Loop
				{
					Update();
					Draw();
				}
			}
		}
	}

	m_Desc.app->Destroy();


	return msg.wParam;
}

ATOM Core::MyRegisterClass()
{
	WNDCLASSEX wndClass;
	ZeroMemory(&wndClass, sizeof(wndClass));
	{
		wndClass.cbSize = sizeof(wndClass);
		wndClass.style = CS_HREDRAW | CS_VREDRAW;
		wndClass.lpfnWndProc = m_Desc.app->GetWndProc();
		wndClass.cbClsExtra = 0;
		wndClass.cbWndExtra = 0;
		wndClass.hInstance = m_Desc.hInstance;
		wndClass.hIcon = ::LoadIcon(NULL, m_Desc.app->GetAppDesc().wndIcon);
		wndClass.hCursor = ::LoadCursor(NULL, m_Desc.app->GetAppDesc().wndCursor);
		wndClass.hbrBackground = (HBRUSH)::GetStockObject(m_Desc.app->GetAppDesc().backgroundColor);
		wndClass.lpszMenuName = NULL;
		wndClass.lpszClassName = m_Desc.app->GetAppDesc().className.c_str();
		wndClass.hIconSm = LoadIcon(NULL, m_Desc.app->GetAppDesc().wndIconSmall);
	}

	return RegisterClassExW(&wndClass);
}

BOOL Core::InitInstance(int cmdShow)
{
	BOOL bResult = TRUE;

	RECT rect{ 0, 0, m_Desc.app->GetAppDesc().wndSize.width , m_Desc.app->GetAppDesc().wndSize.height };
	AdjustWindowRect(&rect, m_Desc.app->GetAppDesc().wndStyle, FALSE);

	int windowWidth = rect.right - rect.left;
	int windowHeight = rect.bottom - rect.top;

	m_Desc.hWnd = ::CreateWindow(
		m_Desc.app->GetAppDesc().className.c_str(),
		m_Desc.app->GetAppDesc().wndName.c_str(),
		m_Desc.app->GetAppDesc().wndStyle,
		m_Desc.app->GetAppDesc().wndPosition.x,
		m_Desc.app->GetAppDesc().wndPosition.y,
		windowWidth,
		windowHeight,
		NULL,
		NULL,
		m_Desc.hInstance,
		NULL
	);

	bResult = ::ShowWindow(m_Desc.hWnd, cmdShow);
	bResult = ::UpdateWindow(m_Desc.hWnd);

	return bResult;
}

void Core::Update()
{
	INPUT.Update();
	TIME.Update();


	m_Desc.app->Update();
}

void Core::Draw()
{
	m_Desc.app->BeginDoubleBuffering(m_Desc.hWnd);
	m_Desc.app->Draw(m_Desc.app->GetBackBuffer());
	m_Desc.app->EndDoubleBuffering(m_Desc.hWnd);

}
