#include "../pch.h"
#include "Demo6_3.h"
#include "../TextBox.h"
#include "../Utils.h"
#include "../Caret.h"
#include "../GameBoard.h"
#include "../resource.h"

using namespace std;
using namespace shapes;

BOOL Demo6_3::Initialize()
{
    m_pProcFunction = WndProc;

    m_AppDesc.wndName = L"Demo6-3";
    m_AppDesc.wndStyle = WS_OVERLAPPEDWINDOW;
    m_AppDesc.backgroundColor = WHITE_BRUSH;
    m_AppDesc.wndIcon = IDI_APPLICATION;
    m_AppDesc.wndCursor = IDC_ARROW;
    m_AppDesc.wndPosition.x = 100;
    m_AppDesc.wndPosition.y = 10;
    m_AppDesc.wndSize.width = 1200;
    m_AppDesc.wndSize.height = 900;
	m_AppDesc.appRunMode = APP_RUN_MODE_GAME_LOOP;

    return 0;
}

void Demo6_3::OnCreate(HWND hWnd)
{
    BOOL bResult = TRUE;
    TIMER.Initialize(hWnd);

    m_diag.Create(IDD_DIALOG_6_3, DialogProc);

    m_pCircle = make_shared<shapes::Ellipse>();
    m_pCircle->Create(C_RECT(-1, -1, 1, 1));
    m_pCircle->SetScale(POINT{ 20, 20 });
    
    m_pRect = make_shared<shapes::Rectangle>();
    m_pRect->Create(C_RECT(-1, -1, 1, 1));
    m_pRect->SetScale(POINT{ 20, 20 });

    if (!bResult) __debugbreak();
}

void Demo6_3::HandleMenu(WORD param)
{
}

void Demo6_3::Update()
{
    ProcessKeyboard();
    ProcessMouse();

    UpdateShapePos();

}

void Demo6_3::Draw(HDC hDC)
{
    DrawRoute(hDC);
    DrawShape(hDC);
    DrawDialogRect(m_diag.m_hDlg);
    DrawCoord(hDC);
}

void Demo6_3::ProcessKeyboard()
{
}

void Demo6_3::ProcessMouse()
{
    if (INPUT.GetButtonDown(KEY_TYPE::LBUTTON))
    {
        if (!m_bDiagShown)
        {
            m_bDiagShown = TRUE;
            m_diag.ShowDialog();
        }
        else
        {
            if (m_curMode == DEMO63_MODE_DRAW_ROUTE)
            {
                POINT mousePos = INPUT.GetMousePos();
                if (m_RoutePoints.size() < MAX_POINT_COUNT)
                {
                    m_RoutePoints.push_back(mousePos);
                }
            }
        }
    }
}

void Demo6_3::DrawRoute(HDC hDC)
{
    if (m_RoutePoints.size() < 7)
    {
        shapes::Polygon::DrawPolyline(hDC, m_RoutePoints);
    }
    else
    {
        shapes::Polygon::DrawPolygon(hDC, m_RoutePoints);
    }


}

void Demo6_3::DrawShape(HDC hDC)
{
    if (m_curMode != DEMO63_MODE_DRAW_ROUTE)
    {
        if (m_curShape == DEMO63_SHAPE_ELLIPSE)
        {
            m_pCircle->SetBackgroundColor(m_shapeColor);
            m_pCircle->SetOffset(m_curPos);
            m_pCircle->DrawInWindowCoord(hDC);
            TextBox::DrawFormattedString(hDC, WndPosition{ (ULONG)m_curPos.x, (ULONG)m_curPos.y - 50 }, m_TextArr[m_curTextIndex].c_str());
        }
        else
        {
            m_pRect->SetBackgroundColor(m_shapeColor);
            m_pRect->SetOffset(m_curPos);
            m_pRect->DrawInWindowCoord(hDC);
            TextBox::DrawFormattedString(hDC, WndPosition{ (ULONG)m_curPos.x, (ULONG)m_curPos.y - 50 }, m_TextArr[m_curTextIndex].c_str());
        }
    }

}

void Demo6_3::UpdateShapePos()
{
    if (m_curMode == DEMO63_MODE_FOLLOW_ROUTE)
    {
        m_beginPoint = m_RoutePoints[m_curBeginPointIndex];
        int endIndex = (m_curBeginPointIndex + 1) % (m_RoutePoints.size());
        m_endPoint = m_RoutePoints[endIndex];

        float t = m_curLineMovingProgress / 100.f;
        m_curPos.x = static_cast<LONG>(m_beginPoint.x + t * (m_endPoint.x - m_beginPoint.x));
        m_curPos.y = static_cast<LONG>(m_beginPoint.y + t * (m_endPoint.y - m_beginPoint.y));

        if (++m_curLineMovingProgress > 100)
        {
            m_curBeginPointIndex = (m_curBeginPointIndex + 1) % (m_RoutePoints.size());
            m_curLineMovingProgress = 0;
        }
    }
    else if (m_curMode == DEMO63_MODE_FOLLOW_ROUTE_REVERSE)
    {
        m_beginPoint = m_RoutePoints[m_curBeginPointIndex];
        int endIndex = (m_curBeginPointIndex - 1 + m_RoutePoints.size()) % m_RoutePoints.size();
        m_endPoint = m_RoutePoints[endIndex];

        float t = m_curLineMovingProgress / 100.f;
        m_curPos.x = static_cast<LONG>(m_beginPoint.x + t * (m_endPoint.x - m_beginPoint.x));
        m_curPos.y = static_cast<LONG>(m_beginPoint.y + t * (m_endPoint.y - m_beginPoint.y));

        if (++m_curLineMovingProgress > 100)
        {
            m_curBeginPointIndex = (m_curBeginPointIndex - 1 + m_RoutePoints.size()) % m_RoutePoints.size();
            m_curLineMovingProgress = 0;
        }
    }


}

void Demo6_3::DrawDialogRect(HWND hDlg)
{
    if (m_bDiagRectShown)
    {
        HDC hDC = GetDC(hDlg);
        RECT diagRect = C_RECT(m_DiagRect.left + m_offset.x, m_DiagRect.top, m_DiagRect.right + m_offset.x, m_DiagRect.bottom);
        shapes::Rectangle::DrawRectangle(hDC, diagRect);

        if (m_bDiagRectDirection)
        {
            m_offset.x++;
        }
        else
        {
            m_offset.x--;
        }

        if (diagRect.right > m_diag.GetDialogSize().right)
        {
            m_bDiagRectDirection = FALSE;
        }
        else if (diagRect.left < 0)
        {
            m_bDiagRectDirection = TRUE;
        }



        ReleaseDC(hDlg, hDC);
    }
}

LRESULT Demo6_3::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    std::shared_ptr<Demo6_3> pDemo = CUR_DEMO(Demo6_3);

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

LONGLONG Demo6_3::DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    std::shared_ptr<Demo6_3> pDemo = CUR_DEMO(Demo6_3);

    switch (message)
    {
    case WM_INITDIALOG:
    {
        HWND hList = GetDlgItem(hDlg, IDC_LIST1);
        SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)pDemo->GetTexts().at(0).c_str());
        SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)pDemo->GetTexts().at(1).c_str());
        SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)pDemo->GetTexts().at(2).c_str());

        CheckRadioButton(hDlg, IDC_RADIO_ELLIPSE, IDC_RADIO_RECT, IDC_RADIO_ELLIPSE);
        CheckRadioButton(hDlg, IDC_RADIO_RED, IDC_RADIO_BLUE, IDC_RADIO_RED);
        break;
    }

    case WM_PAINT:
    {
        break;
    }

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_LIST1:
            if (HIWORD(wParam) == LBN_DBLCLK)
            {
                HWND hList = GetDlgItem(hDlg, IDC_LIST1);
                int selected = SendMessage(hList, LB_GETCURSEL, 0, 0);
                pDemo->SetSelected(selected);
            }
            break;

        case IDC_RADIO_RED:
            pDemo->SetShapeColor(RGB(255, 0, 0));
            break;
            
        case IDC_RADIO_GREEN:
            pDemo->SetShapeColor(RGB(0, 255, 0));
            break;
            
        case IDC_RADIO_BLUE:
            pDemo->SetShapeColor(RGB(0, 255, 0));
            break;

        case IDC_RADIO_ELLIPSE:
            pDemo->SetShape(DEMO63_SHAPE_ELLIPSE);
            break;

        case IDC_RADIO_RECT:
            pDemo->SetShape(DEMO63_SHAPE_RECTANGLE);
            break;

        case IDC_DRAW:
            pDemo->SetDemoMode(DEMO63_MODE_DRAW_ROUTE);
            break;

        case IDC_MOVE:
            pDemo->SetDemoMode(DEMO63_MODE_FOLLOW_ROUTE);
            break;

        case IDC_REVERSE:
            pDemo->SetDemoMode(DEMO63_MODE_FOLLOW_ROUTE_REVERSE);
            break;

        case IDC_STOP:
            pDemo->SetDemoMode(DEMO63_MODE_STOP);
            break;

        case IDC_REDRAW:
            pDemo->ResetAnimVariables();
            pDemo->ResetRoute();
            pDemo->SetDemoMode(DEMO63_MODE_DRAW_ROUTE);
            break;
            
        case IDC_DIAGMOVE:
        {
            pDemo->SetDiagRectShow(!pDemo->GetDiagRectShow());
            break;
        }

        case IDOK:
            break;

        case IDCANCEL:
            pDemo->SetDiagShowState(FALSE);
            EndDialog(hDlg, 0);
            break;

        default:
            break;
        }
        break;

    case WM_CLOSE:
        pDemo->SetDiagShowState(FALSE);
        EndDialog(hDlg, 0);
        break;


    }

    return 0;
}
