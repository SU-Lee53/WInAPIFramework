#include "../pch.h"
#include "Demo1_2.h"

using namespace std;

BOOL Demo1_2::Initialize()
{
    m_pProcFunction = WndProc;

    // • 윈도우의 타이틀을 “windows program 2”로 설정하고,
    // • 시스템 메뉴, 최대, 최소화 버튼, 수평 / 수직 스크롤 바를 가지고 있고, 크기가 조정 가능한
    // • 배경색을 하얀색으로
    // • 윈도우를 위치(100, 50)에, 윈도우의 크기를 800 * 600 으로 만들어 출력하기.
    // • 스몰 아이콘을 물음표로, 커서는 손 모양으로 설정하기
;
    m_AppDesc.wndName = L"Demo1-1";
    m_AppDesc.wndStyle = WS_OVERLAPPED | WS_HSCROLL | WS_VSCROLL | WS_SYSMENU | WS_THICKFRAME;
    m_AppDesc.backgroundColor = WHITE_BRUSH;
    m_AppDesc.wndIcon = IDI_QUESTION;
    m_AppDesc.wndCursor = IDC_HAND;
    m_AppDesc.wndPosition.x = 100;
    m_AppDesc.wndPosition.y = 50;
    m_AppDesc.wndSize.width = 800;
    m_AppDesc.wndSize.height = 600;

    return 0;
}

void Demo1_2::_DrawText(const std::wstring& wstrOutText, int posX, int posY)
{
    m_PaintResource.hDC = BeginPaint(CORE_DESC.hWnd, &m_PaintResource.paintStruct);
    ::TextOut(m_PaintResource.hDC, posX, posY, wstrOutText.c_str(), wstrOutText.size());
    EndPaint(CORE_DESC.hWnd, &m_PaintResource.paintStruct);
}

LRESULT Demo1_2::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
    std::shared_ptr<Demo1_2> pDemo = CUR_DEMO(Demo1_2);

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
