#include "../pch.h"
#include "Demo5_4.h"
#include "../TextBox.h"
#include "../Utils.h"
#include "../Caret.h"
#include "../GameBoard.h"
#include "../Animation.h"
#include "../Image.h"
#include "../resource.h"

using namespace std;
using namespace shapes;

BOOL Demo5_4::Initialize()
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

void Demo5_4::OnCreate(HWND hWnd)
{
    BOOL bResult = TRUE;
    TIMER.Initialize(hWnd);

    m_pAnim = make_shared<Animation>();
    m_pAnim->LoadFromFile(L"animation_sheet.png");
    m_pAnim->RegisterAnimation("idle_right", C_RECT(0, 0, 100, 100), 100, 8);
    m_pAnim->RegisterAnimation("idle_left", C_RECT(0, 100, 100, 200), 100, 8);
    
    m_pAnim->RegisterAnimation("run_right", C_RECT(0, 200, 100, 300), 100, 8);
    m_pAnim->RegisterAnimation("run_left", C_RECT(0, 300, 100, 400), 100, 8);

    m_pAnim->SetAnimation("run_right");
    m_pAnim->SetDrawRect(C_RECT(550, 400, 650, 500));

    m_pBkImg = make_shared<Image>();
    m_pBkImg->LoadFromFile(L"Background.png");
    m_pBkImg->SetDrawRect(C_RECT(0, 0, m_AppDesc.wndSize.width, m_AppDesc.wndSize.height));

    m_moveDir = (MOVE_DIR_5_4)RANDOM.GenerateRandom(0, 3);

    if (!bResult) __debugbreak();
}

void Demo5_4::HandleMenu(WORD param)
{
}

void Demo5_4::CheckCollision()
{
    RECT curRect = m_pAnim->GetDrawRect();

    if (curRect.top < 0)
    {
        m_moveDir = MOVE_DIR_DOWN;
    }
    else if (curRect.bottom >= m_AppDesc.wndSize.height)
    {
        m_moveDir = MOVE_DIR_UP;
    }
    else if (curRect.left < 0)
    {
        m_moveDir = MOVE_DIR_RIGHT;
    }
    else if (curRect.right >= m_AppDesc.wndSize.width)
    {
        m_moveDir = MOVE_DIR_LEFT;
    }


}

void Demo5_4::Update()
{
    ProcessKeyboard();
    ProcessMouse();

    m_pAnim->Update();

    // Move
    RECT curRect = m_pAnim->GetDrawRect();
    switch (m_moveDir)
    {
    case MOVE_DIR_UP:
        curRect.top -= m_moveSpeed;
        curRect.bottom -= m_moveSpeed;
        break;
    case MOVE_DIR_DOWN:
        curRect.top += m_moveSpeed;
        curRect.bottom += m_moveSpeed;
        break;
    case MOVE_DIR_LEFT:
        curRect.left -= m_moveSpeed;
        curRect.right -= m_moveSpeed;
        break;
    case MOVE_DIR_RIGHT:
        curRect.left += m_moveSpeed;
        curRect.right += m_moveSpeed;
        break;
    default:
        break;
    }

    if (m_modeChangedTime != 0)
    {
        ULONGLONG curTick = GetTickCount64();
        if (curTick - m_modeChangedTime > m_modeTime)
        {
            ChangeMode(SHOW_MODE_DEFAULT);
            m_modeChangedTime = 0;
        }
    }
    m_pAnim->SetDrawRect(curRect);

    CheckCollision();
}

void Demo5_4::Draw(HDC hDC)
{
    m_pBkImg->Draw(hDC);
    m_pAnim->Draw(hDC);

    DrawCoord(hDC);
}

void Demo5_4::ProcessKeyboard()
{
    if (INPUT.GetButtonDown(KEY_TYPE::LEFT))
    {
        m_moveDir = MOVE_DIR_LEFT;
    }
    if (INPUT.GetButtonDown(KEY_TYPE::RIGHT))
    {
        m_moveDir = MOVE_DIR_RIGHT;
    }
    if (INPUT.GetButtonDown(KEY_TYPE::UP))
    {
        m_moveDir = MOVE_DIR_UP;
    }
    if (INPUT.GetButtonDown(KEY_TYPE::DOWN))
    {
        m_moveDir = MOVE_DIR_DOWN;
    }

    if (INPUT.GetButtonDown(KEY_TYPE::E))
    {
        ChangeMode(SHOW_MODE_BIG);
        m_modeChangedTime = GetTickCount64();
    }
    if (INPUT.GetButtonDown(KEY_TYPE::S))
    {
        ChangeMode(SHOW_MODE_SMALL);
        m_modeChangedTime = GetTickCount64();
    }
}

void Demo5_4::ProcessMouse()
{
}

LRESULT Demo5_4::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    std::shared_ptr<Demo5_4> pDemo = CUR_DEMO(Demo5_4);

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