#include "../pch.h"
#include "Demo1_1.h"

using namespace std;

BOOL Demo1_1::Initialize()
{
    m_pProcFunction = WndProc;

    // • 윈도우의 타이틀을 “windows program 1”으로 설정하고,
    // • 기본 윈도우 형태로
    // • 배경색을 검정색으로
    // • 윈도우의 위치를(0, 0)에, 윈도우의 크기를 1280 * 800 으로 만들어 출력하기.

    m_AppDesc.wndSize.width = 1280;
    m_AppDesc.wndSize.height = 800;
    m_AppDesc.wndStyle = WS_OVERLAPPEDWINDOW;
    m_AppDesc.wndPosition.x = 0;
    m_AppDesc.wndPosition.y = 0;
    m_AppDesc.wndName = L"windows program 1";
    m_AppDesc.backgroundColor = BLACK_BRUSH;

    return 0;
}

void Demo1_1::_DrawText(const std::wstring& wstrOutText, int posX, int posY)
{
    m_PaintResource.hDC = BeginPaint(CORE_DESC.hWnd, &m_PaintResource.paintStruct);
    ::TextOut(m_PaintResource.hDC, posX, posY, wstrOutText.c_str(), wstrOutText.size());
    EndPaint(CORE_DESC.hWnd, &m_PaintResource.paintStruct);
}

LRESULT Demo1_1::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
    std::shared_ptr<Demo1_1> pDemo = CUR_DEMO(Demo1_1);

    switch (message)
    {
    case WM_CREATE:
        break;

    case WM_PAINT:
        pDemo->_DrawText(L"", 0, 0);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    default:
        break;
    }
    
    return DefWindowProc(handle, message, wParam, lParam);
}
