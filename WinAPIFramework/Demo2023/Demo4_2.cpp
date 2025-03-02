#include "../pch.h"
#include "Demo4_2.h"
#include "../TextBox.h"
#include "../Utils.h"
#include "../Caret.h"
#include "../GameBoard.h"

using namespace std;
using namespace shapes;

BOOL Demo4_2::Initialize()
{
    m_pProcFunction = WndProc;

    m_AppDesc.wndName = L"Demo4-1";
    m_AppDesc.wndStyle = WS_OVERLAPPEDWINDOW;
    m_AppDesc.backgroundColor = WHITE_BRUSH;
    m_AppDesc.wndIcon = IDI_APPLICATION;
    m_AppDesc.wndCursor = IDC_ARROW;
    m_AppDesc.wndPosition.x = 100;
    m_AppDesc.wndPosition.y = 10;
    m_AppDesc.wndSize.width = 800;
    m_AppDesc.wndSize.height = 800;
	m_AppDesc.appRunMode = APP_RUN_MODE_GAME_LOOP;

    // 메뉴 설정
    m_AppDesc.menuName = IDR_MENU_4_2;

    return 0;
}

void Demo4_2::OnCreate(HWND hWnd)
{
    BOOL bResult = TRUE;
    TIMER.Initialize(hWnd);

    m_pBoard = make_shared<GameBoard>();
    m_pBoard->Create(40, 40, 0, 0, 20, 20);

    if (!bResult) __debugbreak();
}

void Demo4_2::HandleMenu(WORD param)
{
    switch (param)
    {
    case ID_GRIDSTYLE_SOLID:
        m_pBoard->SetFrameStyle(PS_SOLID);
        break;

    case ID_GRIDSTYLE_DOT:
        m_pBoard->SetFrameStyle(PS_DOT);
        break;

    case ID_COLOR_1:
        if (m_pRects.size() > m_Seleted)
            m_pRects[m_Seleted]->SetBackgroundColor(RGB(255, 0, 0));
        break;

    case ID_COLOR_2:
        if (m_pRects.size() > m_Seleted)
            m_pRects[m_Seleted]->SetBackgroundColor(RGB(0, 255, 0));
        break;

    case ID_COLOR_3:
        if (m_pRects.size() > m_Seleted)
            m_pRects[m_Seleted]->SetBackgroundColor(RGB(0, 0, 255));
        break;

    case ID_COLOR_4:
        if (m_pRects.size() > m_Seleted)
            m_pRects[m_Seleted]->SetBackgroundColor(RGB(0, 255, 255));
        break;

    case ID_COLOR_5:
        if (m_pRects.size() > m_Seleted)
            m_pRects[m_Seleted]->SetBackgroundColor(RGB(255, 255, 0));
        break;

    case ID_COLOR_6:
        if (m_pRects.size() > m_Seleted)
            m_pRects[m_Seleted]->SetBackgroundColor(RGB(255, 0, 255));
        break;

    case ID_BORDER_ON:
        for (auto& p : m_pRects)
        {
            p->SetFrameStyle(PS_SOLID);
        }
        break;

    case ID_BORDER_OFF:
        for (auto& p : m_pRects)
        {
            p->SetFrameStyle(PS_NULL);
        }
        break;

    default:
        break;
    }

}

void Demo4_2::Update()
{
    ProcessKeyboard();
    ProcessMouse();


}

void Demo4_2::Draw(HDC hDC)
{
    m_pBoard->Draw(hDC);

    DrawRects(hDC);

    if (m_bLDrag)
    {
        shapes::Rectangle::DrawRectangle(hDC, m_tempDrawRect, m_CurrentColor);
    }

    // Debug
    DrawCoord(hDC);
}

void Demo4_2::ProcessKeyboard()
{
    if (INPUT.GetButtonDown(KEY_TYPE::KEY_1))
    {
        m_Seleted = 0;
    }
    else if (INPUT.GetButtonDown(KEY_TYPE::KEY_2))
    {
        m_Seleted = 1;
    }
    else if (INPUT.GetButtonDown(KEY_TYPE::KEY_3))
    {
        m_Seleted = 2;
    }
    else if (INPUT.GetButtonDown(KEY_TYPE::KEY_4))
    {
        m_Seleted = 3;
    }
    else if (INPUT.GetButtonDown(KEY_TYPE::KEY_5))
    {
        m_Seleted = 4;
    }

    if (INPUT.GetButtonDown(KEY_TYPE::UP))
    {
        if (m_pRects.size() > m_Seleted)
        {
            RECT origin = m_pRects[m_Seleted]->GetRect();
            RECT r = origin;
            r.top -= m_pBoard->GetCellSize().height;
            r.bottom -= m_pBoard->GetCellSize().height;
            if (r.top < 0)
            {
                r = origin;
            }

            m_pRects[m_Seleted]->SetRectAndReset(r);
        }
    }
    else if (INPUT.GetButtonDown(KEY_TYPE::DOWN))
    {
        if (m_pRects.size() > m_Seleted)
        {
            RECT origin = m_pRects[m_Seleted]->GetRect();
            RECT r = origin;
            r.top += m_pBoard->GetCellSize().height;
            r.bottom += m_pBoard->GetCellSize().height;
            if (r.bottom > m_AppDesc.wndSize.height)
            {
                r = origin;
            }

            m_pRects[m_Seleted]->SetRectAndReset(r);
        }
    }
    else if (INPUT.GetButtonDown(KEY_TYPE::LEFT))
    {
        if (m_pRects.size() > m_Seleted)
        {
            RECT origin = m_pRects[m_Seleted]->GetRect();
            RECT r = origin;
            r.left -= m_pBoard->GetCellSize().height;
            r.right -= m_pBoard->GetCellSize().height;
            if (r.left < 0)
            {
                r = origin;
            }

            m_pRects[m_Seleted]->SetRectAndReset(r);
        }
    }
    else if (INPUT.GetButtonDown(KEY_TYPE::RIGHT))
    {
        if (m_pRects.size() > m_Seleted)
        {
            RECT origin = m_pRects[m_Seleted]->GetRect();
            RECT r = origin;
            r.left += m_pBoard->GetCellSize().height;
            r.right += m_pBoard->GetCellSize().height;
            if (r.right > m_AppDesc.wndSize.width)
            {
                r = origin;
            }

            m_pRects[m_Seleted]->SetRectAndReset(r);
        }
    }

}

void Demo4_2::ProcessMouse()
{
    if (INPUT.GetButtonDown(KEY_TYPE::LBUTTON))
    {
        m_LMouseDragBeginPoint = INPUT.GetMousePos();
        m_CurrentColor = RANDOM.GenerateRandomColor();
        m_bLDrag = TRUE;
    }
    else if (INPUT.GetButton(KEY_TYPE::LBUTTON))
    {
        if (m_bLDrag)
        {
            POINT curPos = INPUT.GetMousePos();

            auto [minX, maxX] = std::minmax(m_LMouseDragBeginPoint.x, curPos.x);
            auto [minY, maxY] = std::minmax(m_LMouseDragBeginPoint.y, curPos.y);

            m_tempDrawRect = C_RECT(minX, minY, maxX, maxY);
        }
    }
    if (INPUT.GetButtonUp(KEY_TYPE::LBUTTON))
    {
        m_LMouseDragEndPoint = INPUT.GetMousePos();
        m_tempDrawRect = C_RECT(0, 0, 0, 0);

        if (m_pRects.size() < MAX_RECT_COUNT)
        {
            // 시작점과 끝점으로 사각형 그림
            POINT beginBoardPos = m_pBoard->PointToBoardCoord(m_LMouseDragBeginPoint);
            POINT endBoardPos = m_pBoard->PointToBoardCoord(m_LMouseDragEndPoint);

            int beginRow = min(beginBoardPos.y, endBoardPos.y);
            int endRow = max(beginBoardPos.y, endBoardPos.y);
            int beginCol = min(beginBoardPos.x, endBoardPos.x);
            int endCol = max(beginBoardPos.x, endBoardPos.x);

            // 칠했으면 외곽선을 위한 shape 를 만들고 m_pRects 에 추가
            RECT begin = m_pBoard->GetCellRect(beginRow, beginCol);
            RECT end = m_pBoard->GetCellRect(endRow, endCol);

            std::shared_ptr<shapes::Rectangle> p = make_shared<shapes::Rectangle>();
            p->Create(C_RECT(begin.left, begin.top, end.right, end.bottom));
            p->SetBackgroundColor(m_CurrentColor);
            p->SetFrameWidth(m_FrameWidth);

            m_pRects.push_back(std::move(p));

            m_bLDrag = FALSE;
        }
    }
    
    if (INPUT.GetButtonDown(KEY_TYPE::RBUTTON))
    {
        POINT mousePos = INPUT.GetMousePos();

        for (const auto& p : m_pRects)
        {
            if (p->IsInRect(mousePos))
            {
                m_wpRClicked = p;
                m_bRDrag = TRUE;
                m_RMouseDragBeginPoint = mousePos;
                break;
            }
        }
    }
    else if (INPUT.GetButton(KEY_TYPE::RBUTTON))
    {
        if (m_bRDrag)
        {
            POINT curPos = INPUT.GetMousePos();
            int dx = curPos.x - m_RMouseDragBeginPoint.x;
            int dy = curPos.y - m_RMouseDragBeginPoint.y;

            RECT rect = m_wpRClicked.lock()->GetRect();
            OffsetRect(&rect, dx, dy);
            m_wpRClicked.lock()->SetRectAndReset(rect);

            m_RMouseDragBeginPoint = curPos;
        }
    }
    if (INPUT.GetButtonUp(KEY_TYPE::RBUTTON))
    {
        if (m_bRDrag == TRUE)
        {
            RECT movedRect = m_wpRClicked.lock()->GetRect();
            WndSize size = m_wpRClicked.lock()->GetSize();

            POINT leftTop = m_pBoard->PointToBoardCoord(POINT(movedRect.left, movedRect.top));

            RECT begin = m_pBoard->GetCellRect(leftTop.y, leftTop.x);

            movedRect = C_RECT(begin.left, begin.top, begin.left + size.width, begin.top + size.height);
            m_wpRClicked.lock()->SetRectAndReset(movedRect);

            m_wpRClicked.reset();
        }

        m_bRDrag = FALSE;
    }

}

void Demo4_2::DrawRects(HDC hDC)
{
    // 우선 다 그림
    for (int i = 0; i < m_pRects.size(); i++)
    {
        if (i == m_Seleted) // 선택된건 테두리가 빨간색
        {
            m_pRects[i]->SetFrameColor(RGB(255, 0, 0));
            m_pRects[i]->DrawInWindowCoord(hDC);
            m_pRects[i]->SetFrameColor(RGB(0, 0, 0));
        }
        else
        {
            m_pRects[i]->DrawInWindowCoord(hDC);
        }
    }

    // 충돌 여부를 까서 겹친부분만 색을 합쳐 다시그림
    if (!m_pRects.empty())
    {
        for (int i = 0; i < m_pRects.size() - 1; i++)
        {
            RECT r1 = m_pRects[i]->GetRect();
            for (int j = i + 1; j < m_pRects.size(); j++)
            {
                RECT r2 = m_pRects[j]->GetRect();
                RECT intersected;
                if (::IntersectRect(&intersected, &r1, &r2))
                {
                    COLORREF c1 = m_pRects[i]->GetBackgroundColor();
                    COLORREF c2 = m_pRects[j]->GetBackgroundColor();
                    COLORREF colorSum = Utils::AddColorRef(c1, c2);
                    shapes::Rectangle::DrawRectangle(hDC, intersected, colorSum, PS_SOLID, m_FrameWidth, RGB(0, 0, 0));
                }
            }
        }
    }


}

LRESULT Demo4_2::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    std::shared_ptr<Demo4_2> pDemo = CUR_DEMO(Demo4_2);

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
