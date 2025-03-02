#include "../pch.h"
#include "Demo2_9.h"
#include "../TextBox.h"
#include "../Utils.h"
#include "../Caret.h"

using namespace std;
using namespace shapes;

BOOL Demo2_9::Initialize()
{
    m_pProcFunction = WndProc;

    m_AppDesc.wndName = L"Demo2-9";
    m_AppDesc.wndStyle = WS_OVERLAPPEDWINDOW;
    m_AppDesc.backgroundColor = WHITE_BRUSH;
    m_AppDesc.wndIcon = IDI_APPLICATION;
    m_AppDesc.wndCursor = IDC_ARROW;
    m_AppDesc.wndPosition.x = 100;
    m_AppDesc.wndPosition.y = 50;
    m_AppDesc.wndSize.width = 1200;
    m_AppDesc.wndSize.height = 800;

    return 0;
}

void Demo2_9::OnCreate(HWND hWnd)
{
    BOOL bResult = TRUE;

    m_pTriangle = make_shared<shapes::Polygon>();
    std::vector<POINT> triPoints = { {0, -50}, {-50, 50}, {50, 50} };
    m_pTriangle->Create(triPoints);
    m_pTriangle->SetOffset({ -300, 0 });
    m_pTriangle->SetBackgroundColor(RANDOM.GenerateRandomColor());
    
    m_pHourGlass = make_shared<shapes::Polygon>();
    std::vector<POINT> hgPoints = { {-50, 50}, {50, 50}, {-50, -50}, {50, -50} };
    m_pHourGlass->Create(hgPoints);
    m_pHourGlass->SetOffset({ 0, -230 });
    m_pHourGlass->SetBackgroundColor(RANDOM.GenerateRandomColor());
    
    m_pPentagon = make_shared<shapes::Polygon>();
    std::vector<POINT> pentagonPoints = { {0, -50}, {-60, -10}, {-40, 50}, {40, 50}, {60, -10} };
    m_pPentagon->Create(pentagonPoints);
    m_pPentagon->SetOffset({ 300, 0 });
    m_pPentagon->SetBackgroundColor(RANDOM.GenerateRandomColor());
    
    m_pPie = make_shared<shapes::Ellipse>();
    m_pPie->Create(WndSize{100, 100});
    m_pPie->SetOffset({ 0, 230 });
    m_pPie->SetBackgroundColor(RANDOM.GenerateRandomColor());
    
    m_pRectangle = make_shared<shapes::Rectangle>();
    m_pRectangle->Create(WndSize{100, 100});

    if (!bResult) __debugbreak();
}

void Demo2_9::OnPaint()
{
    HDC hDC = BeginAppPaint();
    if (!hDC)
        __debugbreak();

    // DrawAll Each

    // 0
    m_pHourGlass->SetScale({ 2, 2 });
    if (m_Seleted == 0)
    {
        m_pHourGlass->SetFrameWidth(5);
        m_pHourGlass->Draw(hDC);
        m_pHourGlass->SetFrameWidth(1);
    }
    else
    {
        m_pHourGlass->SetFrameWidth(1);
        m_pHourGlass->Draw(hDC);
    }

    // 1
    m_pPentagon->SetScale({2,2});
    if (m_Seleted == 1)
    {
        m_pPentagon->SetFrameWidth(5);
        m_pPentagon->Draw(hDC);
        m_pPentagon->SetFrameWidth(1);
    }
    else
    {
        m_pPentagon->SetFrameWidth(1);
        m_pPentagon->Draw(hDC);
    }

    // 2
    m_pPie->SetScale({ 2,2 });
    if (m_Seleted == 2)
    {
        m_pPie->SetFrameWidth(5);
        m_pPie->Draw(hDC);
        m_pPie->SetFrameWidth(1);
    }
    else
    {
        m_pPie->SetFrameWidth(1);
        m_pPie->Draw(hDC);
    }

    // 3
    m_pTriangle->SetScale({2, 2});
    if (m_Seleted == 3)
    {
        m_pTriangle->SetFrameWidth(5);
        m_pTriangle->Draw(hDC);
        m_pTriangle->SetFrameWidth(1);
    }
    else
    {
        m_pTriangle->SetFrameWidth(1);
        m_pTriangle->Draw(hDC);
    }

    // center
    m_pRectangle->SetScale({ 2,2 });
    m_pRectangle->Draw(hDC);

    // DrawAll Selected
    if (m_Seleted == 0)
    {
        POINT beforeOffset = m_pHourGlass->GetOffset();
        POINT beforeScale = m_pHourGlass->GetScale();
        m_pHourGlass->SetOffset({ 0,0 });
        m_pHourGlass->SetScale({ 1,1 });
        m_pHourGlass->Draw(hDC);
        m_pHourGlass->SetOffset(beforeOffset);
        m_pHourGlass->SetScale(beforeScale);
    }
    else if (m_Seleted == 1)
    {
        POINT beforeOffset = m_pPentagon->GetOffset();
        POINT beforeScale = m_pPentagon->GetScale();
        m_pPentagon->SetOffset({ 0,0 });
        m_pPentagon->SetScale({ 1,1 });
        m_pPentagon->Draw(hDC);
        m_pPentagon->SetOffset(beforeOffset);
        m_pPentagon->SetScale(beforeScale);
    }
    else if (m_Seleted == 2)
    {
        POINT beforeOffset = m_pPie->GetOffset();
        POINT beforeScale = m_pPie->GetScale();
        m_pPie->SetOffset({ 0,0 });
        m_pPie->SetScale({ 1,1 });
        m_pPie->Draw(hDC);
        m_pPie->SetOffset(beforeOffset);
        m_pPie->SetScale(beforeScale);
    }
    else if (m_Seleted == 3)
    {
        POINT beforeOffset = m_pTriangle->GetOffset();
        POINT beforeScale = m_pTriangle->GetScale();
        m_pTriangle->SetOffset({ 0,0 });
        m_pTriangle->SetScale({ 1,1 });
        m_pTriangle->Draw(hDC);
        m_pTriangle->SetOffset(beforeOffset);
        m_pTriangle->SetScale(beforeScale);
    }


    if (!EndAppPaint())
        __debugbreak;
}

void Demo2_9::OnChar(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    switch (wParam)
    {

    default:
        ProcessKeyboard(wParam);
        break;

    }


    ::InvalidateRect(CUR_HWND, NULL, TRUE);
}

void Demo2_9::OnKeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    switch (wParam)
    {
    case VK_UP:
        m_Seleted = 0;
        m_pHourGlass->SetBackgroundColor(RANDOM.GenerateRandomColor());
        break;

    case VK_RIGHT:
        m_Seleted = 1;
        m_pPentagon->SetBackgroundColor(RANDOM.GenerateRandomColor());
        break;

    case VK_DOWN:
        m_Seleted = 2;
        m_pPie->SetBackgroundColor(RANDOM.GenerateRandomColor());
        break;

    case VK_LEFT:
        m_Seleted = 3;
        m_pTriangle->SetBackgroundColor(RANDOM.GenerateRandomColor());
        break;

        break;

    default:
        break;
    }

    ::InvalidateRect(CUR_HWND, NULL, TRUE);
}

void Demo2_9::ProcessKeyboard(WPARAM wParam)
{
    if (wParam == L's' || wParam == L'S')
    {
        m_Seleted = 0;
        m_pHourGlass->SetBackgroundColor(RANDOM.GenerateRandomColor());
    }
    else if (wParam == L'p' || wParam == L'P')
    {
        m_Seleted = 1;
        m_pPentagon->SetBackgroundColor(RANDOM.GenerateRandomColor());
    }
    else if (wParam == L'e' || wParam == L'E')
    {
        m_Seleted = 2;
        m_pPie->SetBackgroundColor(RANDOM.GenerateRandomColor());
    }
    else if (wParam == L't' || wParam == L'T')
    {
        m_Seleted = 3;
        m_pTriangle->SetBackgroundColor(RANDOM.GenerateRandomColor());
    }
}

LRESULT Demo2_9::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    std::shared_ptr<Demo2_9> pDemo = CUR_DEMO(Demo2_9);

    switch (message)
    {
    case WM_CREATE:
        pDemo->OnCreate(hWnd);
        break;

    case WM_PAINT:
        pDemo->OnPaint();
        break;

    case WM_KEYDOWN:
        pDemo->OnKeyDown(hWnd, wParam, lParam);
        break;
        
    case WM_CHAR:
        pDemo->OnChar(hWnd, wParam, lParam);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    default:
        break;
    }
    
    return DefWindowProc(hWnd, message, wParam, lParam);
}
