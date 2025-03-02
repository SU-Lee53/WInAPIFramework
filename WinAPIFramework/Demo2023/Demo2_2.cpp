#include "../pch.h"
#include "Demo2_2.h"
#include "../TextBox.h"

using namespace std;

BOOL Demo2_2::Initialize()
{
    m_pProcFunction = WndProc;

    m_AppDesc.wndName = L"Demo2-2";
    m_AppDesc.wndStyle = WS_OVERLAPPEDWINDOW;
    m_AppDesc.backgroundColor = WHITE_BRUSH;
    m_AppDesc.wndIcon = IDI_QUESTION;
    m_AppDesc.wndCursor = IDC_HAND;
    m_AppDesc.wndPosition.x = 100;
    m_AppDesc.wndPosition.y = 50;
    m_AppDesc.wndSize.width = 800;
    m_AppDesc.wndSize.height = 600;

    m_pTextboxs.resize(6);
    for (int y = 0; y < 2; y++)
    {
        int left = 0, top = 0, right = 0, bottom = 0;
        
        top = y * (600 / 2);
        bottom = top + (600 / 2);

        for (int x = 0; x < 3; x++)
        {
            left = x * (800 / 3);
            right = left + (800 / 3);

            int idx = (y * 3) + x;
            m_pTextboxs[idx] = make_shared<TextBox>();
            m_pTextboxs[idx]->Initialize(C_RECT(left, top, right, bottom), DT_TOP | DT_WORDBREAK, RANDOM.GenerateRandomColor(), RANDOM.GenerateRandomColor());
        }
    }

    return 0;
}

void Demo2_2::OnPaint()
{
    m_PaintResource.hDC = ::BeginPaint(CUR_HWND, &m_PaintResource.paintStruct);

    // 화면의 코너와 중앙에 문자 그리기
    //  – 윈도우를 800x600 크기로 띄운다
    //  – 윈도우의 네 위치를 랜덤하게 설정한 후 그 위치에 문장을 쓴다.
    //      • 랜덤한 위치는 10의 배수로 설정한다.
    //      • 문자 내용 : “1st sentence : (0, 0)”, “2nd sentence : (350, 200)”, “3rd sentence : (120, 540)”, “4th sentence : (380, 180)”,
    //  – 윈도우의 중앙에 한 문장을 쓴다.
    //      • 좌표값 : 각각의 문자가 시작하는 좌표값(x, y)
    //      • 화면의 중앙에 “center(400, 300)”이라는 문장을 쓴다.

    HDC& hDC = m_PaintResource.hDC;

    for (const auto& p : m_pTextboxs)
    {
        p->Draw(hDC, L"ABCDEFGHIJKLMNOPQRSTUVWXYZ", TEXTBOX_DRAW_TYPE_FILL_RECT);
    }



    ::EndPaint(CUR_HWND, &m_PaintResource.paintStruct);
}

LRESULT Demo2_2::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
    std::shared_ptr<Demo2_2> pDemo = CUR_DEMO(Demo2_2);

    switch (message)
    {
    case WM_CREATE:
        break;

    case WM_PAINT:
        pDemo->OnPaint();
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    default:
        break;
    }
    
    return DefWindowProc(handle, message, wParam, lParam);
}
