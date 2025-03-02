#include "../pch.h"
#include "Demo4_1.h"
#include "../TextBox.h"
#include "../Utils.h"
#include "../Caret.h"
#include "../GameBoard.h"

using namespace std;
using namespace shapes;

BOOL Demo4_1::Initialize()
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
    m_AppDesc.wndSize.height = 1000;
	m_AppDesc.appRunMode = APP_RUN_MODE_GAME_LOOP;

    // 메뉴 설정
    m_AppDesc.menuName = IDR_MENU_4_1;

    return 0;
}

void Demo4_1::OnCreate(HWND hWnd)
{
    BOOL bResult = TRUE;
    TIMER.Initialize(hWnd);

    // Ball
    m_pBall = make_shared<Ball_4_1>();
    m_pBall->Create();

    // Bar
    m_pBar = make_shared<Bar_4_1>();
    m_pBar->Create();

    // Bricks will init in ResetBricks

    SetGame();

    if (!bResult) __debugbreak();
}

void Demo4_1::HandleMenu(WORD param)
{
    switch (param)
    {
    case ID_GAME_START:
        m_bBallMove = TRUE;
        m_bGameRun = TRUE;
        break;

    case ID_GAME_RESET:
        ResetBricks();
        break;

    case ID_GAME_END:
        PostQuitMessage(0);
        break;

    case ID_SPEED_FAST:
        m_pBall->SetBallSpeed(10);
        break;

    case ID_SPEED_MEDIUM:
        m_pBall->SetBallSpeed(5);
        break;

    case ID_SPEED_SLOW:
        m_pBall->SetBallSpeed(1);
        break;

    case ID_COLOR_CYAN:
        m_pBall->SetBackgroundColor(RGB(0, 255, 255));
        break;

    case ID_COLOR_MAGENTA:
        m_pBall->SetBackgroundColor(RGB(255, 0, 255));
        break;

    case ID_COLOR_YELLOW:
        m_pBall->SetBackgroundColor(RGB(255, 255, 0));
        break;

    case ID_BALLSIZE_SMALL:
        m_pBall->SetScale(POINT{ 10,10 });
        break;

    case ID_BALLSIZE_BIG:
        m_pBall->SetScale(POINT{ 20,20 });
        break;

    case ID_BRICKCOLUMN_3:
        m_nBrickRows = 3;
        ResetBricks();
        break;

    case ID_BRICKCOLUMN_4:
        m_nBrickRows = 4;
        ResetBricks();
        break;

    case ID_BRICKCOLUMN_5:
        m_nBrickRows = 5;
        ResetBricks();
        break;

    default:
        break;
    }
}

void Demo4_1::Update()
{
    ProcessKeyboard();
    ProcessMouse();


    ULONGLONG curTick = GetTickCount64();

    if (curTick - m_ullPrevUpdateTick > 1)
    {
        if (m_bGameRun)
        {
            CheckGameStatus();

            if (m_bBallMove)
            {
                m_pBall->Update();
            }
            m_pBar->Update();
            for_each(m_pBricks.begin(), m_pBricks.end(), [](auto& p) { p->Update(); });

            CheckCollision();
        }

        m_ullPrevUpdateTick = curTick;
    }
}

void Demo4_1::Draw(HDC hDC)
{
    m_pBall->Draw(hDC);
    m_pBar->Draw(hDC);
    for_each(m_pBricks.begin(), m_pBricks.end(), [&hDC](auto& p) { p->Draw(hDC); });

    if (!m_bGameRun)
    {
        // Show Destroyed Ball Count
        int nDestroyed = 0;
        nDestroyed = 30 - m_pBricks.size();
        TextBox::DrawFormattedString(hDC, { 0,0 }, L"Destroyed Balls : %d", nDestroyed);

        // Show Destroying Ball Count
        int nDestroying = 0;
        for_each(m_pBricks.begin(), m_pBricks.end(), [&nDestroying](std::shared_ptr<Brick_4_1>& p)
            {
                if (p->m_State == BRICK_STATE_DESTROY) nDestroying++;
            }
        );
        TextBox::DrawFormattedString(hDC, { 0,20 }, L"Color Changed Balls : %d", nDestroying);
    }

}

void Demo4_1::ProcessKeyboard()
{
    if (INPUT.GetButtonDown(KEY_TYPE::S))
    {
        m_bBallMove = !m_bBallMove;
    }
    else if (INPUT.GetButtonDown(KEY_TYPE::P))
    {
        m_bGameRun = !m_bGameRun;
    }
    else if (INPUT.GetButtonDown(KEY_TYPE::N))
    {
        // need to fill bricks first
        SetGame();
    }
    else if (INPUT.GetButtonDown(KEY_TYPE::PLUS))
    {
        // TODO : Increase Ball Speed
        m_pBall->IncreaseBallSpeed();
    }
    else if (INPUT.GetButtonDown(KEY_TYPE::MINUS))
    {
        // TODO : Decrease Ball Speed
        m_pBall->DecreaseBallSpeed();
    }
    else if (INPUT.GetButtonDown(KEY_TYPE::Q))
    {
        DestroyWindow(CUR_HWND);
    }
}

void Demo4_1::ProcessMouse()
{
    if (INPUT.GetButtonDown(KEY_TYPE::LBUTTON))
    {
        POINT mousePos = INPUT.GetMousePos();
        auto p = static_pointer_cast<shapes::Rectangle>(m_pBar->GetModel());

        if (p->IsInRect(mousePos))
        {
            m_bDrag = TRUE;
        }

    }
    else if (INPUT.GetButton(KEY_TYPE::LBUTTON))
    {
        if (m_bDrag)
        {
            POINT mousePos = INPUT.GetMousePos();
            m_pBar->SetPosition(POINT{ mousePos.x, m_OriginBarPos.y });
        }
    }
    else if (INPUT.GetButtonUp(KEY_TYPE::LBUTTON))
    {
        if (m_bDrag)
        {
            m_bDrag = FALSE;
            m_pBar->SetPosition(m_OriginBarPos);
        }
    }
}

void Demo4_1::SetGame()
{
    // Ball
    m_pBall->SetPosition(m_OriginBallPos);
    m_pBall->SetScale(POINT(10, 10));
    m_pBall->SetBackgroundColor(RANDOM.GenerateRandomColor());

    // Bar
    m_pBar->SetPosition(m_OriginBarPos);
    m_pBar->SetScale(POINT{ 1, 1 });
    m_pBar->SetBackgroundColor(RANDOM.GenerateRandomColor());

    // Brick
    ResetBricks();

}

void Demo4_1::CheckCollision()
{
    RECT ballRect = static_pointer_cast<shapes::Ellipse>(m_pBall->GetModel())->GetRect();

    // 1. Ball vs Bar
    RECT outRect;
    if (static_pointer_cast<shapes::Rectangle>(m_pBar->GetModel())->Intersects(ballRect, outRect))
    {
        m_pBall->HandleCollision("Bar");
    }


    // 2. Ball vs Brick
    for (const auto& brick : m_pBricks)
    {
        RECT brickRect = static_pointer_cast<shapes::Rectangle>(brick->GetModel())->GetRect();
        
        if (static_pointer_cast<shapes::Rectangle>(brick->GetModel())->Intersects(ballRect, outRect))
        {
            int overlapLeft = outRect.right - brickRect.left;
            int overlapRight = brickRect.right - outRect.left;
            int overlapTop = outRect.bottom - brickRect.top;
            int overlapBottom = brickRect.bottom - outRect.top;

            int minOverlapped = min(min(min(overlapLeft, overlapRight), overlapTop), overlapBottom);

            if (minOverlapped == overlapLeft)
            {
                m_pBall->HandleCollision("Brick_Left");
            }
            else if (minOverlapped == overlapRight)
            {
                m_pBall->HandleCollision("Brick_Right");
            }
            else if (minOverlapped == overlapTop)
            {
                m_pBall->HandleCollision("Brick_Top");
            }
            else if (minOverlapped == overlapBottom)
            {
                m_pBall->HandleCollision("Brick_Bottom");
            }

            // 벽돌 상태 변경
            brick->HandleCollision("Ball");

            // 충돌 한번 감지되면 끝
            break;
        }


    }


    // 3. Ball vs Wall
    if (ballRect.left < 0)
    {
        m_pBall->HandleCollision("Wall_Left");
    }
    else if (ballRect.right >= m_AppDesc.wndSize.width)
    {
        m_pBall->HandleCollision("Wall_Right");
    }
    else if (ballRect.top < 0)
    {
        m_pBall->HandleCollision("Wall_Top");
    }
    else if (ballRect.bottom >= m_AppDesc.wndSize.height)
    {
        m_pBall->HandleCollision("Wall_Bottom");
    }


}

void Demo4_1::CheckGameStatus()
{
    // Erase WAIT_FOR_ERASE bricks
    auto findLamda = [](std::shared_ptr<Brick_4_1>& p) -> bool
        {
            return p->m_State == BRICK_STATE_WAIT_FOR_ERASE;
        };

    auto findIt = std::find_if(m_pBricks.begin(), m_pBricks.end(), findLamda);
    while (findIt != m_pBricks.end())
    {
        m_pBricks.erase(findIt);
        findIt = std::find_if(m_pBricks.begin(), m_pBricks.end(), findLamda);
    }

    // if bricks is empty -> Reset game
    if (m_pBricks.empty())
    {
        // need to fill bricks first
        for (int i = 0; i < 3; i++)
        {
            for (int i = 0; i < 10; i++)
            {
                auto p = make_shared<Brick_4_1>();
                p->Create();
                m_pBricks.push_back(p);
            }
        }

        // Reset
        SetGame();
    }

}

void Demo4_1::ResetBricks()
{
    m_pBricks.clear();

    // Brick 3 x 10
    for (int i = 0; i < m_nBrickRows; i++)
    {
        for (int i = 0; i < m_nBrickCols; i++)
        {
            auto p = make_shared<Brick_4_1>();
            p->Create();
            m_pBricks.push_back(p);
        }
    }

    COLORREF brickColor = RANDOM.GenerateRandomColor();
    POINT brickOffset = POINT{ BRICK_BEGIN_OFFSET_X, BRICK_BEGIN_OFFSET_Y };
    for (int i = 0; i < m_nBrickRows; i++)
    {
        brickOffset.y = (BRICK_HEIGHT * i) + BRICK_BEGIN_OFFSET_Y;
        for (int j = 0; j < m_nBrickCols; j++)
        {
            brickOffset.x = (BRICK_WIDTH * j) + BRICK_BEGIN_OFFSET_X;

            int brickIndex = (i * 10) + j;
            m_pBricks[brickIndex]->SetPosition(brickOffset);
            m_pBricks[brickIndex]->SetOrigin();
            m_pBricks[brickIndex]->SetScale(POINT{ BRICK_WIDTH, BRICK_HEIGHT });
            m_pBricks[brickIndex]->SetBackgroundColor(brickColor);
        }
    }
}

LRESULT Demo4_1::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    std::shared_ptr<Demo4_1> pDemo = CUR_DEMO(Demo4_1);

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

// Brick
///////////////////////////////////////////////////////////////////////////////

BOOL Brick_4_1::Create()
{
    auto p = make_shared<shapes::Rectangle>();
    p->Create(C_RECT(0, 0, 1, 1));
    m_pModel = p;

    return TRUE;
}

void Brick_4_1::Update()
{
    // Update Movement(State)
    POINT pos = m_Position;

    if (m_State == BRICK_STATE_MOVE_LEFT)
    {
        pos.x--;
        if (pos.x - m_Origin.x < -100)
        {
            m_State = BRICK_STATE_MOVE_RIGHT;
        }
    }
    else if (m_State == BRICK_STATE_MOVE_RIGHT)
    {
        pos.x++;
        if (pos.x - m_Origin.x > 100)
        {
            m_State = BRICK_STATE_MOVE_LEFT;
        }
    }

    if (m_State == BRICK_STATE_DESTROY)
    {
        m_Scale.x--;
        m_Scale.y--;
        if (m_Scale.x <= 1 || m_Scale.y <= 1)
        {
            m_State = BRICK_STATE_WAIT_FOR_ERASE;
        }
    }

    m_Position = POINT(pos);

    UpdateObjectStateToModel();
}

void Brick_4_1::Draw(HDC hDC)
{
    m_pModel->DrawInWindowCoord(hDC);
}

void Brick_4_1::HandleCollision(const std::string& otherName)
{
    if (otherName == "Ball")
    {
        if (m_State != BRICK_STATE_DESTROY || m_State != BRICK_STATE_WAIT_FOR_ERASE)
        {
            m_BkColor = RANDOM.GenerateRandomColor();
            m_State = BRICK_STATE_DESTROY;
        }
    }
}

// Bar
///////////////////////////////////////////////////////////////////////////////

BOOL Bar_4_1::Create()
{
    auto p = make_shared<shapes::Rectangle>();
    p->Create(C_RECT(-100, -10, 100, 10));
    m_pModel = p;

    return TRUE;
}

void Bar_4_1::Update()
{


    UpdateObjectStateToModel();
}

void Bar_4_1::Draw(HDC hDC)
{
    m_pModel->DrawInWindowCoord(hDC);
}

void Bar_4_1::HandleCollision(const std::string& otherName)
{
}

// Ball
///////////////////////////////////////////////////////////////////////////////

BOOL Ball_4_1::Create()
{
    auto p = make_shared<shapes::Ellipse>();
    p->Create(C_RECT(-1, -1, 1, 1));
    m_pModel = p;
    return TRUE;
}

void Ball_4_1::Update()
{
    POINT pos = m_Position;

    switch (m_ballMove)
    {
    case BALL_MOVE_RIGHT_TOP:
        pos.x += m_ballSpeed;
        pos.y -= m_ballSpeed;
        break;
    case BALL_MOVE_RIGHT_BOTTOM:
        pos.x += m_ballSpeed;
        pos.y += m_ballSpeed;
        break;
    case BALL_MOVE_LEFT_TOP:
        pos.x -= m_ballSpeed;
        pos.y -= m_ballSpeed;
        break;
    case BALL_MOVE_LEFT_BOTTOM:
        pos.x -= m_ballSpeed;
        pos.y += m_ballSpeed;
        break;
    default:
        break;
    }

    m_Position = pos;
    UpdateObjectStateToModel();
}

void Ball_4_1::Draw(HDC hDC)
{
    m_pModel->DrawInWindowCoord(hDC);
}

void Ball_4_1::HandleCollision(const std::string& otherName)
{
    // Handle Wall Collision
    if (otherName == "Wall_Left")
    {
        if (m_ballMove == BALL_MOVE_LEFT_TOP)
        {
            m_ballMove = BALL_MOVE_RIGHT_TOP;
        }
        else if (m_ballMove == BALL_MOVE_LEFT_BOTTOM)
        {
            m_ballMove = BALL_MOVE_RIGHT_BOTTOM;
        }
    }
    else if (otherName == "Wall_Right")
    {
        if (m_ballMove == BALL_MOVE_RIGHT_TOP)
        {
            m_ballMove = BALL_MOVE_LEFT_TOP;
        }
        else if (m_ballMove == BALL_MOVE_RIGHT_BOTTOM)
        {
            m_ballMove = BALL_MOVE_LEFT_BOTTOM;
        }
    }
    else if (otherName == "Wall_Top")
    {
        if (m_ballMove == BALL_MOVE_LEFT_TOP)
        {
            m_ballMove = BALL_MOVE_LEFT_BOTTOM;
        }
        else if (m_ballMove == BALL_MOVE_RIGHT_TOP)
        {
            m_ballMove = BALL_MOVE_RIGHT_BOTTOM;
        }
    }
    else if (otherName == "Wall_Bottom")
    {
        // Set ball to origin pos
        m_ballMove = BALL_MOVE_RIGHT_TOP;
        POINT pos = CUR_DEMO(Demo4_1)->m_pBar->GetPosition();
        m_Position = POINT{ pos.x, pos.y - 20 };
    }

    // Handle Brick Collision
    if (otherName == "Brick_Left")
    {
        if (m_ballMove == BALL_MOVE_RIGHT_TOP)
        {
            m_ballMove = BALL_MOVE_LEFT_TOP;
        }
        else if (m_ballMove == BALL_MOVE_RIGHT_BOTTOM)
        {
            m_ballMove = BALL_MOVE_LEFT_BOTTOM;
        }
    }
    else if (otherName == "Brick_Right")
    {
        if (m_ballMove == BALL_MOVE_LEFT_TOP)
        {
            m_ballMove = BALL_MOVE_RIGHT_TOP;
        }
        else if (m_ballMove == BALL_MOVE_LEFT_BOTTOM)
        {
            m_ballMove = BALL_MOVE_RIGHT_BOTTOM;
        }
    }
    else if (otherName == "Brick_Top")
    {
        if (m_ballMove == BALL_MOVE_LEFT_BOTTOM)
        {
            m_ballMove = BALL_MOVE_LEFT_TOP;
        }
        else if (m_ballMove == BALL_MOVE_RIGHT_BOTTOM)
        {
            m_ballMove = BALL_MOVE_RIGHT_TOP;
        }
    }
    else if (otherName == "Brick_Bottom")
    {
        if (m_ballMove == BALL_MOVE_LEFT_TOP)
        {
            m_ballMove = BALL_MOVE_LEFT_BOTTOM;
        }
        else if (m_ballMove == BALL_MOVE_RIGHT_TOP)
        {
            m_ballMove = BALL_MOVE_RIGHT_BOTTOM;
        }
    }

    // Handle Bar Collision
    if (otherName == "Bar")
    {
        if (m_ballMove == BALL_MOVE_LEFT_BOTTOM)
        {
            m_ballMove = BALL_MOVE_LEFT_TOP;
        }
        else if (m_ballMove == BALL_MOVE_RIGHT_BOTTOM)
        {
            m_ballMove = BALL_MOVE_RIGHT_TOP;
        }
    }

}
