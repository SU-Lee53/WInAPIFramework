#include "../pch.h"
#include "Demo4_3.h"
#include "../TextBox.h"
#include "../Utils.h"
#include "../Caret.h"
#include "../GameBoard.h"

using namespace std;
using namespace shapes;

BOOL Demo4_3::Initialize()
{
    m_pProcFunction = WndProc;

    m_AppDesc.wndName = L"Demo4-3";
    m_AppDesc.wndStyle = WS_OVERLAPPEDWINDOW;
    m_AppDesc.backgroundColor = WHITE_BRUSH;
    m_AppDesc.wndIcon = IDI_APPLICATION;
    m_AppDesc.wndCursor = IDC_ARROW;
    m_AppDesc.wndPosition.x = 300;
    m_AppDesc.wndPosition.y = 100;
    m_AppDesc.wndSize.width = 1200;
    m_AppDesc.wndSize.height = 800;
	m_AppDesc.appRunMode = APP_RUN_MODE_GAME_LOOP;

    // 메뉴 설정
    m_AppDesc.menuName = IDR_MENU_4_3;

    return 0;
}

void Demo4_3::OnCreate(HWND hWnd)
{
    BOOL bResult = TRUE;
    TIMER.Initialize(hWnd);

    ResetGame();

    if (!bResult) __debugbreak();
}

void Demo4_3::HandleMenu(WORD param)
{
    switch (param)
    {
    case ID_MOVE_CW:    // 메뉴 잘못만듬 -> 메인원의 자전 변경으로
        for (auto& p : m_pCircles)
        {
            auto curState = p->GetState();
            if (curState == MAIN_CIRCLE_STATE_CW)
            {
                p->SetState(MAIN_CIRCLE_STATE_CCW);
            }
            else if (curState == MAIN_CIRCLE_STATE_CCW)
            {
                p->SetState(MAIN_CIRCLE_STATE_CW);
            }
        }
        break;

    case ID_MOVE_CCW:   // 메뉴 잘못만듬 -> 위성원의 자전 변경으로
        for (auto& p : m_pCircles)
        {
            auto curState = p->GetSateliteState();
            if (curState == MINI_CIRCLE_STATE_CW)
            {
                p->SetSateliteState(MINI_CIRCLE_STATE_CCW);
            }
            else if (curState == MINI_CIRCLE_STATE_CCW)
            {
                p->SetSateliteState(MINI_CIRCLE_STATE_CW);
            }
        }
        break;

    case ID_MOVE_STOP:
        for (auto& p : m_pCircles)
        {
            p->SetState(MAIN_CIRCLE_STATE_STOP);
            p->SetSateliteState(MINI_CIRCLE_STATE_STOP);
        }

        break;

    case ID_CHANGE_REVERSE:
        {
            int randomCount = RANDOM.GenerateRandom(1, (int)m_pCircles.size());
            for (int i = 0; i < randomCount; i++)
            {
                int randomIndex = RANDOM.GenerateRandom(0, (int)m_pCircles.size() - 1);
                COLORREF origin = m_pCircles[randomIndex]->GetBackgroundColor();
                m_pCircles[randomIndex]->SetBackgroundColor(Utils::InvertColor(origin));
            }
        }
        break;

    case ID_CHANGE_RED:
        for (auto& p : m_pCircles)
        {
            p->SetBackgroundColor(RGB(255, 0, 0));
        }
        break;

    case ID_CHANGE_GREEN:
        for (auto& p : m_pCircles)
        {
            p->SetBackgroundColor(RGB(0, 255, 0));
        }
        break;

    case ID_CHANGE_BLUE:
        for (auto& p : m_pCircles)
        {
            p->SetBackgroundColor(RGB(0, 0, 255));
        }
        break;

    case ID_CHANGE_RANDOM:
        for (auto& p : m_pCircles)
        {
            p->SetBackgroundColor(RANDOM.GenerateRandomColor());
        }
        break;

    case ID_GAME_RESET40037:
        ResetGame();
        break;

    case ID_GAME_QUIT:
        PostQuitMessage(0);
        break;

    }


}

void Demo4_3::Update()
{
    ProcessKeyboard();
    ProcessMouse();

    for (auto& p : m_pCircles)
    {
        p->Update();
    }

}

void Demo4_3::Draw(HDC hDC)
{
    for (auto& p : m_pCircles)
    {
        p->Draw(hDC);
    }

    // Debug
    DrawCoord(hDC);
}

void Demo4_3::ProcessKeyboard()
{
}

void Demo4_3::ProcessMouse()
{
    if (INPUT.GetButtonDown(KEY_TYPE::LBUTTON))
    {
        POINT curMousePos = INPUT.GetMousePos();

        BOOL bIsInCircle = FALSE;
        for (auto& p : m_pCircles)
        {
            if (p->CheckCollision(curMousePos))
            {
                p->HandleCollision("Mouse");
                bIsInCircle = TRUE;
                break;
            }
        }

        if (!bIsInCircle)
        {
            if (m_pCircles.size() < MAX_CIRCLE_COUNT)
            {
                auto p = make_shared<MainCircle4_3>();
                p->Create();
                p->SetPosition(curMousePos);
                m_pCircles.push_back(p);
            }
        }

    }
}

void Demo4_3::ResetGame()
{
    m_pCircles.clear();

    for (int i = 0; i < 10; i++)
    {
        auto p = make_shared<MainCircle4_3>();
        p->Create();
        m_pCircles.push_back(p);
    }

}

LRESULT Demo4_3::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    std::shared_ptr<Demo4_3> pDemo = CUR_DEMO(Demo4_3);

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

// MiniCircle
///////////////////////////////////////////////////////////////////////

BOOL MiniCircle4_3::Create(std::shared_ptr<GameObject> main)
{
    m_wpMainCircle = static_pointer_cast<MainCircle4_3>(main);

    auto p = make_shared<shapes::Ellipse>();
    p->Create(C_RECT(-1, -1, 1, 1));
    m_pModel = p;

    POINT mainScale = m_wpMainCircle.lock()->GetScale();
    m_Scale = POINT{ mainScale.x / 3, mainScale.y / 3 };
    m_BkColor = m_wpMainCircle.lock()->GetBackgroundColor();

    // Position 은 Update 에서

    return TRUE;
}

void MiniCircle4_3::Update()
{
    POINT offset = m_Scale;
    weak_ptr<shapes::Ellipse> wpMainModel = static_pointer_cast<shapes::Ellipse>(m_wpMainCircle.lock()->GetModel());
    wpMainModel.lock()->AddScale(POINT{ offset.x, offset.y });
    POINT pos = wpMainModel.lock()->DegreeToPoint(m_degree);
    wpMainModel.lock()->AddScale(POINT{ -offset.x, -offset.y });

    if (m_curState == MINI_CIRCLE_STATE_CCW)
    {
        m_degree += 0.1f;
    }
    else if(m_curState == MINI_CIRCLE_STATE_CW)
    {
        m_degree -= 0.1f;
    }

    m_Position = POINT{ pos.x, pos.y };

}

void MiniCircle4_3::Draw(HDC hDC)
{
    m_pModel->SetOffset(m_Position);
    m_pModel->SetScale(m_Scale);
    m_pModel->SetBackgroundColor(m_BkColor);
    m_pModel->DrawInWindowCoord(hDC);

}

void MiniCircle4_3::HandleCollision(const std::string& otherName)
{
}

// MainCircle
///////////////////////////////////////////////////////////////////////

BOOL MainCircle4_3::Create()
{
    auto p = make_shared<shapes::Ellipse>();
    p->Create(C_RECT(-1, -1, 1, 1));
    m_pModel = p;

    int scale = RANDOM.GenerateRandom(Demo4_3::MIN_CIRCLE_SIZE, Demo4_3::MAX_CIRCLE_SIZE);

    m_Position.x = RANDOM.GenerateRandom(100, 1100);
    m_Position.y = RANDOM.GenerateRandom(100, 700);
    m_Scale = POINT{ scale, scale };
    m_BkColor = RANDOM.GenerateRandomColor();

    m_pSatellite = make_unique<MiniCircle4_3>();
    m_pSatellite->Create(shared_from_this());

    m_degree = RANDOM.GenerateRandom(0.f, 360.f);

    return TRUE;
}

void MainCircle4_3::Update()
{
    if (m_curState == MAIN_CIRCLE_STATE_CCW)
    {
        m_degree += 0.05f;
    }
    else if (m_curState == MAIN_CIRCLE_STATE_CW)
    {
        m_degree -= 0.05f;
    }

    m_pSatellite->Update();
}

void MainCircle4_3::Draw(HDC hDC)
{
    m_pModel->SetOffset(m_Position);
    m_pModel->SetScale(m_Scale);
    m_pModel->SetBackgroundColor(m_BkColor);
    m_pModel->DrawInWindowCoord(hDC);

    // 내부 바퀴모양 직선도 그려야 

    shapes::Ellipse& refCircle = *static_pointer_cast<shapes::Ellipse>(m_pModel);

    for (int i = 0; i < 4; i++)
    {
        float degree = ((180 / 4) * i) + m_degree;
        POINT beginPoint = refCircle.DegreeToPoint(degree);
        POINT endPoint = refCircle.DegreeToPoint(degree + 180);

        shapes::Line::DrawLine(hDC, beginPoint, endPoint);
    }

    m_pSatellite->Draw(hDC);

}

void MainCircle4_3::HandleCollision(const std::string& otherName)
{
    if (otherName == "Mouse")
    {
        MINI_CIRCLE_STATE curState = m_pSatellite->GetState();
        if (curState == MINI_CIRCLE_STATE_CW)
        {
            m_pSatellite->SetState(MINI_CIRCLE_STATE_CCW);
        }
        else if (curState == MINI_CIRCLE_STATE_CCW)
        {
            m_pSatellite->SetState(MINI_CIRCLE_STATE_CW);
        }
    }
}

BOOL MainCircle4_3::CheckCollision(POINT pos)
{
    shapes::Ellipse& refCircle = *static_pointer_cast<shapes::Ellipse>(m_pModel);

    return refCircle.IsInRect(pos);
}
