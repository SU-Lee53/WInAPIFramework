#include "../pch.h"
#include "Demo2_10.h"
#include "../TextBox.h"
#include "../Utils.h"
#include "../Caret.h"

using namespace std;
using namespace shapes;

BOOL Demo2_10::Initialize()
{
    m_pProcFunction = WndProc;

    m_AppDesc.wndName = L"Demo2-10";
    m_AppDesc.wndStyle = WS_OVERLAPPEDWINDOW;
    m_AppDesc.backgroundColor = WHITE_BRUSH;
    m_AppDesc.wndIcon = IDI_APPLICATION;
    m_AppDesc.wndCursor = IDC_ARROW;
    m_AppDesc.wndPosition.x = 100;
    m_AppDesc.wndPosition.y = 50;
    m_AppDesc.wndSize.width = 1200;
    m_AppDesc.wndSize.height = 1200;

    return 0;
}

void Demo2_10::OnCreate(HWND hWnd)
{
    BOOL bResult = TRUE;

    m_pBoardRect = make_shared<shapes::Rectangle>();
    m_pBoardRect->Create(WndSize{ 26, 26 });

    if (!m_pPlayer1) m_pPlayer1 = make_shared<Demo2_10_Player>();
    if (!m_pPlayer2) m_pPlayer2 = make_shared<Demo2_10_Player>();

    m_pPlayer1->Create(shared_from_this());
    m_pPlayer2->Create(shared_from_this());

    SetGame();
    CreatePlayerModel();

    if (!bResult) __debugbreak();
}

void Demo2_10::OnPaint()
{
    HDC hDC = BeginAppPaint();
    if (!hDC)
        __debugbreak();

    ProcessGameStatus();

    for (int i = 0; i < 40; i++)
    {
        m_pBoardRect->SetOffset({ -500, (-500 + (26 * i)) });
        for (int j = 0; j < 40; j++)
        {
            if (m_pCellInfo[j][i] == CELL_TYPE_CHANGE_COLOR)
            {
                m_pBoardRect->SetBackgroundColor(RGB(0, 0, 255));
                m_pBoardRect->Draw(hDC);
            }
            else if (m_pCellInfo[j][i] == CELL_TYPE_OBSTACLE)
            {
                m_pBoardRect->SetBackgroundColor(RGB(255, 0, 0));
                m_pBoardRect->Draw(hDC);
            }
            else if (m_pCellInfo[j][i] == CELL_TYPE_CHANGE_SIZE)
            {
                m_pBoardRect->SetBackgroundColor(RGB(255, 255, 0));
                m_pBoardRect->Draw(hDC);
            }
            else if (m_pCellInfo[j][i] == CELL_TYPE_CHANGE_MODEL)
            {
                m_pBoardRect->SetBackgroundColor(RGB(122, 255, 0));
                m_pBoardRect->Draw(hDC);
            }
            else
            {
                m_pBoardRect->SetBackgroundColor(RGB(255, 255, 255));
                m_pBoardRect->Draw(hDC);
            }
            m_pBoardRect->AddOffset({ 26,0 });
        }
    }

    m_pPlayer1->Draw(hDC);
    m_pPlayer2->Draw(hDC);

    TextBox::DrawFormattedString(hDC, { 10, 10 }, m_wstrErrString.c_str());
    m_wstrErrString.clear();

    if (!EndAppPaint())
        __debugbreak;
}

void Demo2_10::OnChar(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    switch (wParam)
    {

    default:
        ProcessKeyboard(wParam);
        break;

    }


    ::InvalidateRect(CUR_HWND, NULL, TRUE);
}

void Demo2_10::ProcessKeyboard(WPARAM wParam)
{
    if (wParam == L'r' || wParam == L'R')
    {
        SetGame();
    }
    if (wParam == L'q' || wParam == L'Q')
    {
        DestroyWindow(CUR_HWND);
    }

    BOOL WhosKeyPressed;
    if (!CheckWhosKeyDowned(wParam, WhosKeyPressed))
    {
        return;
    }

    // Player1 : WASD
    if (m_bPlayerTurn)
    {
        if (WhosKeyPressed == FALSE)
        {
            m_wstrErrString = L"PLAYER2 : NOT YOUR TURN!!";
            return;
        }

        if (wParam == L'w' || wParam == L'W')
        {
            m_pPlayer1->MoveUp();
        }
        else if (wParam == L'a' || wParam == L'A')
        {
            m_pPlayer1->MoveLeft();
        }
        else if (wParam == L's' || wParam == L'S')
        {
            m_pPlayer1->MoveDown();
        }
        else if (wParam == L'd' || wParam == L'D')
        {
            m_pPlayer1->MoveRight();
        }

        m_bPlayerTurn = !m_bPlayerTurn;
    }
    else
    {
        if (WhosKeyPressed == TRUE)
        {
            m_wstrErrString = L"PLAYER1 : NOT YOUR TURN!!";
            return;
        }

        // Player2 : 8456
        if (wParam == L'8')
        {
            m_pPlayer2->MoveUp();
        }
        else if (wParam == L'4')
        {
            m_pPlayer2->MoveLeft();
        }
        else if (wParam == L'5')
        {
            m_pPlayer2->MoveDown();
        }
        else if (wParam == L'6')
        {
            m_pPlayer2->MoveRight();
        }

        m_bPlayerTurn = !m_bPlayerTurn;
    }

}

void Demo2_10::OnKeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    switch (wParam)
    {

    default:
        break;
    }

    ::InvalidateRect(CUR_HWND, NULL, TRUE);
}

void Demo2_10::SetGame()
{
    // Set CELL_TYPE_NONE to m_pCellInfo
    for (int i = 0; i < 40; i++)
    {
        for (int j = 0; j < 40; j++)
        {
            m_pCellInfo[i][j] = CELL_TYPE_NONE;
        }
    }

    // Generate Object pos
    int nObjCount = RANDOM.GenerateRandom(20, 100);
    for (int i = 0; i < nObjCount; i++)
    {
        // Random Select Obj type 
        DEMO2_10_CELL_TYPE cellType = (DEMO2_10_CELL_TYPE)RANDOM.GenerateRandom(0, 3);
        POINT targetPos = RANDOM.GenerateRandomPoint(0, 40);

        while (m_pCellInfo[targetPos.x][targetPos.y] != CELL_TYPE_NONE)
        {
            targetPos = RANDOM.GenerateRandomPoint(0, 40);
        }

        m_pCellInfo[targetPos.x][targetPos.y] = cellType;

    }

    // Create Player
    m_pPlayer1->SetPos({0, 0});
    m_pPlayer1->SetColor(RANDOM.GenerateRandomColor());
    m_pPlayer1->SetPlayerModel(RANDOM.GenerateRandom(0, 3));
    
    m_pPlayer2->SetPos({39, 39});
    m_pPlayer2->SetColor(RANDOM.GenerateRandomColor());
    m_pPlayer2->SetPlayerModel(RANDOM.GenerateRandom(0, 3));

}

void Demo2_10::CreatePlayerModel()
{
    m_pPlayerModel0 = make_shared<shapes::Polygon>();
    std::vector<POINT> triPoints = { {0, -1}, {-1, 1}, {1, 1} };
    m_pPlayerModel0->Create(triPoints);

    m_pPlayerModel1 = make_shared<shapes::Polygon>();
    std::vector<POINT> hgPoints = { {-1, 1}, {1, 1}, {-1, -1}, {1, -1} };
    m_pPlayerModel1->Create(hgPoints);

    m_pPlayerModel2 = make_shared<shapes::Ellipse>();
    m_pPlayerModel2->Create(WndSize{2, 2});

    m_pPlayerModel3 = make_shared<shapes::Ellipse>();
    m_pPlayerModel3->Create(WndSize{ 2, 2 });

}

void Demo2_10::ProcessGameStatus()
{
    POINT p1Pos = m_pPlayer1->GetPos();

    if (m_pCellInfo[p1Pos.x][p1Pos.y] == CELL_TYPE_CHANGE_COLOR)
    {
        m_pPlayer1->SetColor(RANDOM.GenerateRandomColor());
    }
    else if (m_pCellInfo[p1Pos.x][p1Pos.y] == CELL_TYPE_CHANGE_SIZE)
    {
        m_pPlayer1->UpdateScale();
    }
    else if (m_pCellInfo[p1Pos.x][p1Pos.y] == CELL_TYPE_CHANGE_MODEL)
    {
        m_pPlayer1->SetPlayerModel(RANDOM.GenerateRandom(0, 3));
    }
    
    POINT p2Pos = m_pPlayer2->GetPos();

    if (m_pCellInfo[p2Pos.x][p2Pos.y] == CELL_TYPE_CHANGE_COLOR)
    {
        m_pPlayer2->SetColor(RANDOM.GenerateRandomColor());
    }
    else if (m_pCellInfo[p2Pos.x][p2Pos.y] == CELL_TYPE_CHANGE_SIZE)
    {
        m_pPlayer2->UpdateScale();
    }
    else if (m_pCellInfo[p2Pos.x][p2Pos.y] == CELL_TYPE_CHANGE_MODEL)
    {
        m_pPlayer2->SetPlayerModel(RANDOM.GenerateRandom(0, 3));
    }


}

BOOL Demo2_10::CheckWhosKeyDowned(WPARAM wParam, BOOL& who)
{
    std::wstring p1Key = L"WwAaSsDd";
    std::wstring p2Key = L"8456";

    size_t p1Founded = p1Key.find(wParam, 0);
    size_t p2Founded = p2Key.find(wParam, 0);

    if (p1Founded != wstring::npos)
    {
        who = TRUE;
        return TRUE;
    }
    else if (p2Founded != wstring::npos)
    {
        who = FALSE;
        return TRUE;
    }
    else
    {
        return FALSE;
    }


}

LRESULT Demo2_10::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    std::shared_ptr<Demo2_10> pDemo = CUR_DEMO(Demo2_10);

    switch (message)
    {
    case WM_CREATE:
        pDemo->OnCreate(hWnd);
        break;

    case WM_PAINT:
        pDemo->OnPaint();
        break;

    case WM_KEYDOWN:
        pDemo->OnKeyDown(hWnd, wParam, lParam);
        break;
        
    case WM_CHAR:
        pDemo->OnChar(hWnd, wParam, lParam);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    default:
        break;
    }
    
    return DefWindowProc(hWnd, message, wParam, lParam);
}


////////////
// Player //
////////////

void Demo2_10_Player::Draw(HDC hDC)
{
    if (m_PlayerModel == 0)
    {
        auto& model = *static_pointer_cast<Demo2_10>(m_wpDemo.lock())->GetPlayerModel0();
        model.SetOffset(CalculatePlayerPos());
        model.SetBackgroundColor(m_Color);
        model.SetScale(m_Scale);
        model.Draw(hDC);
    }
    else if (m_PlayerModel == 1)
    {
        auto& model = *static_pointer_cast<Demo2_10>(m_wpDemo.lock())->GetPlayerModel1();
        model.SetOffset(CalculatePlayerPos());
        model.SetBackgroundColor(m_Color);
        model.SetScale(m_Scale);
        model.Draw(hDC);
    }
    else if (m_PlayerModel == 2)
    {
        auto& model = *static_pointer_cast<Demo2_10>(m_wpDemo.lock())->GetPlayerModel2();
        model.SetOffset(CalculatePlayerPos());
        model.SetBackgroundColor(m_Color);
        model.SetScale(m_Scale);
        model.DrawPie(hDC, 15, -15);
    }
    else if (m_PlayerModel == 3)
    {
        auto& model = *static_pointer_cast<Demo2_10>(m_wpDemo.lock())->GetPlayerModel3();
        model.SetOffset(CalculatePlayerPos());
        model.SetBackgroundColor(m_Color);
        model.SetScale(m_Scale);
        model.Draw(hDC);
    }
}

void Demo2_10_Player::MoveUp()
{
    POINT origin = m_Pos;
    m_Pos.y--;
    if (m_Pos.y < 0) m_Pos.y = 39;
    if (static_pointer_cast<Demo2_10>(m_wpDemo.lock())->GetCellInfo(m_Pos.x, m_Pos.y) == CELL_TYPE_OBSTACLE)
    {
        m_Pos = origin;
    }
}

void Demo2_10_Player::MoveDown()
{
    POINT origin = m_Pos;
    m_Pos.y++;
    if (m_Pos.y >= 40) m_Pos.y = 0;
    if (static_pointer_cast<Demo2_10>(m_wpDemo.lock())->GetCellInfo(m_Pos.x, m_Pos.y) == CELL_TYPE_OBSTACLE)
    {
        m_Pos = origin;
    }
}

void Demo2_10_Player::MoveLeft()
{
    POINT origin = m_Pos;
    m_Pos.x--;
    if (m_Pos.x < 0) m_Pos.x = 39;
    if (static_pointer_cast<Demo2_10>(m_wpDemo.lock())->GetCellInfo(m_Pos.x, m_Pos.y) == CELL_TYPE_OBSTACLE)
    {
        m_Pos = origin;
    }
}

void Demo2_10_Player::MoveRight()
{
    POINT origin = m_Pos;
    m_Pos.x++;
    if (m_Pos.x >= 40) m_Pos.x = 0;
    if (static_pointer_cast<Demo2_10>(m_wpDemo.lock())->GetCellInfo(m_Pos.x, m_Pos.y) == CELL_TYPE_OBSTACLE)
    {
        m_Pos = origin;
    }
}
