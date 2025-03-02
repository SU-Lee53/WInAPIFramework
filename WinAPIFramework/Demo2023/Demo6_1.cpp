#include "../pch.h"
#include "Demo6_1.h"
#include "../TextBox.h"
#include "../Utils.h"
#include "../Caret.h"
#include "../GameBoard.h"
#include "../resource.h"

using namespace std;
using namespace shapes;

BOOL Demo6_1::Initialize()
{
    m_pProcFunction = WndProc;

    m_AppDesc.wndName = L"Demo6-1";
    m_AppDesc.wndStyle = WS_OVERLAPPEDWINDOW;
    m_AppDesc.backgroundColor = WHITE_BRUSH;
    m_AppDesc.wndIcon = IDI_APPLICATION;
    m_AppDesc.wndCursor = IDC_ARROW;
    m_AppDesc.wndPosition.x = 100;
    m_AppDesc.wndPosition.y = 10;
    m_AppDesc.wndSize.width = 1200;
    m_AppDesc.wndSize.height = 900;
	m_AppDesc.appRunMode = APP_RUN_MODE_GAME_LOOP;

    // 메뉴 설정
    //m_AppDesc.menuName = IDR_MENU_5_2;

    return 0;
}

void Demo6_1::OnCreate(HWND hWnd)
{
    BOOL bResult = TRUE;
    TIMER.Initialize(hWnd);

    m_pDialogBox = make_shared<ModalessDialog>();
    m_pDialogBox->Create(IDD_DIALOG_6_1, Demo6_1::DialogProc);

    m_pDialogBox->ShowDialog();

    m_sin.Reset();
    m_zigzag.Reset();
    m_pi.Reset();
    m_spring.Reset();

    if (!bResult) __debugbreak();
}

void Demo6_1::HandleMenu(WORD param)
{
}

void Demo6_1::Update()
{
    ProcessKeyboard();
    ProcessMouse();

}

void Demo6_1::Draw(HDC hDC)
{
    shapes::Line::DrawLine(hDC, POINT{ 0, (LONG)m_AppDesc.wndSize.height / 2 }, POINT{ (LONG)m_AppDesc.wndSize.width, (LONG)m_AppDesc.wndSize.height / 2 });
    shapes::Line::DrawLine(hDC, POINT{ (LONG)m_AppDesc.wndSize.width / 2, 0 }, POINT{ (LONG)m_AppDesc.wndSize.width / 2, (LONG)m_AppDesc.wndSize.height });

    COLORREF color = RGB(0, 0, 0);

    if (m_colorMode & DEMO61_COLOR_MODE_CYAN)
    {
        color = RGB(0, 255, 255);
    }
    else if (m_colorMode & DEMO61_COLOR_MODE_MAGENTA)
    {
        color = RGB(255, 0, 255);
    }
    else if (m_colorMode & DEMO61_COLOR_MODE_YELLOW)
    {
        color = RGB(255, 255, 0);
    }

    if (m_bInverted)
    {
        color = Utils::InvertColor(color);
    }

    C_HPEN pen(PS_SOLID, 2, color);
    HPEN oldPen = (HPEN)SelectObject(hDC, pen);

    if (m_drawMode & DEMO61_DRAW_MODE_SIN)
    {
        DrawSin(hDC);
    }
    else if (m_drawMode & DEMO61_DRAW_MODE_ZIGZAG)
    {
        DrawZigzag(hDC);
    }
    else if (m_drawMode & DEMO61_DRAW_MODE_SPRING)
    {
        DrawSpring(hDC);
    }
    else if (m_drawMode & DEMO61_DRAW_MODE_PI)
    {
        DrawPi(hDC);
    }

    ::SelectObject(hDC, oldPen);
    pen.Destroy();

    DrawCoord(hDC);
}

void Demo6_1::DrawSin(HDC hDC)
{
    int wndWidth = m_AppDesc.wndSize.width;
    int wndHeight = m_AppDesc.wndSize.height;

    ::MoveToEx(hDC, 0, wndHeight / 2, NULL);

    for (int x = 0; x < wndWidth; x++)
    {
        int y = (int)(m_sin.radius * sin((x + m_sin.phase) * 0.05f) + wndHeight / 2);
        ::LineTo(hDC, x, y);
    }

    if (m_animMode & DEMO61_ANIM_MODE_MOVE_X)
    {
        m_sin.phase += 0.5f;
    }

    if (m_animMode & DEMO61_ANIM_MODE_MOVE_Y)
    {
        if (m_sin.bUp)
        {
            m_sin.radius += 0.5f;
        }
        else
        {
            m_sin.radius -= 0.5f;
        }

        if (m_sin.radius > 100.f) m_sin.bUp = FALSE;
        else if (m_sin.radius <= 10.f) m_sin.bUp = TRUE;

    }

    if (m_animMode & DEMO61_ANIM_MODE_RESET)
    {
        m_sin.Reset();
    }

}

void Demo6_1::DrawZigzag(HDC hDC)
{
    int wndWidth = m_AppDesc.wndSize.width;
    int wndHeight = m_AppDesc.wndSize.height;

    ::MoveToEx(hDC, m_zigzag.offsetX, wndHeight / 2, NULL);

    for (int x = m_zigzag.offsetX; x < wndWidth * 2; x += 100)
    {
        ::LineTo(hDC, x, -m_zigzag.height + wndHeight / 2);
        ::LineTo(hDC, x + (100 / 2), m_zigzag.height + wndHeight / 2);
    }

    if (m_animMode & DEMO61_ANIM_MODE_MOVE_X)
    {
        m_zigzag.offsetX -= 0.1;
        if (m_zigzag.offsetX > 100.f) m_zigzag.offsetX = 0.f;
    }

    if (m_animMode & DEMO61_ANIM_MODE_MOVE_Y)
    {
        if (m_zigzag.bUp)
        {
            m_zigzag.height += 0.1;
        }
        else
        {
            m_zigzag.height -= 0.1;
        }

        if (m_zigzag.height > 100.f) m_zigzag.bUp = FALSE;
        else if (m_zigzag.height <= 10.f) m_zigzag.bUp = TRUE;

    }

    if (m_animMode & DEMO61_ANIM_MODE_RESET)
    {
        m_zigzag.Reset();
    }
}

void Demo6_1::DrawSpring(HDC hDC)
{
    int wndWidth = m_AppDesc.wndSize.width;
    int wndHeight = m_AppDesc.wndSize.height;

    ::MoveToEx(hDC, m_spring.center.x, m_spring.center.y, NULL);

    float oneDegToRad = 3.141592f / 180.f;

    float centerX = m_spring.center.x;
    float centerY = m_spring.center.y;

    int count = 0;
    while(centerX < wndWidth * 2)
    {
        centerX = m_spring.center.x + (count * -0.25f);
        centerY = m_spring.center.y;
        int x = centerX + (m_spring.radius * (sin(count * oneDegToRad)));
        int y = centerY + (m_spring.radius * (cos(count * oneDegToRad)));
        ::LineTo(hDC, x, y);
        count--;
    }

    if (m_animMode & DEMO61_ANIM_MODE_MOVE_X)
    {
        m_spring.center.x -= 1;
        //if (m_spring.center.x < -100) m_spring.center.x = 0;
    }

    if (m_animMode & DEMO61_ANIM_MODE_MOVE_Y)
    {
        if (m_spring.bUp)
        {
            m_spring.radius += 0.5;
        }
        else
        {
            m_spring.radius -= 0.5;
        }

        if (m_spring.radius > 150.f) m_spring.bUp = FALSE;
        else if (m_spring.radius <= 50.f) m_spring.bUp = TRUE;

    }

    if (m_animMode & DEMO61_ANIM_MODE_RESET)
    {
        m_spring.Reset();
    }
}

void Demo6_1::DrawPi(HDC hDC)
{
    int wndWidth = m_AppDesc.wndSize.width;
    int wndHeight = m_AppDesc.wndSize.height;

    ::MoveToEx(hDC, m_pi.offsetX, wndHeight / 2, NULL);

    for (int x = m_pi.offsetX; x < wndWidth * 2; x += 70)
    {
        int height = m_pi.bDirection ? m_pi.height : -m_pi.height;
        int y = height + wndHeight / 2;
        ::LineTo(hDC, x, y);
        ::LineTo(hDC, x + 70, y);
        m_pi.bDirection = !m_pi.bDirection;
    }


    if (m_animMode & DEMO61_ANIM_MODE_MOVE_X)
    {
        m_pi.offsetX -= 0.1;
        if (m_pi.offsetX > 100.f) m_pi.offsetX = 0.f;
    }

    if (m_animMode & DEMO61_ANIM_MODE_MOVE_Y)
    {
        if (m_pi.bUp)
        {
            m_pi.height += 0.1;
        }
        else
        {
            m_pi.height -= 0.1;
        }

        if (m_pi.height > 100.f) m_pi.bUp = FALSE;
        else if (m_pi.height <= 10.f) m_pi.bUp = TRUE;

    }
    
    if (m_animMode & DEMO61_ANIM_MODE_RESET)
    {
        m_pi.Reset();
    }

}

void Demo6_1::ProcessKeyboard()
{
}

void Demo6_1::ProcessMouse()
{
}

LRESULT Demo6_1::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    std::shared_ptr<Demo6_1> pDemo = CUR_DEMO(Demo6_1);

    switch (message)
    {
    case WM_CREATE:
        pDemo->OnCreate(hWnd);
        break;

    case WM_PAINT:
        break;

    case WM_SIZE:
        break;

    case WM_MOVE:
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_COMMAND:
        pDemo->HandleMenu(LOWORD(wParam));
        break;

    default:
        break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

LONGLONG Demo6_1::DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    std::shared_ptr<Demo6_1> pDemo = CUR_DEMO(Demo6_1);

    HWND hRadio[4];
    HWND hCheck[4];

    switch (message)
    {
    case WM_INITDIALOG:
        CheckRadioButton(hDlg, IDC_RADIO1, IDC_RADIO4, IDC_RADIO1);
        break;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_RADIO1:
            pDemo->SetDrawMode(DEMO61_DRAW_MODE_SIN);
            break;

        case IDC_RADIO2:
            pDemo->SetDrawMode(DEMO61_DRAW_MODE_ZIGZAG);
            break;

        case IDC_RADIO3:
            pDemo->SetDrawMode(DEMO61_DRAW_MODE_SPRING);
            break;

        case IDC_RADIO4:
            pDemo->SetDrawMode(DEMO61_DRAW_MODE_PI);
            break;

        case IDC_BUTTON1:
            pDemo->SetAnimationMode(DEMO61_ANIM_MODE_MOVE_X);
            break;

        case IDC_BUTTON2:
            pDemo->SetAnimationMode(DEMO61_ANIM_MODE_MOVE_Y);
            break;

        case IDC_BUTTON3:
            pDemo->SetAnimationMode(DEMO61_ANIM_MODE_STOP);
            break;

        case IDC_BUTTON4:
            pDemo->SetAnimationMode(DEMO61_ANIM_MODE_RESET);
            break;

        case IDC_BUTTON5:
            pDemo->SetAnimationMode(DEMO61_ANIM_MODE_FOLLOW_TRAIL);
            break;

        case IDC_CHECK1:
            if (IsDlgButtonChecked(hDlg, IDC_CHECK1))
            {
                pDemo->SetColorMode(DEMO61_COLOR_MODE_CYAN);
            }
            else
            {
                pDemo->SetColorMode(DEMO61_COLOR_MODE_BLACK);
            }
            break;

        case IDC_CHECK2:
            if (IsDlgButtonChecked(hDlg, IDC_CHECK2))
            {
                pDemo->SetColorMode(DEMO61_COLOR_MODE_MAGENTA);
            }
            else
            {
                pDemo->SetColorMode(DEMO61_COLOR_MODE_BLACK);
            }
            break;

        case IDC_CHECK3:
            if (IsDlgButtonChecked(hDlg, IDC_CHECK3))
            {
                pDemo->SetColorMode(DEMO61_COLOR_MODE_YELLOW);
            }
            else
            {
                pDemo->SetColorMode(DEMO61_COLOR_MODE_BLACK);
            }
            break;

        case IDC_CHECK4:
            pDemo->SetColorInvert(IsDlgButtonChecked(hDlg, IDC_CHECK4));
            break;

        case IDOK:
            // 버튼 초기화
            // Radio Button
            CheckRadioButton(hDlg, IDC_RADIO1, IDC_RADIO4, IDC_RADIO1);

            // Check Button
            SendMessage(GetDlgItem(hDlg, IDC_CHECK1), BM_SETCHECK, BST_UNCHECKED, 0);
            SendMessage(GetDlgItem(hDlg, IDC_CHECK2), BM_SETCHECK, BST_UNCHECKED, 0);
            SendMessage(GetDlgItem(hDlg, IDC_CHECK3), BM_SETCHECK, BST_UNCHECKED, 0);
            SendMessage(GetDlgItem(hDlg, IDC_CHECK4), BM_SETCHECK, BST_UNCHECKED, 0);

            // Demo State 초기화
            pDemo->SetDrawMode(DEMO61_DRAW_MODE_SIN);
            pDemo->SetColorMode(DEMO61_COLOR_MODE_BLACK);
            pDemo->SetAnimationMode(DEMO61_ANIM_MODE_MOVE_X);
            pDemo->SetColorInvert(FALSE);
            break;

        case IDCANCEL:
            EndDialog(hDlg, 0);
            break;

        default:
            break;
        }
        break;

    case WM_CLOSE:
        EndDialog(hDlg, 0);
        break;


    }

    return 0;
}
