#include "../pch.h"
#include "Demo3_1.h"
#include "../TextBox.h"
#include "../Utils.h"
#include "../Caret.h"
#include "../GameBoard.h"

using namespace std;
using namespace shapes;

BOOL Demo3_1::Initialize()
{
    m_pProcFunction = WndProc;

    m_AppDesc.wndName = L"Demo2-13";
    m_AppDesc.wndStyle = WS_OVERLAPPEDWINDOW;
    m_AppDesc.backgroundColor = WHITE_BRUSH;
    m_AppDesc.wndIcon = IDI_APPLICATION;
    m_AppDesc.wndCursor = IDC_ARROW;
    m_AppDesc.wndPosition.x = 100;
    m_AppDesc.wndPosition.y = 50;
    m_AppDesc.wndSize.width = 1000;
    m_AppDesc.wndSize.height = 1000;
	m_AppDesc.appRunMode = APP_RUN_MODE_GAME_LOOP;

    return 0;
}

void Demo3_1::OnCreate(HWND hWnd)
{
    // TimerManager 는 Core 가 아닌 여기서 초기화되어야 함
    // 이유 -> WM_CREATE 이전에는 HWND 가 안나옴 -> 초기화 없이 타이머를 만들면 초기화 안된상태에서 타이머가 작동 -> 작동 안됨

    BOOL bResult = TRUE;
    TIMER.Initialize(hWnd);

	m_pGameBoard = make_shared<GameBoard>();
	m_pGameBoard->Create(40, 40, 100, 100, 20, 20);

    m_pPlayer = make_shared<Player3_1>();
	m_pPlayer->Create();

    for (int i = 0; i < 20; i++)
    {
		auto p = make_shared<Tail3_1>();
		p->Create(nTails++);
		m_pTails.push_back(p);
    }

    m_PrevPlayerUpdateTick = TIME.GetCurrent();
    m_PrevCollisionGuardTick = TIME.GetCurrent();

    if (!bResult) __debugbreak();
}

void Demo3_1::ProcessKeyboard()
{
    if (INPUT.GetButton(KEY_TYPE::UP))
    {
        m_pPlayer->SetMoveDirection(PLAYER_MOVE_DIRECTION::PLAYER_MOVE_UP);
    }
    else if (INPUT.GetButton(KEY_TYPE::DOWN))
    {
        m_pPlayer->SetMoveDirection(PLAYER_MOVE_DIRECTION::PLAYER_MOVE_DOWN);
    }
    else if (INPUT.GetButton(KEY_TYPE::LEFT))
    {
        m_pPlayer->SetMoveDirection(PLAYER_MOVE_DIRECTION::PLAYER_MOVE_LEFT);
    }
    else if (INPUT.GetButton(KEY_TYPE::RIGHT))
    {
        m_pPlayer->SetMoveDirection(PLAYER_MOVE_DIRECTION::PLAYER_MOVE_RIGHT);
    }
	else if (INPUT.GetButton(KEY_TYPE::PLUS))
	{
        m_PlayerUpdateTick -= 10;
		if (m_PlayerUpdateTick < 100)
		{
			m_PlayerUpdateTick = 100;
		}
		m_TailUpdateTick = m_PlayerUpdateTick - 50;
	}
    else if (INPUT.GetButton(KEY_TYPE::MINUS))
    {
        m_PlayerUpdateTick += 10;
		if (m_PlayerUpdateTick > 10000)
		{
			m_PlayerUpdateTick = 10000;
		}
        m_TailUpdateTick = m_PlayerUpdateTick - 50;
    }
	else if (INPUT.GetButtonDown(KEY_TYPE::S))
	{
		m_bGameStart = !m_bGameStart;
	}
	else if (INPUT.GetButtonDown(KEY_TYPE::J))
	{
		m_pPlayer->Jump();
	}
	else if (INPUT.GetButtonDown(KEY_TYPE::T))
	{
		m_pPlayer->ChangePlayerToTail();
	}
	else if (INPUT.GetButtonDown(KEY_TYPE::Q))
	{
		DestroyWindow(CUR_HWND);
	}
}

void Demo3_1::ProcessMouse()
{
    if (INPUT.GetButtonDown(KEY_TYPE::LBUTTON))
    {
        POINT p = m_pGameBoard->PointToBoardCoord(INPUT.GetMousePos());

		if (p.x == m_pPlayer->GetOffset().x && p.y == m_pPlayer->GetOffset().y)
		{
            m_pPlayer->Inflate();
		}
        // 나머지는 걍 안함ㅇㅇ
	}
    else if (INPUT.GetButtonDown(KEY_TYPE::RBUTTON))
    {
        POINT p = m_pGameBoard->PointToBoardCoord(INPUT.GetMousePos());

        if (p.x == m_pPlayer->GetOffset().x && p.y == m_pPlayer->GetOffset().y)
        {
            return;
        }

        for (const auto& tail : m_pTails)
        {
			if (p.x == tail->GetOffset().x && p.y == tail->GetOffset().y)
			{
                return;
			}
        }

        CreateObstacle(p);


    }
}

void Demo3_1::CheckCollision()
{
	// Player vs Tail
    POINT playerPos = m_pPlayer->GetOffset();

	for (const auto& p : m_pTails)
	{
		if (p->GetCollisionGuard()) continue;

		POINT tailPos = p->GetOffset();
        if (playerPos.x == tailPos.x && playerPos.y == tailPos.y)
        {
			if (p->GetStateType() == TAIL_STATE_FOOD)
			{
				p->ChangeState(TAIL_STATE_FREE);
			}
			else if (p->GetStateType() == TAIL_STATE_FREE)
			{
                p->ChangeState(TAIL_STATE_FOLLOW_PLAYER);
				m_pPlayer->AddTail(p);
			}
        }
	}


	// Tail vs Tail
	for (int i = 0; i < m_pTails.size(); i++)
	{
		for (int j = i + 1; j < m_pTails.size(); j++)
		{
            if (m_pTails[i]->GetSomeoneFollowMe()) continue;

			if (m_pTails[i]->GetOffset().x == m_pTails[j]->GetOffset().x &&
				m_pTails[i]->GetOffset().y == m_pTails[j]->GetOffset().y)
			{
				if (m_pTails[i]->GetStateType() == TAIL_STATE_FREE &&
                    m_pTails[j]->GetStateType() == TAIL_STATE_FREE)
				{
					m_pTails[i]->SetSomeoneFollowMe(TRUE);
					m_pTails[j]->ChangeStateToFollowTail(m_pTails[i]->GetID());
				}
			}
		}
	}
}

void Demo3_1::CreateObstacle(POINT pos)
{
	if (m_ObstaclePos.size() >= 20) return;

    m_ObstaclePos.push_back(pos);
}

void Demo3_1::Update()
{
    ProcessKeyboard();
    ProcessMouse();

    if (m_bGameStart)
    {
        ULONGLONG curTick = GetTickCount64();

        if (curTick - m_PrevPlayerUpdateTick > m_PlayerUpdateTick)
        {
            m_PrevPlayerUpdateTick = curTick;
            m_pPlayer->Move();
        }

        if (curTick - m_PrevTailUpdateTick > m_TailUpdateTick)
        {
            m_PrevTailUpdateTick = curTick;
            for (auto& p : m_pTails)
            {
                p->Move();
            }
        }

        if (curTick - m_PrevCollisionGuardTick > m_TailCollisionGuardTick)
        {
            m_PrevCollisionGuardTick = curTick;
            for (auto& p : m_pTails)
            {
                p->SetCollisionGuard(FALSE);
            }
        }


    }

	CheckCollision();
}

void Demo3_1::Draw(HDC hDC)
{
	m_pGameBoard->Draw(hDC);
	m_pPlayer->Draw(hDC);

	for (auto& p : m_pTails)
	{
		p->Draw(hDC);
	}

	DrawObstacle(hDC);
}

void Demo3_1::DrawObstacle(HDC hDC)
{
	for (const auto& p : m_ObstaclePos)
	{
		POINT offset = POINT{ p.x * 20 + m_pGameBoard->GetOffsetX(), p.y * 20 + m_pGameBoard->GetOffsetY() };
		RECT r = C_RECT(offset.x, offset.y, offset.x + 20, offset.y + 20);
		shapes::Rectangle::DrawRectangle(hDC, r, RGB(255, 0, 0), PS_SOLID, 1, RGB(0, 0, 0));
	}
}

LRESULT Demo3_1::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    std::shared_ptr<Demo3_1> pDemo = CUR_DEMO(Demo3_1);

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

///////////////
// Player3_1 //
///////////////

BOOL Player3_1::Create()
{
    m_pPlayerModel = make_shared<shapes::Ellipse>();
    m_pPlayerModel->Create(C_RECT(0, 0, 1, 1));
    m_pPlayerModel->SetScale(POINT{ 20,20 });
    m_pPlayerModel->SetOffset(POINT{ 100, 100 });
    m_Color = RANDOM.GenerateRandomColor();

    return TRUE;
}

BOOL Player3_1::Draw(HDC hDC)
{
    POINT offset = POINT{ m_Position.x * 20, m_Position.y * 20 };
	COLORREF originColor = m_pPlayerModel->GetFrameColor();

	m_pPlayerModel->SetFrameColor(RGB(255, 0, 0));
    m_pPlayerModel->SetFrameWidth(3);
    m_pPlayerModel->AddOffset(offset);
	m_pPlayerModel->SetBackgroundColor(m_Color);
	m_pPlayerModel->DrawInWindowCoord(hDC);
	m_pPlayerModel->AddOffset(POINT{ -offset.x, -offset.y });
    m_pPlayerModel->SetFrameWidth(1);
	m_pPlayerModel->SetFrameColor(originColor);

	return 0;
}

void Player3_1::Move()
{
    UpdateTailPos();

	POINT origin = m_Position;

    if (m_bJumped)
    {
        if (m_MoveDirection == PLAYER_MOVE_LEFT || m_MoveDirection == PLAYER_MOVE_RIGHT)
        {
            if (m_JumpUpCount < 4)
            {
				MoveUp();
                m_JumpUpCount++;
                m_JumpDownCount++;
			}
            else
            {
				MoveDown();
                m_JumpDownCount--;
                if (m_JumpDownCount <= 0)
                {
					m_JumpUpCount = 0;
					m_JumpDownCount = 0;
                    m_bJumped = FALSE;
                }
            }
        }
        else
        {
            if (m_JumpUpCount < 4)
            {
                MoveLeft();
                m_JumpUpCount++;
                m_JumpDownCount++;
            }
			else
			{
                MoveRight();
                m_JumpDownCount--;
				if (m_JumpDownCount <= 0)
				{
                    m_JumpUpCount = 0;
                    m_JumpDownCount = 0;
					m_bJumped = FALSE;
				}
			}
        }
    }
    else
    {
        if (m_MoveDirection == PLAYER_MOVE_DIRECTION::PLAYER_MOVE_RIGHT)
        {
            MoveRight();
        }
        else if (m_MoveDirection == PLAYER_MOVE_DIRECTION::PLAYER_MOVE_LEFT)
        {
            MoveLeft();
        }
        else if (m_MoveDirection == PLAYER_MOVE_DIRECTION::PLAYER_MOVE_UP)
        {
            MoveUp();
        }
        else if (m_MoveDirection == PLAYER_MOVE_DIRECTION::PLAYER_MOVE_DOWN)
        {
            MoveDown();
        }
    }

	auto obs = CUR_DEMO(Demo3_1)->GetObstaclePos();
	for (const auto& p : obs)
	{
		if (m_Position.x == p.x && m_Position.y == p.y)
		{
            // 방향 전환
			if (m_MoveDirection == PLAYER_MOVE_UP)
			{
				m_Position = origin;
				m_MoveDirection = PLAYER_MOVE_DOWN;
			}
			else if (m_MoveDirection == PLAYER_MOVE_DOWN)
			{
                m_Position = origin;
				m_MoveDirection = PLAYER_MOVE_UP;
			}
			else if (m_MoveDirection == PLAYER_MOVE_LEFT)
			{
                m_Position = origin;
				m_MoveDirection = PLAYER_MOVE_RIGHT;
			}
			else if (m_MoveDirection == PLAYER_MOVE_RIGHT)
			{
                m_Position = origin;
				m_MoveDirection = PLAYER_MOVE_LEFT;
			}
		}
	}

}

void Player3_1::UpdateTailPos()
{
    if (m_pTails.empty()) return;

    for (int i = m_pTails.size() - 1; i > 0; i--) 
    {
        m_pTails[i]->SetOffset(m_pTails[i - 1]->GetOffset());
    }

    // 첫 번째 Tail에 새로운 Offset 설정
    m_pTails[0]->SetOffset(m_Position);

}

void Player3_1::MoveUp()
{
    m_Position.y--;
    if (m_Position.y < 0)
    {
        m_Position.y++;
        m_Position.x++;
        if (m_Position.x > 39)
        {
            m_Position.x = 0;
        }
        m_MoveDirection = PLAYER_MOVE_DOWN;
    }
}

void Player3_1::MoveDown()
{
    m_Position.y++;
    if (m_Position.y > 39)
    {
        m_Position.y--;
        m_Position.x++;
        if (m_Position.x > 39)
        {
            m_Position.x = 0;
        }
        m_MoveDirection = PLAYER_MOVE_UP;
    }
}

void Player3_1::MoveLeft()
{
    m_Position.x--;
    if (m_Position.x < 0)
    {
        m_Position.x++;
        m_Position.y++;
        if (m_Position.y > 39)
        {
            m_Position.y = 0;
        }
        m_MoveDirection = PLAYER_MOVE_RIGHT;
    }
}

void Player3_1::MoveRight()
{
    m_Position.x++;
    if (m_Position.x > 39)
    {
        m_Position.x--;
        m_Position.y++;
        if (m_Position.y > 39)
        {
            m_Position.y = 0;
        }
        m_MoveDirection = PLAYER_MOVE_LEFT;
    }
}

void Player3_1::Jump()
{
	m_bJumped = TRUE;
}

void Player3_1::Inflate()
{
}

void Player3_1::Deflate()
{
}

void Player3_1::ChangePlayerToTail()
{
	if (m_pTails.empty()) return;

	std::swap(m_pTails.front()->GetModel(), static_pointer_cast<Shapes>(m_pPlayerModel));

	COLORREF temp = m_Color;
	m_Color = m_pTails.back()->GetColor();
	m_pTails.back()->SetColor(temp);

}

/////////////
// Tail3_1 //
/////////////

BOOL Tail3_1::Create(int ID)
{
    m_Color = RANDOM.GenerateRandomColor();

    auto p = make_shared<shapes::Rectangle>();
    p->Create(C_RECT(0, 0, 1, 1));
    p->SetScale(POINT{ 10,10 });
    p->SetOffset(POINT{ 100, 100 });

    m_Position = RANDOM.GenerateRandomPoint(0, 39);
    m_MoveType = (TAIL_MOVE_TYPE)RANDOM.GenerateRandom(0, 4);

    if (m_MoveType == TAIL_MOVE_TRIANGLE)
    {
		m_PrevTriangleMoveTick = GetTickCount64();
    }

    m_pTailModel = p;
	m_TailID = ID;

    return TRUE;
}

BOOL Tail3_1::Draw(HDC hDC)
{
	if (m_StateType == TAIL_STATE_FOOD)
	{
		auto p = static_pointer_cast<shapes::Rectangle>(m_pTailModel);
        POINT offset = POINT{ (m_Position.x * 20) + 5, (m_Position.y * 20) + 5 };
        p->AddOffset(offset);
		p->SetBackgroundColor(m_Color);
        p->DrawInWindowCoord(hDC);
        p->AddOffset(POINT{ -offset.x, -offset.y });
	}
	else
	{
		auto p = static_pointer_cast<shapes::Ellipse>(m_pTailModel);
		POINT offset = POINT{ m_Position.x * 20, m_Position.y * 20 };
		p->AddOffset(offset);
        p->SetBackgroundColor(m_Color);
		p->DrawInWindowCoord(hDC);
		p->AddOffset(POINT{ -offset.x, -offset.y });
	}

    return TRUE;
}

void Tail3_1::Move()
{
    if (m_StateType == TAIL_STATE_FREE)
    {
        // 나를 따라오는 놈이 있다면 찾아서 업데이트
		if (m_bSomeoneFollowMe)
		{
			auto& tails = CUR_DEMO(Demo3_1)->GetTails();
			for (auto& p : tails)
			{
				if (p->m_FollowID == m_TailID)
				{
					p->SetOffset(m_Position);
					break;
				}
			}
		}


        if (m_MoveType == TAIL_MOVE_RIGHT)
        {
            m_Position.x++;
            if (m_Position.x > 39)
            {
                m_Position.x--;
                m_Position.y++;
                if (m_Position.y > 39)
                {
                    m_Position.y = 0;
                }
                m_MoveType = TAIL_MOVE_LEFT;
            }
        }
        else if (m_MoveType == TAIL_MOVE_LEFT)
        {
            m_Position.x--;
            if (m_Position.x < 0)
            {
                m_Position.x++;
                m_Position.y++;
                if (m_Position.y > 39)
                {
                    m_Position.y = 0;
                }
                m_MoveType = TAIL_MOVE_RIGHT;
            }
        }
        else if (m_MoveType == TAIL_MOVE_UP)
        {
            m_Position.y--;
            if (m_Position.y < 0)
            {
                m_Position.y++;
                m_Position.x++;
                if (m_Position.x > 39)
                {
                    m_Position.x = 0;
                }
                m_MoveType = TAIL_MOVE_DOWN;
            }
        }
        else if (m_MoveType == TAIL_MOVE_DOWN)
        {
            m_Position.y++;
            if (m_Position.y > 39)
            {
                m_Position.y--;
                m_Position.x++;
                if (m_Position.x > 39)
                {
                    m_Position.x = 0;
                }
                m_MoveType = TAIL_MOVE_UP;
            }
        }
        else if (m_MoveType == TAIL_MOVE_TRIANGLE)
        {
            // ??????? 
            // Tick 을 이용해서 방향을 바꾸면 될거같긴 함

            ULONGLONG curTick = GetTickCount64();

            if (curTick - m_PrevTriangleMoveTick > m_TriangleMoveTick)
            {
                m_PrevTriangleMoveTick = curTick;
                m_TriangleMoveCount++;
            }

            if (m_TriangleMoveCount % 3 == 0)
            {
				m_Position.x++;
				m_Position.y++;
                if (m_Position.x > 39)
                {
                    m_Position.x = 0;
                }
				if (m_Position.y > 39)
				{
					m_Position.y = 0;
				}
            }
			else if (m_TriangleMoveCount % 3 == 1)
			{
                m_Position.x--;
				if (m_Position.x < 0)
				{
					m_Position.x = 39;
				}
			}
            else if (m_TriangleMoveCount % 3 == 2)
            {
                m_Position.x++;
                m_Position.y--;
				if (m_Position.x > 39)
				{
					m_Position.x = 0;
				}
                if (m_Position.y < 0)
                {
                    m_Position.y = 39;
                }
            }
        }
    }
    
	// TAIL_STATE_FOOD : NEVER MOVE
	// TAIL_STATE_FOLLOW_PLAYER : Player will control
}

void Tail3_1::ChangeState(TAIL_STATE_TYPE ty)
{
	if (ty == m_StateType)
	{
		return;
	}

	m_pTailModel.reset();

	if (ty == TAIL_STATE_FOOD)
	{
        auto p = make_shared<shapes::Rectangle>();
        p->Create(C_RECT(0, 0, 1, 1));
        p->SetScale(POINT{ 10,10 });
        p->SetOffset(POINT{ 100, 100 });
        p->SetBackgroundColor(m_Color);
		m_pTailModel = p;
        m_StateType = TAIL_STATE_FOOD;
	}
	else if (ty == TAIL_STATE_FREE)
	{
		auto p = make_shared<shapes::Ellipse>();
		p->Create(C_RECT(0, 0, 1, 1));
        p->SetScale(POINT{ 20,20 });
        p->SetOffset(POINT{ 100, 100 });
		p->SetBackgroundColor(m_Color);
		m_pTailModel = p;
        m_StateType = TAIL_STATE_FREE;
		SetCollisionGuard(TRUE);
	}
	else if (ty == TAIL_STATE_FOLLOW_PLAYER)
	{
        auto p = make_shared<shapes::Ellipse>();
        p->Create(C_RECT(0, 0, 1, 1));
        p->SetScale(POINT{ 20,20 });
        p->SetOffset(POINT{ 100, 100 });
        p->SetBackgroundColor(m_Color);
		m_pTailModel = p;
        m_StateType = TAIL_STATE_FOLLOW_PLAYER;
	}
}

void Tail3_1::ChangeStateToFollowTail(int id)
{
	if (m_StateType == TAIL_STATE_FOLLOW_TAIL)
	{
		return;
	}

	m_StateType = TAIL_STATE_FOLLOW_TAIL;
	m_FollowID = id;
}
