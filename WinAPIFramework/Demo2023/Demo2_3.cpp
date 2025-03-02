#include "../pch.h"
#include "Demo2_3.h"
#include "../TextBox.h"
#include "../Utils.h"

using namespace std;

BOOL Demo2_3::Initialize()
{
    m_pProcFunction = WndProc;

    m_AppDesc.wndName = L"Demo2-3";
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

    m_pResultText->Initialize(C_RECT(50, 40, 200, 120), DT_SINGLELINE | DT_LEFT | DT_TOP);

    return 0;
}

void Demo2_3::OnPaint()
{
    if (!BeginAppPaint())
        __debugbreak();

    // 화면에 문자 그리기
    //      –(800, 600) 크기의 윈도우를 띄운다.
    //      – 네 개의 정수를 랜덤하게 구한다 :
    //          • x : 문자가 시작하는 x 좌표값(0 ~700 사이)
    //          • y : 문자가 시작하는 y 좌표값(0 ~500 사이)
    //          • n : 0 ~9 사이의 숫자
    //          • count : 숫자 n의 출력 개수(10 ~50 사이)
    //          • 문자 색과 배경색을 랜덤하게 설정한다.
    //      –(x, y) 좌표에 숫자 n을 count 만큼 출력한다.

    HDC& hDC = m_PaintResource.hDC;

    int x = RANDOM.GenerateRandom(0, 700);
    int y = RANDOM.GenerateRandom(0, 500);
    int n = RANDOM.GenerateRandom(0, 9);
    int count = RANDOM.GenerateRandom(10, 50);

    COLORREF textColor = RANDOM.GenerateRandomColor();
    COLORREF bkColor = RANDOM.GenerateRandomColor();

    m_pResultText->SetRect(RECT{ x, y, x + 500, y + 500 });
    m_pResultText->SetTextColor(textColor);
    m_pResultText->SetBackgroundColor(bkColor);

    std::wstring wstr = L"";
    for (int i = 0; i < count; i++)
    {
        wstr += ::to_wstring(n);
    }

    m_pResultText->Draw(hDC, wstr);

    
    if (!EndAppPaint())
        __debugbreak;
}

LRESULT Demo2_3::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
    std::shared_ptr<Demo2_3> pDemo = CUR_DEMO(Demo2_3);

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
