#include "../pch.h"
#include "Demo2_13.h"
#include "../TextBox.h"
#include "../Utils.h"
#include "../Caret.h"

using namespace std;
using namespace shapes;

BOOL Demo2_13::Initialize()
{
    m_pProcFunction = WndProc;

    m_AppDesc.wndName = L"Demo2-13";
    m_AppDesc.wndStyle = WS_OVERLAPPEDWINDOW;
    m_AppDesc.backgroundColor = WHITE_BRUSH;
    m_AppDesc.wndIcon = IDI_APPLICATION;
    m_AppDesc.wndCursor = IDC_ARROW;
    m_AppDesc.wndPosition.x = 100;
    m_AppDesc.wndPosition.y = 50;
    m_AppDesc.wndSize.width = 800;
    m_AppDesc.wndSize.height = 800;

    return 0;
}

void Demo2_13::OnCreate(HWND hWnd)
{
    BOOL bResult = TRUE;

	// Create Base (Rectangle, Line, Line, Line)
    m_pHangBase.clear();
    {
        shared_ptr<shapes::Rectangle> pBase = make_shared<shapes::Rectangle>();
        pBase->Create(C_RECT(0, 0, 500, 50));
        pBase->SetOffset({ 100, 500 });
        pBase->SetFrameWidth(5);
        m_pHangBase.push_back(pBase);

        shared_ptr<shapes::Line> pBase2 = make_shared<shapes::Line>();
        pBase2->Create(POINT{ 0, 0 }, POINT{ 0, 400 });
        pBase2->SetOffset({ 150, 100 });
        pBase2->SetFrameWidth(3);
        m_pHangBase.push_back(pBase2);

        shared_ptr<shapes::Line> pBase3 = make_shared<shapes::Line>();
        pBase3->Create(POINT{ 0, 0 }, POINT{ 300, 0 });
        pBase3->SetOffset({ 150, 100 });
        pBase3->SetFrameWidth(3);
        m_pHangBase.push_back(pBase3);

        shared_ptr<shapes::Line> pBase4 = make_shared<shapes::Line>();
        pBase4->Create(POINT{ 0, 0 }, POINT{ 0, 50 });
        pBase4->SetOffset({ 350, 100 });
        pBase4->SetFrameWidth(3);
        m_pHangBase.push_back(pBase4);
    }

	// Create HangMan(Rectangle, Line, Line, Line, Line)
    m_pHangMan.clear();
    {
		std::shared_ptr<shapes::Ellipse> pHead = make_shared<shapes::Ellipse>();
		pHead->Create(C_RECT(0, 0, 50, 50));
		pHead->SetOffset({ 325, 150 });
		pHead->SetFrameWidth(3);
		m_pHangMan.push_back(pHead);

		std::shared_ptr<shapes::Line> pBody = make_shared<shapes::Line>();
		pBody->Create(POINT{ 0, 0 }, POINT{ 0, 200 });
		pBody->SetOffset({ 350, 200 });
		pBody->SetFrameWidth(3);
		m_pHangMan.push_back(pBody);

		std::shared_ptr<shapes::Line> pLeftArm = make_shared<shapes::Line>();
		pLeftArm->Create(POINT{ 0, 0 }, POINT{ -50, 50 });
		pLeftArm->SetOffset({ 350, 250 });
		pLeftArm->SetFrameWidth(3);
		m_pHangMan.push_back(pLeftArm);

		std::shared_ptr<shapes::Line> pRightArm = make_shared<shapes::Line>();
		pRightArm->Create(POINT{ 0, 0 }, POINT{ 50, 50 });
		pRightArm->SetOffset({ 350, 250 });
		pRightArm->SetFrameWidth(3);
		m_pHangMan.push_back(pRightArm);

		std::shared_ptr<shapes::Line> pLeftLeg = make_shared<shapes::Line>();
		pLeftLeg->Create(POINT{ 0, 0 }, POINT{ -50, 50 });
		pLeftLeg->SetOffset({ 350, 400 });
		pLeftLeg->SetFrameWidth(3);
		m_pHangMan.push_back(pLeftLeg);

		std::shared_ptr<shapes::Line> pRightLeg = make_shared<shapes::Line>();
		pRightLeg->Create(POINT{ 0, 0 }, POINT{ 50, 50 });
		pRightLeg->SetOffset({ 350, 400 });
		pRightLeg->SetFrameWidth(3);
		m_pHangMan.push_back(pRightLeg);
    }

    m_pTextBox = make_shared<TextBox>();
	m_pTextBox->Initialize(C_RECT(0, 600, 800, 750), DT_VCENTER | DT_CENTER | DT_SINGLELINE);

    ResetGame();

    if (!bResult) __debugbreak();
}

void Demo2_13::OnPaint()
{
    HDC hDC = BeginAppPaint();
    if (!hDC)
        __debugbreak();

	for (const auto& shape : m_pHangBase)
	{
		shape->DrawInWindowCoord(hDC);
	}
    
	for (const auto& shape : m_pHangMan)
	{
		shape->DrawInWindowCoord(hDC);
	}

    if (m_bShowAnswser)
    {
		wstring ansStr = L"Answer : " + m_Words[m_WordSelected];
		TextBox::DrawFormattedString(hDC, { 0, 0 }, ansStr.c_str());
    }

    if (m_bGameEnded)
    {
        if (m_bGameWin)
        {
			TextBox::DrawFormattedString(hDC, { 50, 50 }, L"YOU WIN : PRESS F1 TO RESTART");
        }
        else
        {
			TextBox::DrawFormattedString(hDC, { 50, 50 }, L"YOU LOSE : PRESS F1 TO RESTART");
        }
    }

    COLORREF bkColor = RGB(255 - ((255 / 5) * m_FailCount), 255 - ((255 / 5) * m_FailCount), 255 - ((255 / 5) * m_FailCount));
	COLORREF textColor = RGB(255, 0, 0);
	m_pTextBox->SetBackgroundColor(bkColor);
	m_pTextBox->SetTextColor(textColor);
	m_pTextBox->Draw(hDC, m_wstrOutput.c_str(), TEXTBOX_DRAW_TYPE_DRAW_OUTLINE | TEXTBOX_DRAW_TYPE_FILL_RECT);

	SIZE size = TextBox::GetTextExtent(hDC, m_Words[m_WordSelected].c_str());

    if (!EndAppPaint())
        __debugbreak;
}

void Demo2_13::OnChar(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    switch (wParam)
    {
    default:
        ProcessChar(wParam);
        break;
    }


    ::InvalidateRect(CUR_HWND, NULL, TRUE);
}

void Demo2_13::OnKeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    switch (wParam)
    {
    case VK_F1:
        ResetGame();
        break;

	case VK_F2:
		QuitGame();
		break;
        
	case VK_F3:
        m_bShowAnswser = !m_bShowAnswser;
		break;

    default:
        break;
    }

    ::InvalidateRect(CUR_HWND, NULL, TRUE);
}

void Demo2_13::ProcessChar(WPARAM wParam)
{
    if (m_bGameEnded)
    {
        return;
    }

	wchar_t in = wParam;
	in = std::toupper(in);
	wstring rep(1, in);
	size_t findPos = m_Words[m_WordSelected].find(in);
	if (findPos == wstring::npos)
	{
		m_FailCount++;
	}
    else
    {
		while (findPos != wstring::npos)
		{
			if (m_wstrOutput[findPos] == in)
			{
                findPos = m_Words[m_WordSelected].find(in, findPos + 1);
				continue;
			}
			m_wstrOutput.replace(findPos, 1, rep);
            findPos = m_Words[m_WordSelected].find(in, findPos + 1);
		}  
		if (m_wstrOutput == m_Words[m_WordSelected])
		{
			m_bGameEnded = TRUE;
			m_bGameWin = TRUE;
		}
    }
	if (m_FailCount >= 5)
	{
		m_bShowAnswser = TRUE;
		m_bGameEnded = TRUE;
        m_bGameWin = FALSE;
	}
}

void Demo2_13::ResetGame()
{
	m_FailCount = 0;
    m_WordSelected = RANDOM.GenerateRandom((int)0, (int)(m_Words.size() - 1));
    m_wstrOutput.clear();
    
	m_wstrOutput.assign(m_Words[m_WordSelected].size(), L'_');

    m_bGameEnded = FALSE;
    m_bGameWin = FALSE;
    m_bShowAnswser = FALSE;
}

void Demo2_13::QuitGame()
{
	DestroyWindow(CUR_HWND);
}

LRESULT Demo2_13::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    std::shared_ptr<Demo2_13> pDemo = CUR_DEMO(Demo2_13);

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

