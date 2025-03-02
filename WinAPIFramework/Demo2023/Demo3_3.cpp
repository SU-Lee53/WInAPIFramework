#include "../pch.h"
#include "Demo3_3.h"
#include "../TextBox.h"
#include "../Utils.h"
#include "../Caret.h"
#include "../GameBoard.h"

using namespace std;
using namespace shapes;

BOOL Demo3_3::Initialize()
{
    m_pProcFunction = WndProc;

    m_AppDesc.wndName = L"Demo2-13";
    m_AppDesc.wndStyle = WS_OVERLAPPEDWINDOW;
    m_AppDesc.backgroundColor = WHITE_BRUSH;
    m_AppDesc.wndIcon = IDI_APPLICATION;
    m_AppDesc.wndCursor = IDC_ARROW;
    m_AppDesc.wndPosition.x = 100;
    m_AppDesc.wndPosition.y = 10;
    m_AppDesc.wndSize.width = 1200;
    m_AppDesc.wndSize.height = 800;
	m_AppDesc.appRunMode = APP_RUN_MODE_GAME_LOOP;

    return 0;
}

void Demo3_3::OnCreate(HWND hWnd)
{
    BOOL bResult = TRUE;
    TIMER.Initialize(hWnd);

    m_pTrafficLight = make_shared<TrafficLight3_3>();
    m_pTrafficLight->Create();

    CreateCars();

    if (!bResult) __debugbreak();
}

void Demo3_3::Update()
{
    ProcessKeyboard();

    for (const auto& car : m_pCars)
    {
        car->Update();
    }

    m_pTrafficLight->Update();
}

void Demo3_3::Draw(HDC hDC)
{
    DrawCrossRoad(hDC);
    m_pTrafficLight->Draw(hDC);

    for (const auto& car : m_pCars)
    {
        car->Draw(hDC);
    }

    // Debug
    std::wstring lightMode = m_pTrafficLight->GetChangeMode() ? L"Change When Click" : L"Change Every 3sec";
    TextBox::DrawFormattedString(hDC, { 900,100 }, lightMode.c_str());

    DrawCoord(hDC);
}

void Demo3_3::ProcessKeyboard()
{
    if (INPUT.GetButtonDown(KEY_TYPE::PLUS))
    {
        for (auto& car : m_pCars)
        {
            car->AddSpeed(1);
        }
    }
    
    if (INPUT.GetButtonDown(KEY_TYPE::MINUS))
    {
        for (auto& car : m_pCars)
        {
            car->AddSpeed(-1);
        }
    }

    if (INPUT.GetButtonDown(KEY_TYPE::A))
    {
        m_pTrafficLight->ChangeMode();
        if (m_pTrafficLight->GetChangeMode() == FALSE)  // 만약 시간에따라 바뀌는 모드로 설정했다면
        {
            m_pTrafficLight->SetPrevTick(GetTickCount64());
        }
    }

    if (INPUT.GetButtonDown(KEY_TYPE::Q))
    {
        DestroyWindow(CUR_HWND);
    }
}

void Demo3_3::ProcessMouse()
{
}

void Demo3_3::CreateCars()
{
    COLORREF carColor = RANDOM.GenerateRandomColor();

    // Up 방향 2대
    auto pCarUp1 = make_shared<Car3_3>();
    pCarUp1->Create();
    pCarUp1->SetMoveType(CAR_MOVE_UP);
    pCarUp1->SetPosition({ 650, 100 });
    pCarUp1->SetScale({ 30, 60 });
    pCarUp1->SetBackgroundColor(carColor);
    pCarUp1->SetFrameWidth(3);
    m_pCars.push_back(pCarUp1);
    
    auto pCarUp2 = make_shared<Car3_3>();
    pCarUp2->Create();
    pCarUp2->SetMoveType(CAR_MOVE_UP);
    pCarUp2->SetPosition({ 650, 600 });
    pCarUp2->SetScale({ 30, 60 });
    pCarUp2->SetBackgroundColor(carColor);
    pCarUp2->SetFrameWidth(3);
    m_pCars.push_back(pCarUp2);
    
    // Down 방향 2대
    auto pCarDown1 = make_shared<Car3_3>();
    pCarDown1->Create();
    pCarDown1->SetMoveType(CAR_MOVE_DOWN);
    pCarDown1->SetPosition({ 550, 100 });
    pCarDown1->SetScale({ 30, 60 });
    pCarDown1->SetBackgroundColor(carColor);
    pCarDown1->SetFrameWidth(3);
    m_pCars.push_back(pCarDown1);
    
    auto pCarDown2 = make_shared<Car3_3>();
    pCarDown2->Create();
    pCarDown2->SetMoveType(CAR_MOVE_DOWN);
    pCarDown2->SetPosition({ 550, 600 });
    pCarDown2->SetScale({ 30, 60 });
    pCarDown2->SetBackgroundColor(carColor);
    pCarDown2->SetFrameWidth(3);
    m_pCars.push_back(pCarDown2);
    
    // Left 방향 2대
    auto pCarLeft1 = make_shared<Car3_3>();
    pCarLeft1->Create();
    pCarLeft1->SetMoveType(CAR_MOVE_LEFT);
    pCarLeft1->SetPosition({ 100, 350 });
    pCarLeft1->SetScale({ 60, 30 });
    pCarLeft1->SetBackgroundColor(carColor);
    pCarLeft1->SetFrameWidth(3);
    m_pCars.push_back(pCarLeft1);
    
    auto pCarLeft2 = make_shared<Car3_3>();
    pCarLeft2->Create();
    pCarLeft2->SetMoveType(CAR_MOVE_LEFT);
    pCarLeft2->SetPosition({ 800, 350 });
    pCarLeft2->SetScale({ 60, 30 });
    pCarLeft2->SetBackgroundColor(carColor);
    pCarLeft2->SetFrameWidth(3);
    m_pCars.push_back(pCarLeft2);
    
    // Right 방향 2대
    auto pCarRight1 = make_shared<Car3_3>();
    pCarRight1->Create();
    pCarRight1->SetMoveType(CAR_MOVE_RIGHT);
    pCarRight1->SetPosition({ 100, 450 });
    pCarRight1->SetScale({ 60, 30 });
    pCarRight1->SetBackgroundColor(carColor);
    pCarRight1->SetFrameWidth(3);
    m_pCars.push_back(pCarRight1);
    
    auto pCarRight2 = make_shared<Car3_3>();
    pCarRight2->Create();
    pCarRight2->SetMoveType(CAR_MOVE_RIGHT);
    pCarRight2->SetPosition({ 800, 450 });
    pCarRight2->SetScale({ 60, 30 });
    pCarRight2->SetBackgroundColor(carColor);
    pCarRight2->SetFrameWidth(3);
    m_pCars.push_back(pCarRight2);

}

void Demo3_3::DrawCrossRoad(HDC hDC)
{
    shapes::Rectangle::DrawRectangle(hDC, C_RECT(0, 0, 500, 300), RGB(255, 255, 255), PS_SOLID, 2, RGB(0,0,0));
    shapes::Rectangle::DrawRectangle(hDC, C_RECT(700, 0, 1200, 300), RGB(255, 255, 255), PS_SOLID, 2, RGB(0,0,0));

    shapes::Rectangle::DrawRectangle(hDC, C_RECT(0, 500, 500, 800), RGB(255, 255, 255), PS_SOLID, 2, RGB(0,0,0));
    shapes::Rectangle::DrawRectangle(hDC, C_RECT(700, 500, 1200, 800), RGB(255, 255, 255), PS_SOLID, 2, RGB(0,0,0));

    shapes::Rectangle::DrawRectangle(hDC, C_RECT(500, 300, 700, 500), RGB(255, 255, 255), PS_DOT, 1, RGB(0, 0, 0));

    shapes::Line::DrawLine(hDC, POINT{ 600, 0 }, POINT{ 600, 800 }, PS_SOLID, 2, RGB(0, 255, 255));
    shapes::Line::DrawLine(hDC, POINT{ 0, 400 }, POINT{ 1200, 400 }, PS_SOLID, 2, RGB(0, 255, 255));
}

LRESULT Demo3_3::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    std::shared_ptr<Demo3_3> pDemo = CUR_DEMO(Demo3_3);

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

// TrafficLight
/////////////////////////////////////////////////////////////////////////

BOOL TrafficLight3_3::Create()
{
    m_pLightFrame = make_shared<shapes::Rectangle>();
    m_pRedLight = make_shared<shapes::Ellipse>();
    m_pYellowLight = make_shared<shapes::Ellipse>();
    m_pBlueLight = make_shared<shapes::Ellipse>();

    POINT frameOffset = POINT{ 900, 30 };
    m_pLightFrame->Create(C_RECT(0, 0, 210, 70));
    m_pLightFrame->SetOffset(frameOffset);

    m_pRedLight->Create(C_RECT(0, 0, 50, 50));
    m_pRedLight->SetOffset(frameOffset);
    m_pRedLight->AddOffset(POINT(10, 10));
    m_pRedLight->SetBackgroundColor(RGB(255, 0, 0));

    m_pYellowLight->Create(C_RECT(0, 0, 50, 50));
    m_pYellowLight->SetOffset(frameOffset);
    m_pYellowLight->AddOffset(POINT(80, 10));
    m_pYellowLight->SetBackgroundColor(RGB(255, 255, 0));

    m_pBlueLight->Create(C_RECT(0, 0, 50, 50));
    m_pBlueLight->SetOffset(frameOffset);
    m_pBlueLight->AddOffset(POINT(150, 10));
    m_pBlueLight->SetBackgroundColor(RGB(0, 0, 255));

    return TRUE;
}

void TrafficLight3_3::Update()
{
    if (m_bChangeWhenClicked)
    {
        if (INPUT.GetButtonDown(KEY_TYPE::LBUTTON))
        {
            POINT mousePos = INPUT.GetMousePos();

            if (m_pRedLight->IsInRect(mousePos))
            {
                m_State = TRAFFIC_LIGHT_STATE_RED;
            }
            
            if (m_pYellowLight->IsInRect(mousePos))
            {
                if (m_State != TRAFFIC_LIGHT_STATE_CHANGE_AFTER_SECOND)
                {
                    TRAFFIC_LIGHT_STATE beforeState = m_State;
                    m_State = TRAFFIC_LIGHT_STATE_CHANGE_AFTER_SECOND;
                    m_TargetState = beforeState == TRAFFIC_LIGHT_STATE_BLUE ? TRAFFIC_LIGHT_STATE_RED : TRAFFIC_LIGHT_STATE_BLUE;

                    m_ullYellowLightSettedTick = GetTickCount64();
                }
            }
            
            if (m_pBlueLight->IsInRect(mousePos))
            {
                m_State = TRAFFIC_LIGHT_STATE_BLUE;
            }

        }
    }
    else
    {
        ULONGLONG curTick = GetTickCount64();

        if (curTick - m_ullPrevChangedTick > 3000)
        {
            int curState = (int)(m_State);
            m_State = (TRAFFIC_LIGHT_STATE)(++curState % 3);

            m_ullPrevChangedTick = curTick;
        }
    }

    if (m_State == TRAFFIC_LIGHT_STATE_CHANGE_AFTER_SECOND)
    {
        ULONGLONG curTick = GetTickCount64();

        if (curTick - m_ullYellowLightSettedTick > 1000)
        {
            m_State = m_TargetState;
        }
    }

}

void TrafficLight3_3::Draw(HDC hDC)
{
    m_pLightFrame->DrawInWindowCoord(hDC);

    if (m_State == TRAFFIC_LIGHT_STATE_RED)
    {
        m_pRedLight->SetFrameWidth(5);
        m_pRedLight->DrawInWindowCoord(hDC);
        m_pRedLight->SetFrameWidth(1);
    }
    else
    {
        m_pRedLight->DrawInWindowCoord(hDC);
    }
    
    if (m_State == TRAFFIC_LIGHT_STATE_YELLOW || m_State == TRAFFIC_LIGHT_STATE_CHANGE_AFTER_SECOND)
    {
        m_pYellowLight->SetFrameWidth(5);
        m_pYellowLight->DrawInWindowCoord(hDC);
        m_pYellowLight->SetFrameWidth(1);
    }
    else
    {
        m_pYellowLight->DrawInWindowCoord(hDC);
    }
    
    if (m_State == TRAFFIC_LIGHT_STATE_BLUE)
    {
        m_pBlueLight->SetFrameWidth(5);
        m_pBlueLight->DrawInWindowCoord(hDC);
        m_pBlueLight->SetFrameWidth(1);
    }
    else
    {
        m_pBlueLight->DrawInWindowCoord(hDC);
    }

}

// Car
/////////////////////////////////////////////////////////////////////////

BOOL Car3_3::Create()
{
    auto p = make_shared<shapes::Rectangle>();
    p->Create(C_RECT(-1, -1, 1, 1));
    m_pModel = p;

    return TRUE;
}

void Car3_3::Update()
{
    UpdateObjectStateToModel();

    POINT pos = m_Position;

    WndSize windowSize = CUR_DEMO(Demo3_3)->GetAppDesc().wndSize;
    RECT carRect = static_pointer_cast<shapes::Rectangle>(m_pModel)->GetRect();

    TRAFFIC_LIGHT_STATE lightState = CUR_DEMO(Demo3_3)->GetTrafficLight()->GetState();

    if (m_MoveType == CAR_MOVE_UP)
    {
        if (lightState == TRAFFIC_LIGHT_STATE_BLUE)
        {
            pos.y -= m_CarSpeed;
            if (carRect.top < 0)    // 위쪽이 먼저 나가기 시작
            {
                m_bIsOut = TRUE;
            }
            if (carRect.bottom < 0) // 아랫쪽까지 완전히 나감
            {
                pos.y = windowSize.height - m_Scale.y;
                m_bIsOut = FALSE;
            }
        }
    }
    else if (m_MoveType == CAR_MOVE_DOWN)
    {
        if (lightState == TRAFFIC_LIGHT_STATE_BLUE)
        {
            pos.y += m_CarSpeed;
            if (carRect.bottom > windowSize.height)
            {
                m_bIsOut = TRUE;
            }
            if (carRect.top > windowSize.height)
            {
                pos.y = m_Scale.y;
                m_bIsOut = FALSE;
            }
        }
    }
    else if (m_MoveType == CAR_MOVE_LEFT)
    {
        if (lightState == TRAFFIC_LIGHT_STATE_RED)
        {
            pos.x -= m_CarSpeed;
            if (carRect.left < 0)
            {
                m_bIsOut = TRUE;
            }
            if (carRect.right < 0)
            {
                pos.x = windowSize.width - m_Scale.x;
                m_bIsOut = FALSE;
            }
        }
    }
    else if (m_MoveType == CAR_MOVE_RIGHT)
    {
        if (lightState == TRAFFIC_LIGHT_STATE_RED)
        {
            pos.x += m_CarSpeed;
            if (carRect.right > windowSize.width)
            {
                m_bIsOut = TRUE;
            }
            if (carRect.left > windowSize.width)
            {
                pos.x = m_Scale.x;
                m_bIsOut = FALSE;
            }
        }
    }


    m_Position = pos;
}

void Car3_3::Draw(HDC hDC)
{
    m_pModel->DrawInWindowCoord(hDC);

    // 나간 일부를 그리려면 사각형을 2개로 쪼개야 함
    // 아직 있는부분을 RECT1 나간부분을 RECT2 로 나누고 반대쪽도 그려주어야 함
    // 아니 쪼개지말고 아래부터 하나 더그리면 되잖아?

    if (m_bIsOut)
    {
        // Q. 여기서 뭘하나요?
        // A. 나간만큼을 구해서 한번 더그림ㅇㅇ

        RECT outRect;
        WndSize windowSize = CUR_DEMO(Demo3_3)->GetAppDesc().wndSize;
        RECT carRect = static_pointer_cast<shapes::Rectangle>(m_pModel)->GetRect();

        if (m_MoveType == CAR_MOVE_UP)
        {
            // 나간만큼의 RECT 의 Height를 우선 구함
            int outHeight = 0 - carRect.top;    // 나갔다면 top 이 음수 -> 0 에서 빼면 heght

            // 아래부터 나타날 outRect 만듬
            outRect = C_RECT(carRect.left, (windowSize.height - outHeight), carRect.right, windowSize.height);

            // 그림
            shapes::Rectangle::DrawRectangle(hDC, outRect, m_BkColor, PS_SOLID, m_FrameWidth, m_FrameColor);
        }
        else if (m_MoveType == CAR_MOVE_DOWN)
        {
            int outHeight = carRect.bottom - windowSize.height;
            outRect = C_RECT(carRect.left, 0, carRect.right, outHeight);
            shapes::Rectangle::DrawRectangle(hDC, outRect, m_BkColor, PS_SOLID, m_FrameWidth, m_FrameColor);
        }
        else if (m_MoveType == CAR_MOVE_LEFT)
        {
            int outWidth = 0 - carRect.left;
            outRect = C_RECT((windowSize.width - outWidth), carRect.top, windowSize.width, carRect.bottom);
            shapes::Rectangle::DrawRectangle(hDC, outRect, m_BkColor, PS_SOLID, m_FrameWidth, m_FrameColor);
        }
        else if (m_MoveType == CAR_MOVE_RIGHT)
        {
            int outWidth = carRect.right - windowSize.width;
            outRect = C_RECT(0, carRect.top, outWidth, carRect.bottom);
            shapes::Rectangle::DrawRectangle(hDC, outRect, m_BkColor, PS_SOLID, m_FrameWidth, m_FrameColor);
        }
    }

}

void Car3_3::HandleCollision(const std::string& otherName)
{
}
