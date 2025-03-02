#include "../pch.h"
#include "Demo3_4.h"
#include "../TextBox.h"
#include "../Utils.h"
#include "../Caret.h"
#include "../GameBoard.h"

using namespace std;
using namespace shapes;

BOOL Demo3_4::Initialize()
{
    m_pProcFunction = WndProc;

    m_AppDesc.wndName = L"Demo3-4";
    m_AppDesc.wndStyle = WS_OVERLAPPEDWINDOW;
    m_AppDesc.backgroundColor = WHITE_BRUSH;
    m_AppDesc.wndIcon = IDI_APPLICATION;
    m_AppDesc.wndCursor = IDC_ARROW;
    m_AppDesc.wndPosition.x = 100;
    m_AppDesc.wndPosition.y = 10;
    m_AppDesc.wndSize.width = 360;
    m_AppDesc.wndSize.height = 720;
	m_AppDesc.appRunMode = APP_RUN_MODE_GAME_LOOP;

    return 0;
}

void Demo3_4::OnCreate(HWND hWnd)
{
    BOOL bResult = TRUE;
    TIMER.Initialize(hWnd);

    UINT cellWidth = m_AppDesc.wndSize.width / 6;
    UINT cellHeight = m_AppDesc.wndSize.height / 12;
    m_pBoard = make_shared<GameBoard>();
    m_pBoard->Create(12, 6, 0, 0, cellWidth, cellHeight);


    if (!bResult) __debugbreak();
}

void Demo3_4::Update()
{
    ProcessKeyboard();

    ULONGLONG curTick = GetTickCount64();
    if (curTick - m_ullPrevUpdateTick > m_ullUpdateTick)
    {
        // Update
        if (m_CurGameState == GAME_STATE_READY_TO_DOWN)
        {
            CreateRect();
        }
        else if (m_CurGameState == GAME_STATE_DOWN)
        {
            DownRect();
        }
        else if (m_CurGameState == GAME_STATE_DOWN_DONE)
        {
            CheckBoard();
        }


        m_ullPrevUpdateTick = curTick;
    }

}

void Demo3_4::Draw(HDC hDC)
{
    m_pBoard->Draw(hDC);

    // Debug
    DrawCoord(hDC);
}

void Demo3_4::ProcessKeyboard()
{
    if (INPUT.GetButtonDown(KEY_TYPE::DOWN))
    {
        m_ullUpdateTick = 100;
    }
    if (INPUT.GetButtonUp(KEY_TYPE::DOWN))
    {
        m_ullUpdateTick = 1000;
    }
    
    if (INPUT.GetButtonDown(KEY_TYPE::LEFT))
    {
        MoveLeft();
    }
    if (INPUT.GetButtonDown(KEY_TYPE::RIGHT))
    {
        MoveRight();
    }
    

    if (INPUT.GetButtonDown(KEY_TYPE::ENTER))
    {
        // 일단 지움
        ClearCurrentPos();

        // 바꿀수 없는 경우들이 있으므로 잘 확인해야함...
        if (m_CurRect == RECT_OBJ_TWO_H)
        {
            // 일단 변경
            m_CurRect = RECT_OBJ_TWO_V;

            // 더 내려갈수 없다면 원상복구
            BOOL bCanGoDown = CheckCanGoDown();
            // 바꾸면 벽에 걸린다면 원상복구 -> 세로 - 가로 변경은 걸릴일 없을듯?

            if (!bCanGoDown) m_CurRect = RECT_OBJ_TWO_H;
        }
        else if (m_CurRect == RECT_OBJ_TWO_V)
        {
            m_CurRect = RECT_OBJ_TWO_H;

            BOOL bCanGoDown = CheckCanGoDown();
            if (m_CurPos.y + 1 >= 6)
                bCanGoDown = FALSE;

            if (!bCanGoDown) m_CurRect = RECT_OBJ_TWO_H;
        }
        else if (m_CurRect == RECT_OBJ_THREE_H) 
        {
            m_CurRect = RECT_OBJ_THREE_V;

            BOOL bCanGoDown = CheckCanGoDown();
            if (!bCanGoDown) m_CurRect = RECT_OBJ_THREE_H;
        }
        else if (m_CurRect == RECT_OBJ_THREE_V)
        {
            m_CurRect = RECT_OBJ_THREE_H;

            BOOL bCanGoDown = CheckCanGoDown();
            if (m_CurPos.y + 2 >= 6) 
                bCanGoDown = FALSE;

            if (!bCanGoDown) m_CurRect = RECT_OBJ_THREE_V;
        }

        // 다시 채움
        FillCurrentPos();
    }
}

void Demo3_4::ProcessMouse()
{
}

void Demo3_4::CreateRect()
{
    // 값 초기화
    m_CurRect = (RECT_OBJ_TYPE)RANDOM.GenerateRandom(0, 4);
    m_CurColor = m_Colors[RANDOM.GenerateRandom(0, 4)];
    m_CurPos = POINT{ 0, 2 };   // 0행 2열에서 출발

    // 일단 시작위치서 그리도록 함
    if (m_CurRect == RECT_OBJ_ONE)
    {
        m_pBoard->SetCellColor(m_CurPos.x, m_CurPos.y, m_CurColor);
    }
    else if (m_CurRect == RECT_OBJ_TWO_V)
    {
        m_pBoard->SetCellColor(m_CurPos.x, m_CurPos.y, m_CurColor);
        m_pBoard->SetCellColor(m_CurPos.x + 1, m_CurPos.y, m_CurColor);
    }
    else if (m_CurRect == RECT_OBJ_TWO_H)
    {
        m_pBoard->SetCellColor(m_CurPos.x, m_CurPos.y, m_CurColor);
        m_pBoard->SetCellColor(m_CurPos.x, m_CurPos.y + 1, m_CurColor);
    }
    else if (m_CurRect == RECT_OBJ_THREE_V)
    {
        m_pBoard->SetCellColor(m_CurPos.x, m_CurPos.y, m_CurColor);
        m_pBoard->SetCellColor(m_CurPos.x + 1, m_CurPos.y, m_CurColor);
        m_pBoard->SetCellColor(m_CurPos.x + 2, m_CurPos.y, m_CurColor);
    }
    else if (m_CurRect == RECT_OBJ_THREE_H)
    {
        m_pBoard->SetCellColor(m_CurPos.x, m_CurPos.y, m_CurColor);
        m_pBoard->SetCellColor(m_CurPos.x, m_CurPos.y + 1, m_CurColor);
        m_pBoard->SetCellColor(m_CurPos.x, m_CurPos.y + 2, m_CurColor);
    }


    m_CurGameState = GAME_STATE_DOWN;
}

void Demo3_4::DownRect()
{
    // 1. 일단 현위치를 다시 흰색으로 밀어버림
    ClearCurrentPos();


    // 2. 한칸 내림
    POINT origin = m_CurPos;
    m_CurPos.x++;

    // 3. 다음 프레임에 더 내려갈수 있는지 체크
    // 못내려간다면 좌표를 원상복구함
    // 못내려가는 조건 : 1. 아래에 이미 뭔가 있음 | 2. 맨 밑바닥임

    BOOL bCanDownNextFrame = CheckCanGoDown();

    if (!bCanDownNextFrame)
    {
        m_CurPos = origin;
    }

    // 4. 내려갈 수 있다면 다음 위치를 칠함, 아니면 복구된 위치를 다시 칠함
    FillCurrentPos();

    // 내려갈 수 없다면 상태전환 후 리턴

    if (!bCanDownNextFrame)
    {
        m_CurGameState = GAME_STATE_DOWN_DONE;
    }

}

void Demo3_4::CheckBoard()
{
    // 보드 점검 및 연속된거 제거
    bool removed = false;
    {
        UINT rows = m_pBoard->GetRows();
        UINT cols = m_pBoard->GetCols();

        // 가로로 연속된 색 확인 및 제거
        for (UINT i = 0; i < rows; i++)
        {
            UINT j = 0;
            while (j < cols)
            {
                COLORREF color = m_pBoard->GetCellColor(i, j);
                if (color == RGB(255, 255, 255))
                {
                    j++;
                    continue;
                }

                UINT start = j;
                while (j < cols && m_pBoard->GetCellColor(i, j) == color)
                {
                    j++;
                }

                if (j - start >= 3)
                {
                    removed = true;
                    for (UINT k = start; k < j; k++)
                    {
                        m_pBoard->SetCellColor(i, k, RGB(255, 255, 255));
                    }
                }
            }
        }

        // 세로로 연속된 색 확인 및 제거
        for (UINT j = 0; j < cols; j++)
        {
            UINT i = 0;
            while (i < rows)
            {
                COLORREF color = m_pBoard->GetCellColor(i, j);
                if (color == RGB(255, 255, 255))
                {
                    i++;
                    continue;
                }

                UINT start = i;
                while (i < rows && m_pBoard->GetCellColor(i, j) == color)
                {
                    i++;
                }

                if (i - start >= 3)
                {
                    removed = true;
                    for (UINT k = start; k < i; k++)
                    {
                        m_pBoard->SetCellColor(k, j, RGB(255, 255, 255));
                    }
                }
            }
        }
    }

    // 제거 뒤 흰칸 위에 색깔칸이 있다면 밑으로 옮김
    if (removed)
    {
        UINT rows = m_pBoard->GetRows();
        UINT cols = m_pBoard->GetCols();

        for (UINT j = 0; j < cols; j++)
        {
            for (int i = rows - 1; i >= 0; i--)
            {
                if (m_pBoard->GetCellColor(i, j) == RGB(255, 255, 255))
                {
                    int k = i - 1;
                    while (k >= 0 && m_pBoard->GetCellColor(k, j) == RGB(255, 255, 255))
                    {
                        k--;
                    }

                    if (k >= 0)
                    {
                        m_pBoard->SetCellColor(i, j, m_pBoard->GetCellColor(k, j));
                        m_pBoard->SetCellColor(k, j, RGB(255, 255, 255));
                    }
                }
            }
        }
    }

    m_CurGameState = GAME_STATE_READY_TO_DOWN;
}

BOOL Demo3_4::CheckCanGoDown()
{
    BOOL bCanDownNextFrame = TRUE;

    if (m_CurRect == RECT_OBJ_ONE)
    {
        if (m_CurPos.x == 12) bCanDownNextFrame = FALSE;  // 2번 조건
        if (!bCanDownNextFrame) goto lb_return;

        // 1번 조건
        if (m_pBoard->GetCellColor(m_CurPos.x, m_CurPos.y) != RGB(255, 255, 255))
            bCanDownNextFrame = FALSE;
        if (!bCanDownNextFrame) goto lb_return;
    }
    else if (m_CurRect == RECT_OBJ_TWO_V)
    {
        if (m_CurPos.x == 11) bCanDownNextFrame = FALSE;  // 2번 조건
        if (!bCanDownNextFrame) goto lb_return;

        // 1번 조건
        if (m_pBoard->GetCellColor(m_CurPos.x, m_CurPos.y) != RGB(255, 255, 255)) bCanDownNextFrame = FALSE;
        if (!bCanDownNextFrame) goto lb_return;
        if (m_pBoard->GetCellColor(m_CurPos.x + 1, m_CurPos.y) != RGB(255, 255, 255)) bCanDownNextFrame = FALSE;
        if (!bCanDownNextFrame) goto lb_return;
    }
    else if (m_CurRect == RECT_OBJ_TWO_H)
    {
        if (m_CurPos.x == 12) bCanDownNextFrame = FALSE;  // 2번 조건
        if (!bCanDownNextFrame) goto lb_return;

        // 1번 조건
        if (m_pBoard->GetCellColor(m_CurPos.x, m_CurPos.y) != RGB(255, 255, 255)) bCanDownNextFrame = FALSE;
        if (!bCanDownNextFrame) goto lb_return;
        if (m_pBoard->GetCellColor(m_CurPos.x, m_CurPos.y + 1) != RGB(255, 255, 255)) bCanDownNextFrame = FALSE;
        if (!bCanDownNextFrame) goto lb_return;
    }
    else if (m_CurRect == RECT_OBJ_THREE_V)
    {
        if (m_CurPos.x == 10) bCanDownNextFrame = FALSE;  // 2번 조건
        if (!bCanDownNextFrame) goto lb_return;

        // 1번 조건
        if (m_pBoard->GetCellColor(m_CurPos.x, m_CurPos.y) != RGB(255, 255, 255)) bCanDownNextFrame = FALSE;
        if (!bCanDownNextFrame) goto lb_return;
        if (m_pBoard->GetCellColor(m_CurPos.x + 1, m_CurPos.y) != RGB(255, 255, 255)) bCanDownNextFrame = FALSE;
        if (!bCanDownNextFrame) goto lb_return;
        if (m_pBoard->GetCellColor(m_CurPos.x + 2, m_CurPos.y) != RGB(255, 255, 255)) bCanDownNextFrame = FALSE;
        if (!bCanDownNextFrame) goto lb_return;
    }
    else if (m_CurRect == RECT_OBJ_THREE_H)
    {
        if (m_CurPos.x == 12) bCanDownNextFrame = FALSE;  // 2번 조건
        if (!bCanDownNextFrame) goto lb_return;

        // 1번 조건
        if (m_pBoard->GetCellColor(m_CurPos.x, m_CurPos.y) != RGB(255, 255, 255)) bCanDownNextFrame = FALSE;
        if (!bCanDownNextFrame) goto lb_return;
        if (m_pBoard->GetCellColor(m_CurPos.x, m_CurPos.y + 1) != RGB(255, 255, 255)) bCanDownNextFrame = FALSE;
        if (!bCanDownNextFrame) goto lb_return;
        if (m_pBoard->GetCellColor(m_CurPos.x, m_CurPos.y + 2) != RGB(255, 255, 255)) bCanDownNextFrame = FALSE;
        if (!bCanDownNextFrame) goto lb_return;
    }

lb_return:
    return bCanDownNextFrame;
}

void Demo3_4::MoveLeft()
{
    // 현위치 일단 밀기
    ClearCurrentPos();

    // 이동
    m_CurPos.y--;

    BOOL bCanMove = TRUE;

    // 만약 y(col) 이 0보다 작으면 원상복구
    if (m_CurPos.y < 0) 
        bCanMove = FALSE;

    // 만약 이동될 자리에 이미 색이 있다면 원상복구
    if(m_pBoard->GetCellColor(m_CurPos.x, m_CurPos.y) != RGB(255,255,255))
        bCanMove = FALSE;

    if (!bCanMove) m_CurPos.y++;

    // 다시 칠하기
    FillCurrentPos();
}

void Demo3_4::MoveRight()
{
    // 현위치 일단 밀기
    ClearCurrentPos();

    // 이동
    m_CurPos.y++;

    BOOL bCanMove = TRUE;

    // 만약 y(col) 이 0보다 작으면 원상복구
    // H 타입들은 특별히 더 체크
    if (m_CurRect == RECT_OBJ_TWO_H)
    {
        // 만약 y + 1(col) 이 12보다 크면 원상복구
        if (m_CurPos.y + 1 >= 6)
            bCanMove = FALSE;
        
        // 혹은 다른색이 있다면 원상복구
        if (m_pBoard->GetCellColor(m_CurPos.x, m_CurPos.y + 1) != RGB(255, 255, 255))
        {
            bCanMove = FALSE;
        }
    }
    else if (m_CurRect == RECT_OBJ_THREE_H)
    {
        // 만약 y(col) 이 12보다 크면 원상복구
        if (m_CurPos.y + 2 >= 6)
            bCanMove = FALSE;

        if (m_pBoard->GetCellColor(m_CurPos.x, m_CurPos.y + 2) != RGB(255, 255, 255))
        {
            bCanMove = FALSE;
        }
    }
    else
    {
        // 만약 y(col) 이 12보다 크면 원상복구
        if (m_CurPos.y >= 6)
            bCanMove = FALSE;

        if (m_pBoard->GetCellColor(m_CurPos.x, m_CurPos.y) != RGB(255, 255, 255))
        {
            bCanMove = FALSE;
        }
    }

    // 원상복구
    if (!bCanMove) m_CurPos.y--;

    // 다시 칠하기
    FillCurrentPos();
}

void Demo3_4::ClearCurrentPos()
{
    switch (m_CurRect)
    {
    case RECT_OBJ_ONE:
        m_pBoard->SetCellColor(m_CurPos.x, m_CurPos.y, RGB(255, 255, 255));
        break;
    case RECT_OBJ_TWO_V:
        m_pBoard->SetCellColor(m_CurPos.x, m_CurPos.y, RGB(255, 255, 255));
        m_pBoard->SetCellColor(m_CurPos.x + 1, m_CurPos.y, RGB(255, 255, 255));
        break;
    case RECT_OBJ_TWO_H:
        m_pBoard->SetCellColor(m_CurPos.x, m_CurPos.y, RGB(255, 255, 255));
        m_pBoard->SetCellColor(m_CurPos.x, m_CurPos.y + 1, RGB(255, 255, 255));
        break;
    case RECT_OBJ_THREE_V:
        m_pBoard->SetCellColor(m_CurPos.x, m_CurPos.y, RGB(255, 255, 255));
        m_pBoard->SetCellColor(m_CurPos.x + 1, m_CurPos.y, RGB(255, 255, 255));
        m_pBoard->SetCellColor(m_CurPos.x + 2, m_CurPos.y, RGB(255, 255, 255));
        break;
    case RECT_OBJ_THREE_H:
        m_pBoard->SetCellColor(m_CurPos.x, m_CurPos.y, RGB(255, 255, 255));
        m_pBoard->SetCellColor(m_CurPos.x, m_CurPos.y + 1, RGB(255, 255, 255));
        m_pBoard->SetCellColor(m_CurPos.x, m_CurPos.y + 2, RGB(255, 255, 255));
        break;
    case RECT_OBJ_NONE:
        break;
    default:
        break;
    }
}

void Demo3_4::FillCurrentPos()
{
    switch (m_CurRect)
    {
    case RECT_OBJ_ONE:
        m_pBoard->SetCellColor(m_CurPos.x, m_CurPos.y, m_CurColor);
        break;
    case RECT_OBJ_TWO_V:
        m_pBoard->SetCellColor(m_CurPos.x, m_CurPos.y, m_CurColor);
        m_pBoard->SetCellColor(m_CurPos.x + 1, m_CurPos.y, m_CurColor);
        break;
    case RECT_OBJ_TWO_H:
        m_pBoard->SetCellColor(m_CurPos.x, m_CurPos.y, m_CurColor);
        m_pBoard->SetCellColor(m_CurPos.x, m_CurPos.y + 1, m_CurColor);
        break;
    case RECT_OBJ_THREE_V:
        m_pBoard->SetCellColor(m_CurPos.x, m_CurPos.y, m_CurColor);
        m_pBoard->SetCellColor(m_CurPos.x + 1, m_CurPos.y, m_CurColor);
        m_pBoard->SetCellColor(m_CurPos.x + 2, m_CurPos.y, m_CurColor);
        break;
    case RECT_OBJ_THREE_H:
        m_pBoard->SetCellColor(m_CurPos.x, m_CurPos.y, m_CurColor);
        m_pBoard->SetCellColor(m_CurPos.x, m_CurPos.y + 1, m_CurColor);
        m_pBoard->SetCellColor(m_CurPos.x, m_CurPos.y + 2, m_CurColor);
        break;
    case RECT_OBJ_NONE:
        break;
    default:
        break;
    }
}

LRESULT Demo3_4::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    std::shared_ptr<Demo3_4> pDemo = CUR_DEMO(Demo3_4);

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

    default:
        break;
    }
    
    return DefWindowProc(hWnd, message, wParam, lParam);
}
