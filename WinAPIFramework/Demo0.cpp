#include "pch.h"
#include "Demo0.h"

BOOL Demo0::Initialize()
{
    m_pProcFunction = WndProc;

    m_AppDesc.wndSize.width = 800;
    m_AppDesc.wndSize.height = 600;
    m_AppDesc.wndName = L"Demo0";
    m_AppDesc.backgroundColor = BLACK_BRUSH;

    return 0;
}

LRESULT Demo0::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hDC;
    std::wstring temp = L"Hello World";
    int x = 0, y = 0;

    switch (message)
    {
    case WM_CREATE:
        break;

    case WM_PAINT:
        hDC = BeginPaint(CORE_DESC.hWnd, &ps);
        ::TextOut(hDC, x, y, temp.c_str(), temp.size());
        EndPaint(CORE_DESC.hWnd, &ps);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    default:
        break;
    }
    
    return DefWindowProc(handle, message, wParam, lParam);
}
