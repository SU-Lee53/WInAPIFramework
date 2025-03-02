#include "../pch.h"
#include "Demo2_1.h"
#include "../TextBox.h"

using namespace std;

BOOL Demo2_1::Initialize()
{
    m_pProcFunction = WndProc;

    m_AppDesc.wndName = L"Demo2-1";
    m_AppDesc.wndStyle = WS_OVERLAPPEDWINDOW;
    m_AppDesc.backgroundColor = WHITE_BRUSH;
    m_AppDesc.wndIcon = IDI_QUESTION;
    m_AppDesc.wndCursor = IDC_HAND;
    m_AppDesc.wndPosition.x = 100;
    m_AppDesc.wndPosition.y = 50;
    m_AppDesc.wndSize.width = 800;
    m_AppDesc.wndSize.height = 600;

    m_pResultText = make_shared<TextBox>();

    RECT rect;
    rect.left = 50;
    rect.top = 40;
    rect.right = 200;
    rect.bottom = 120;

    m_pResultText->Initialize(C_RECT(50, 40, 200, 120), DT_SINGLELINE | DT_CENTER | DT_VCENTER);


    return 0;
}

void Demo2_1::OnPaint()
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

    for (int i = 0; i < 4; i++)
    {
        int x = RANDOM.GenerateRandom(0, 80);
        int y = RANDOM.GenerateRandom(0, 60);

        x *= 10;
        y *= 10;

        if(i == 0)
        {
            TextBox::DrawFormattedString(hDC, { (ULONG)x, (ULONG)y }, L"%dst sentence : (%d, %d)", i + 1, x, y);
        }
        else if (i == 1)
        {
            TextBox::DrawFormattedString(hDC, { (ULONG)x, (ULONG)y }, L"%dnd sentence : (%d, %d)", i + 1, x, y);
        }
        else if (i == 2)
        {
            TextBox::DrawFormattedString(hDC, { (ULONG)x, (ULONG)y }, L"%drd sentence : (%d, %d)", i + 1, x, y);
        }
        else if (i == 3)
        {
            TextBox::DrawFormattedString(hDC, { (ULONG)x, (ULONG)y }, L"%dth sentence : (%d, %d)", i + 1, x, y);
        }

    }

    TextBox::DrawFormattedString(hDC, { 400,300 }, L"center(%d, %d)", 400, 300);


    ::EndPaint(CUR_HWND, &m_PaintResource.paintStruct);
}

LRESULT Demo2_1::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
    std::shared_ptr<Demo2_1> pDemo = CUR_DEMO(Demo2_1);

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
