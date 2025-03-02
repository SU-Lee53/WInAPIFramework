#include "../pch.h"
#include "Demo5_1.h"
#include "../TextBox.h"
#include "../Utils.h"
#include "../Caret.h"
#include "../GameBoard.h"
#include "../resource.h"

using namespace std;
using namespace shapes;

BOOL Demo5_1::Initialize()
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
    m_AppDesc.wndSize.height = 800;
	m_AppDesc.appRunMode = APP_RUN_MODE_GAME_LOOP;

    // 메뉴 설정
    //m_AppDesc.menuName = IDR_MENU_4_4;

    return 0;
}

void Demo5_1::OnCreate(HWND hWnd)
{
    BOOL bResult = TRUE;
    TIMER.Initialize(hWnd);

    ResetGame();

    if (!bResult) __debugbreak();
}

void Demo5_1::ResetGame()
{
    m_mainRect = C_RECT(0, 0, m_AppDesc.wndSize.width, m_AppDesc.wndSize.height);
    m_Bitmaps[0].CreateFromFile(L"bmp1.bmp", m_mainRect);
    m_Bitmaps[1].CreateFromFile(L"bmp1.bmp", C_RECT(m_mainRect.right, m_mainRect.top, m_AppDesc.wndSize.width, m_mainRect.bottom));
    m_Bitmaps[2].CreateFromFile(L"bmp1.bmp", C_RECT(m_mainRect.left, m_mainRect.bottom, m_mainRect.right, m_AppDesc.wndSize.height));
    m_Bitmaps[3].CreateFromFile(L"bmp1.bmp", C_RECT(m_mainRect.right, m_mainRect.bottom, m_AppDesc.wndSize.width, m_AppDesc.wndSize.height));
}

void Demo5_1::HandleMenu(WORD param)
{
    switch (param)
    {
    default:
        break;
    }
}

void Demo5_1::Update()
{
    ProcessKeyboard();
    ProcessMouse();

    // 0번 기준으로 화면 분할
    // 전체화면 기준이면 0번이 전체에 뜸 -> 나머지는 쪼그라들어서 안보임
    RECT rect1 = C_RECT(m_mainRect.right, m_mainRect.top, m_AppDesc.wndSize.width, m_mainRect.bottom);              // 우상단
    RECT rect2 = C_RECT(m_mainRect.left, m_mainRect.bottom, m_mainRect.right, m_AppDesc.wndSize.height);            // 좌하단
    RECT rect3 = C_RECT(m_mainRect.right, m_mainRect.bottom, m_AppDesc.wndSize.width, m_AppDesc.wndSize.height);    // 우하단

    m_Bitmaps[0].drawRect = m_mainRect;
    m_Bitmaps[1].drawRect = rect1;
    m_Bitmaps[2].drawRect = rect2;
    m_Bitmaps[3].drawRect = rect3;

}

void Demo5_1::Draw(HDC hDC)
{
    // 0번이 메인 -> 가장 마지막에 그려져야 함
    m_Bitmaps[1].Draw(hDC, m_drawMode);
    m_Bitmaps[2].Draw(hDC, m_drawMode);
    m_Bitmaps[3].Draw(hDC, m_drawMode);

    if (m_bFullscreen)
    {
        m_Bitmaps[0].drawRect = C_RECT(0, 0, m_AppDesc.wndSize.width, m_AppDesc.wndSize.height);
        m_Bitmaps[0].Draw(hDC, m_drawMode);
    }
    else
    {
        m_Bitmaps[0].Draw(hDC, m_drawMode);
    }
    
    if (m_bMove)
    {
        ULONGLONG cur = ::GetTickCount64();
        if (cur - m_ullPrevMoveTick > m_ullMoveTick)
        {
            for (auto& b : m_Bitmaps)
            {
               b.imageRect.left += 10;
               b.imageRect.right += 10;
            }
            m_ullPrevMoveTick = cur;
        }
    }

    C_SOLID_HBRUSH brush = (RGB(255, 0, 0));

    ::FrameRect(hDC, &m_Bitmaps[m_Seleted].drawRect, brush);

    brush.Destroy();

    DrawCoord(hDC);
}

void Demo5_1::ProcessKeyboard()
{
    if (INPUT.GetButtonDown(KEY_TYPE::R))
    {
        m_drawMode = m_drawMode == SRCCOPY ? NOTSRCCOPY : SRCCOPY;
    }
    else if (INPUT.GetButtonDown(KEY_TYPE::A))
    {
        m_bFullscreen = !m_bFullscreen;
    }
    else if (INPUT.GetButtonDown(KEY_TYPE::S))
    {
        ResetGame();
    }
    else if (INPUT.GetButtonDown(KEY_TYPE::P))
    {
        m_bMove = !m_bMove;
        if (m_bMove)
        {
            m_ullPrevMoveTick = ::GetTickCount64();
        }
    }

    if (INPUT.GetButtonDown(KEY_TYPE::PLUS))
    {
        m_mainRect.right += 10;
        m_mainRect.bottom += 10;
    }
    else if (INPUT.GetButtonDown(KEY_TYPE::MINUS))
    {
        m_mainRect.right -= 10;
        m_mainRect.bottom -= 10;
    }

    if (INPUT.GetButton(KEY_TYPE::LEFT))
    {
        m_Bitmaps[m_Seleted].imageRect.left += 10;
        m_Bitmaps[m_Seleted].imageRect.right += 10;
    }
    else if (INPUT.GetButton(KEY_TYPE::RIGHT))
    {
        m_Bitmaps[m_Seleted].imageRect.left -= 10;
        m_Bitmaps[m_Seleted].imageRect.right -= 10;
    }
}

void Demo5_1::ProcessMouse()
{
    if (INPUT.GetButtonDown(KEY_TYPE::LBUTTON))
    {
        POINT mousePos = INPUT.GetMousePos();
        for (int i = 0; i < m_Bitmaps.size(); i++)
        {
            if (PtInRect(&m_Bitmaps[i].drawRect, mousePos))
            {
                m_Seleted = i;
                break;
            }
        }
    }
}

LRESULT Demo5_1::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    std::shared_ptr<Demo5_1> pDemo = CUR_DEMO(Demo5_1);

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
