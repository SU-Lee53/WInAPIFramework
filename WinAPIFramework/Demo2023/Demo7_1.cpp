#include "../pch.h"
#include "Demo7_1.h"
#include "../TextBox.h"
#include "../Utils.h"
#include "../Caret.h"
#include "../GameBoard.h"
#include "../resource.h"
#include "../ChildControls.h"
#include "../ChildWindow.h"

using namespace std;
using namespace shapes;

#define IDC_GROUPBOX_SHAPE             100
#define IDC_RADIO_SHAPES_ELLIPSE        101
#define IDC_RADIO_SHAPES_RECTANGLE      102
#define IDC_RADIO_SHAPES_TRIANGLE       103

#define IDC_GROUPBOX_SIZE               104
#define IDC_RADIO_SIZE_SMALL            105
#define IDC_RADIO_SIZE_MEDIUM           106
#define IDC_RADIO_SIZE_LARGE            107

#define IDC_GROUPBOX_COLOR              108
#define IDC_RADIO_COLOR_RED             109
#define IDC_RADIO_COLOR_GREEN           110
#define IDC_RADIO_COLOR_BLUE            111

#define IDC_BUTTON_CHATTING             112
#define IDC_BUTTON_MOVE                 113
#define IDC_BUTTON_PLUS                 114
#define IDC_BUTTON_MINUS                115
#define IDC_BUTTON_STOP                 116

#define IDC_EDIT_CHAT_WRITE             117
#define IDC_EDIT_CHAT_OUT               118

BOOL Demo7_1::Initialize()
{
    m_pProcFunction = WndProc;

    m_AppDesc.wndName = L"Demo7-1";
    m_AppDesc.wndStyle = WS_OVERLAPPEDWINDOW;
    m_AppDesc.backgroundColor = GRAY_BRUSH;
    m_AppDesc.wndIcon = IDI_APPLICATION;
    m_AppDesc.wndCursor = IDC_ARROW;
    m_AppDesc.wndPosition.x = 100;
    m_AppDesc.wndPosition.y = 10;
    m_AppDesc.wndSize.width = 1200;
    m_AppDesc.wndSize.height = 900;
	m_AppDesc.appRunMode = APP_RUN_MODE_WNDPROC;

    return 0;
}

void Demo7_1::OnPaint()
{
    PAINTSTRUCT ps = {};
    HDC hDC = ::BeginPaint(CUR_HWND, &ps);

    DrawCoord(hDC);

    ::EndPaint(CUR_HWND, &ps);
}

void Demo7_1::OnCreate(HWND hWnd)
{
    BOOL bResult = TRUE;
    TIMER.Initialize(hWnd);

    ChildWindowDesc desc;
    {
        desc.wndPosition = WndPosition{ 50, 50 };
        desc.wndSize = WndSize{ 800, 800 };
        desc.wndStyle = WS_CHILD | WS_VISIBLE | WS_BORDER | WS_THICKFRAME;
        desc.wndIcon = IDI_APPLICATION;
        desc.wndIconSmall = IDI_APPLICATION;
        desc.wndCursor = IDC_ARROW;
        desc.className = L"childWindow";
        desc.wndName = L"";
        desc.menuName = 0;
        desc.backgroundColor = WHITE_BRUSH;
    }

    m_pDrawWindow = make_shared<ChildWindow>();
    m_pDrawWindow->Register(desc, hWnd, DrawChildProc);
    m_pDrawWindow->Create();

    m_pEllipse = make_shared<shapes::Ellipse>();
    m_pEllipse->Create(C_RECT(-250, -250, 250, 250));
    
    m_pRect = make_shared<shapes::Rectangle>();
    m_pRect->Create(C_RECT(-250, -250, 250, 250));
    
    m_pTriangle = make_shared<shapes::Polygon>();
    m_pTriangle->Create(m_triPoints);

    InitChildButtons(hWnd);


    m_animTimerID = TIMER.AddTimer(100, AnimTimer);
    TIMER.SetTimer(m_animTimerID);

    if (!bResult) __debugbreak();
}

void Demo7_1::InitChildButtons(HWND hWnd)
{
    // Shapes Radio
    {
        m_pShapeGroupBox = make_shared<ChildButton>();
        m_pShapeGroupBox->Create(hWnd, C_RECT(900, 50, 1100, 200), L"Shape", CHILD_BUTTON_TYPE_GROUPBOX, IDC_GROUPBOX_SHAPE);

        m_pRadioEllipse = make_shared<ChildButton>();
        m_pRadioEllipse->Create(hWnd, C_RECT(910, 100, 1000, 120), L"Ellipse", CHILD_BUTTON_TYPE_RADIO, IDC_RADIO_SHAPES_ELLIPSE);

        m_pRadioRectangle = make_shared<ChildButton>();
        m_pRadioRectangle->Create(hWnd, C_RECT(910, 120, 1000, 140), L"Rectangle", CHILD_BUTTON_TYPE_RADIO, IDC_RADIO_SHAPES_RECTANGLE);

        m_pRadioTriangle = make_shared<ChildButton>();
        m_pRadioTriangle->Create(hWnd, C_RECT(910, 140, 1000, 160), L"Triangle", CHILD_BUTTON_TYPE_RADIO, IDC_RADIO_SHAPES_TRIANGLE);
    }
    
    // Size Radio
    {
        m_pShapeGroupBox = make_shared<ChildButton>();
        m_pShapeGroupBox->Create(hWnd, C_RECT(900, 250, 1100, 400), L"Size", CHILD_BUTTON_TYPE_GROUPBOX, IDC_GROUPBOX_SIZE);

        m_pRadioSmall = make_shared<ChildButton>();
        m_pRadioSmall->Create(hWnd, C_RECT(910, 300, 1000, 320), L"Small", CHILD_BUTTON_TYPE_RADIO, IDC_RADIO_SIZE_SMALL);

        m_pRadioMedium = make_shared<ChildButton>();
        m_pRadioMedium->Create(hWnd, C_RECT(910, 320, 1000, 340), L"Medium", CHILD_BUTTON_TYPE_RADIO, IDC_RADIO_SIZE_MEDIUM);

        m_pRadioLarge = make_shared<ChildButton>();
        m_pRadioLarge->Create(hWnd, C_RECT(910, 340, 1000, 360), L"Large", CHILD_BUTTON_TYPE_RADIO, IDC_RADIO_SIZE_LARGE);
    }
    
    // Color Radio
    {
        m_pColorGroupBox = make_shared<ChildButton>();
        m_pColorGroupBox->Create(hWnd, C_RECT(900, 450, 1100, 600), L"Color", CHILD_BUTTON_TYPE_GROUPBOX, IDC_GROUPBOX_SIZE);

        m_pRadioRed = make_shared<ChildButton>();
        m_pRadioRed->Create(hWnd, C_RECT(910, 500, 1000, 520), L"Red", CHILD_BUTTON_TYPE_RADIO, IDC_RADIO_COLOR_RED);

        m_pRadioGreen = make_shared<ChildButton>();
        m_pRadioGreen->Create(hWnd, C_RECT(910, 520, 1000, 540), L"Green", CHILD_BUTTON_TYPE_RADIO, IDC_RADIO_COLOR_GREEN);

        m_pRadioBlue = make_shared<ChildButton>();
        m_pRadioBlue->Create(hWnd, C_RECT(910, 540, 1000, 560), L"Blue", CHILD_BUTTON_TYPE_RADIO, IDC_RADIO_COLOR_BLUE);
    }

    // Chatting
    {
        m_pEditChatWrite = make_shared<ChildEdit>();
        m_pEditChatWrite->Create(hWnd, C_RECT(900, 620, 1100, 650), L"", IDC_EDIT_CHAT_WRITE);
        
        m_pEditChatOut = make_shared<ChildEdit>();
        m_pEditChatOut->Create(hWnd, C_RECT(700, 50, 860, 250), L"", IDC_EDIT_CHAT_OUT, ES_READONLY);

        m_pButtonChatting = make_shared<ChildButton>();
        m_pButtonChatting->Create(hWnd, C_RECT(950, 660, 1050, 680), L"Chatting", CHILD_BUTTON_TYPE_BUTTON, IDC_BUTTON_CHATTING);
    }

    // Buttons
    {
        m_pButtonMove = make_shared<ChildButton>();
        m_pButtonMove->Create(hWnd, C_RECT(900, 700, 990, 730), L"Move", CHILD_BUTTON_TYPE_BUTTON, IDC_BUTTON_MOVE);
        
        m_pButtonPlus = make_shared<ChildButton>();
        m_pButtonPlus->Create(hWnd, C_RECT(1010, 700, 1100, 730), L"+", CHILD_BUTTON_TYPE_BUTTON, IDC_BUTTON_PLUS);
        
        m_pButtonMinus = make_shared<ChildButton>();
        m_pButtonMinus->Create(hWnd, C_RECT(900, 750, 990, 780), L"-", CHILD_BUTTON_TYPE_BUTTON, IDC_BUTTON_MINUS);
        
        m_pButtonStop = make_shared<ChildButton>();
        m_pButtonStop->Create(hWnd, C_RECT(1010, 750, 1100, 780), L"Stop", CHILD_BUTTON_TYPE_BUTTON, IDC_BUTTON_STOP);

    }

}

void Demo7_1::HandleMenu(WORD param)
{
}

void Demo7_1::ProcessKeyboard()
{
}

void Demo7_1::ProcessMouse()
{
}

void Demo7_1::OnDrawWindowPaint()
{
    PAINTSTRUCT ps = {};
    HDC hDC = BeginPaint(m_pDrawWindow->GetHwnd(), &ps);

    int childWidth = m_pDrawWindow->GetDesc().wndSize.width;
    int childHeight = m_pDrawWindow->GetDesc().wndSize.height;

    if (m_shape == DEMO71_SHAPE_TYPE_ELLIPSE)
    {
        m_pEllipse->SetOffset(POINT{ 400, 400 });
        m_pEllipse->DrawInWindowCoord(hDC);
    }
    else if (m_shape == DEMO71_SHAPE_TYPE_RECTANGLE)
    {
        m_pRect->SetOffset(POINT{ 400, 400 });
        m_pRect->DrawInWindowCoord(hDC);
    }
    else if (m_shape == DEMO71_SHAPE_TYPE_TRIANGLE)
    {
        m_pTriangle->SetOffset(POINT{ 400, 400 });
        m_pTriangle->DrawInWindowCoord(hDC);
    }

    shapes::Line::DrawLine(hDC, POINT{ childWidth / 2, 0 }, POINT{ childHeight / 2, childHeight });
    shapes::Line::DrawLine(hDC, POINT{ 0, childHeight / 2 }, POINT{ childWidth, childHeight / 2 });

    DrawBall(hDC);

    ::EndPaint(m_pDrawWindow->GetHwnd(), &ps);
}

void Demo7_1::ProcessShapeButton(WPARAM wParam)
{
    WORD loWparam = LOWORD(wParam);

    switch (loWparam)
    {
    case IDC_RADIO_SHAPES_ELLIPSE:
        m_shape = DEMO71_SHAPE_TYPE_ELLIPSE;
        break;

    case IDC_RADIO_SHAPES_RECTANGLE:
        m_shape = DEMO71_SHAPE_TYPE_RECTANGLE;
        break;

    case IDC_RADIO_SHAPES_TRIANGLE:
        m_shape = DEMO71_SHAPE_TYPE_TRIANGLE;
        break;
    }


}

void Demo7_1::ProcessSizeButton(WPARAM wParam)
{
}

void Demo7_1::ProcessColorButton(WPARAM wParam)
{
    WORD loWparam = LOWORD(wParam);

    switch (loWparam)
    {
    case IDC_RADIO_COLOR_RED:
        m_color = RGB(255, 0, 0);
        break;

    case IDC_RADIO_COLOR_GREEN:
        m_color = RGB(0, 255, 0);
        break;

    case IDC_RADIO_COLOR_BLUE:
        m_color = RGB(0, 0, 255);
        break;
    }
}

void Demo7_1::ProcessChatting(WPARAM wParam)
{
}

void Demo7_1::UpdateBallPos()
{
    if (m_shape == DEMO71_SHAPE_TYPE_ELLIPSE)
    {
        int x = 250 * cos(m_ballAnimDegree);
        int y = 250 * sin(m_ballAnimDegree);
        m_ballPos = POINT{ x, y };
        m_ballAnimDegree += 0.1f;
    }
}

void Demo7_1::DrawBall(HDC hDC)
{
    RECT ballRect = C_RECT(-1, -1, 1, 1);
    int scale = 50;

    ballRect = C_RECT(ballRect.left * scale, ballRect.top * scale, ballRect.right * scale, ballRect.bottom * scale);
    ballRect = C_RECT(ballRect.left + m_ballPos.x, ballRect.top + m_ballPos.y, ballRect.right + m_ballPos.x, ballRect.bottom + m_ballPos.y);
    ballRect = C_RECT(ballRect.left + 400, ballRect.top + 400, ballRect.right + 400, ballRect.bottom + 400);

    shapes::Ellipse::DrawEllipse(hDC, ballRect, m_color);

}

LRESULT Demo7_1::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    std::shared_ptr<Demo7_1> pDemo = CUR_DEMO(Demo7_1);

    switch (message)
    {
    case WM_CREATE:
        pDemo->OnCreate(hWnd);
        break;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_RADIO_SHAPES_ELLIPSE:
        case IDC_RADIO_SHAPES_RECTANGLE:
        case IDC_RADIO_SHAPES_TRIANGLE:
            pDemo->ProcessShapeButton(wParam);
            break;

        case IDC_RADIO_SIZE_SMALL:
        case IDC_RADIO_SIZE_MEDIUM:
        case IDC_RADIO_SIZE_LARGE:
            pDemo->ProcessSizeButton(wParam);
            break;

        case IDC_RADIO_COLOR_RED:
        case IDC_RADIO_COLOR_GREEN:
        case IDC_RADIO_COLOR_BLUE:
            pDemo->ProcessColorButton(wParam);
            break;

        case IDC_BUTTON_CHATTING:
            pDemo->ProcessChatting(wParam);
            break;

        case IDC_BUTTON_MOVE:
            break;

        case IDC_BUTTON_PLUS:
            break;

        case IDC_BUTTON_MINUS:
            break;

        case IDC_BUTTON_STOP:
            break;

        case IDC_EDIT_CHAT_WRITE:
            break;

        case IDC_EDIT_CHAT_OUT:
            break;


        default:
            break;
        }

    case WM_PAINT:
        pDemo->OnPaint();
        break;

    case WM_SIZE:
        break;

    case WM_MOVE:
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    default:
        break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT Demo7_1::DrawChildProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    std::shared_ptr<Demo7_1> pDemo = CUR_DEMO(Demo7_1);

    switch (message)
    {
    case WM_CREATE:
        break;

    case WM_PAINT:
        pDemo->OnDrawWindowPaint();
        break;

    case WM_SIZE:
        break;

    case WM_MOVE:
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_COMMAND:
        break;

    default:
        break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

VOID Demo7_1::AnimTimer(HWND hWnd, UINT message, UINT_PTR nElapse, DWORD)
{
    std::shared_ptr<Demo7_1> pDemo = CUR_DEMO(Demo7_1);
    pDemo->UpdateBallPos();
    InvalidateRect(pDemo->m_pDrawWindow->GetHwnd(), NULL, TRUE);
}
