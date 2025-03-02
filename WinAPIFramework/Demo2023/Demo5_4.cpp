#include "../pch.h"
#include "Demo5_2.h"
#include "../TextBox.h"
#include "../Utils.h"
#include "../Caret.h"
#include "../GameBoard.h"
#include "../resource.h"

using namespace std;
using namespace shapes;

BOOL Demo5_2::Initialize()
{
    m_pProcFunction = WndProc;

    m_AppDesc.wndName = L"Demo5-1";
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
    m_AppDesc.menuName = IDR_MENU_5_2;

    return 0;
}

void Demo5_2::OnCreate(HWND hWnd)
{
    BOOL bResult = TRUE;
    TIMER.Initialize(hWnd);

    ResetGame();

    if (!bResult) __debugbreak();
}

void Demo5_2::ResetGame()
{
    m_pPuzzle = make_shared<Puzzle5_2>();
    m_pPuzzle->Create(m_AppDesc.wndSize.width, m_AppDesc.wndSize.height);
}
void Demo5_2::Divide(int row, int col)
{
    m_pPuzzle->ReDivide(row, col);
}

void Demo5_2::HandleMenu(WORD param)
{
    switch (param)
    {
    case ID_IMAGE_1:
        m_pPuzzle->SetImage(0);
        break;

    case ID_IMAGE_2:
        m_pPuzzle->SetImage(1);
        break;

    case ID_DIVIDE_3:
        m_pPuzzle->ReDivide(3, 3);
        break;

    case ID_DIVIDE_4:
        m_pPuzzle->ReDivide(4, 4);
        break;

    case ID_DIVIDE_5:
        m_pPuzzle->ReDivide(5, 5);
        break;

    case ID_GAME_START40056:
        break;

    case ID_GAME_SHOWANSWER:
        break;

    case ID_GAME_INVERT:
        break;

    case ID_GAME_STOP:
        break;


    default:
        break;
    }
}

void Demo5_2::Update()
{
    ProcessKeyboard();
    ProcessMouse();

    m_pPuzzle->Update();

}

void Demo5_2::Draw(HDC hDC)
{
    m_pPuzzle->Draw(hDC);

    DrawCoord(hDC);
}

void Demo5_2::ProcessKeyboard()
{
}

void Demo5_2::ProcessMouse()
{
    if (INPUT.GetButtonDown(KEY_TYPE::LBUTTON))
    {
        m_bDrag = TRUE;
        m_DragStartedPos = INPUT.GetMousePos();
    }
    else if (INPUT.GetButtonUp(KEY_TYPE::LBUTTON))
    {
        if(!m_pPuzzle->IsMoving())
        {
            POINT dragEndPos = INPUT.GetMousePos();

            int dx = dragEndPos.x - m_DragStartedPos.x;
            int dy = dragEndPos.y - m_DragStartedPos.y;

            if (abs(dx) > abs(dy))
            {
                if (dx > 0)
                {
                    // Move Right
                    m_pPuzzle->SetBeginMove();
                    m_pPuzzle->SetState(PUZZLE_STATE_MOVE_RIGHT);
                }
                else
                {
                    // Move Left
                    m_pPuzzle->SetBeginMove();
                    m_pPuzzle->SetState(PUZZLE_STATE_MOVE_LEFT);
                }
            }
            else
            {
                if (dy > 0)
                {
                    // Move Down
                    m_pPuzzle->SetBeginMove();
                    m_pPuzzle->SetState(PUZZLE_STATE_MOVE_DOWN);
                }
                else
                {
                    // Move Up
                    m_pPuzzle->SetBeginMove();
                    m_pPuzzle->SetState(PUZZLE_STATE_MOVE_UP);
                }
            }
        }

        m_bDrag = FALSE;
    }

}

LRESULT Demo5_2::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    std::shared_ptr<Demo5_2> pDemo = CUR_DEMO(Demo5_2);

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

// Puzzle
///////////////////////////////////////////////////////////////////////////////////////

void Puzzle5_2::Create(int width, int height)
{
    m_Tiled[0].CreateFromFile(L"bmp1.bmp", C_RECT(0, 0, width, height), m_divRow, m_divCol);
    m_Tiled[1].CreateFromFile(L"dog.bmp", C_RECT(0, 0, width, height), m_divRow, m_divCol);

    ReDivide(m_divRow, m_divCol);
}

void Puzzle5_2::Update()
{
}

void Puzzle5_2::Draw(HDC hDC)
{
    for (int i = 0; i < m_Bitmaps.size(); i++)
    {
        m_Bitmaps[i].Draw(hDC);
    }

    C_SOLID_HBRUSH brush(RGB(255, 0, 0));
    ::FrameRect(hDC, &m_Tiled[m_Selected].GetRect(m_Tiled[m_Selected].GetPosToIndex(m_currentBlankedPos)), brush);
    brush.Destroy();
}

void Puzzle5_2::ReDivide(int row, int col)
{
    m_divRow = row;
    m_divCol = col;
    m_Tiled[0].ReDivide(row, col);
    m_Tiled[1].ReDivide(row, col);

    PushBitmapToDrawVector();
    Shuffle();
}

void Puzzle5_2::Shuffle()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::shuffle(m_Bitmaps.begin(), m_Bitmaps.end(), gen);
}

void Puzzle5_2::PushBitmapToDrawVector()
{
    m_Bitmaps.clear();
    for (int i = 0; i < (m_divRow * m_divCol) - 1; i++)
    {
        m_Bitmaps.push_back(m_Tiled[m_Selected].GetBitmapRect(i));
    }

}

void Puzzle5_2::SetImage(int index)
{
    m_Selected = index;

    PushBitmapToDrawVector();
    Shuffle();
}

void Puzzle5_2::MoveUp()
{
    m_moveTarget->top -= m_moveSpeed;
    m_moveTarget->bottom -= m_moveSpeed;
}

void Puzzle5_2::MoveDown()
{
    m_moveTarget->top += m_moveSpeed;
    m_moveTarget->bottom += m_moveSpeed;
}

void Puzzle5_2::MoveLeft()
{
    m_moveTarget->left -= m_moveSpeed;
    m_moveTarget->right -= m_moveSpeed;
}

void Puzzle5_2::MoveRight()
{
    m_moveTarget->left += m_moveSpeed;
    m_moveTarget->right += m_moveSpeed;
}

BOOL Puzzle5_2::IsMoveComplete()
{
    return (abs(m_moveTarget->left - m_moveEndRect.left) <= m_moveSpeed &&
        abs(m_moveTarget->top - m_moveEndRect.top) <= m_moveSpeed &&
        abs(m_moveTarget->right - m_moveEndRect.right) <= m_moveSpeed &&
        abs(m_moveTarget->bottom - m_moveEndRect.bottom) <= m_moveSpeed);
}
