#include "../pch.h"
#include "Demo2_12.h"
#include "../TextBox.h"
#include "../Utils.h"
#include "../Caret.h"

using namespace std;
using namespace shapes;

BOOL Demo2_12::Initialize()
{
    m_pProcFunction = WndProc;

    m_AppDesc.wndName = L"Demo2-12";
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

void Demo2_12::OnCreate(HWND hWnd)
{
    BOOL bResult = TRUE;

	m_pBoardRect = make_shared<shapes::Rectangle>();
    m_pBoardRect->Create(C_RECT(0,0,25,25));
	m_lBoardSize = 25;
	m_nRowCols = 40;

    if (!bResult) __debugbreak();
}

void Demo2_12::OnPaint()
{
    HDC hDC = BeginAppPaint();
    if (!hDC)
        __debugbreak();

	DrawBoard(hDC);
    DrawShapes(hDC);
    TextBox::DrawFormattedString(hDC, WndPosition{ 10, 10 }, m_wstrErr.c_str());

	m_wstrErr.clear();

    if (!EndAppPaint())
        __debugbreak;
}

void Demo2_12::OnChar(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    switch (wParam)
    {
    default:
		ProcessChar(wParam);
        break;
    }


    ::InvalidateRect(CUR_HWND, NULL, TRUE);
}

void Demo2_12::OnKeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    switch (wParam)
    {
    case VK_UP:
    case VK_DOWN:
    case VK_LEFT:
    case VK_RIGHT:
        ProcessArrow(wParam);
        break;

    case VK_ADD:
		ProessPlus();
		break;

	case VK_SUBTRACT:
		ProcessMinus();
		break;


    default:
        break;
    }

    ::InvalidateRect(CUR_HWND, NULL, TRUE);
}

void Demo2_12::ProcessS()
{
	m_DrawMode = BOARD_DRAW_MODE_SMALL;
	m_lBoardSize = 33;
	m_nRowCols = 30;
    m_pBoardRect->SetRectAndReset(C_RECT(0, 0, m_lBoardSize, m_lBoardSize));

    ProcessP();
}

void Demo2_12::ProcessM()
{
    m_DrawMode = BOARD_DRAW_MODE_MEDIUM;
    m_lBoardSize = 25;
	m_nRowCols = 40;
    m_pBoardRect->SetRectAndReset(C_RECT(0, 0, m_lBoardSize, m_lBoardSize));

    ProcessP();
}

void Demo2_12::ProcessL()
{
    m_DrawMode = BOARD_DRAW_MODE_LARGE;
    m_lBoardSize = 20;
	m_nRowCols = 50;
    m_pBoardRect->SetRectAndReset(C_RECT(0, 0, m_lBoardSize, m_lBoardSize));
    
    ProcessP();
}

void Demo2_12::ProcessE()
{
    if (m_pShapes.size() >= 10)
    {
        m_wstrErr = L"Shapes Full";
        return;
    }

	std::shared_ptr<shapes::Ellipse> p = make_shared<shapes::Ellipse>();
    p->Create(C_RECT(0, 0, 1, 1));
    p->SetScale(POINT(m_pBoardRect->GetSize().width, m_pBoardRect->GetSize().height));
    p->SetOffset(RANDOM.GenerateRandomPoint(0, m_nRowCols - 1));
    p->SetBackgroundColor(RANDOM.GenerateRandomColor());

	m_pShapes.push_back(p);
    m_ShapeTypes[m_pShapes.size() - 1] = SHAPE_TYPE_ELLIPSE;
}

void Demo2_12::ProcessT()
{
    if (m_pShapes.size() >= 10)
    {
        m_wstrErr = L"Shapes Full";
        return;
    }

	std::shared_ptr<shapes::Polygon> p = make_shared<shapes::Polygon>();
    std::vector<POINT> triPoints = {};
	triPoints.push_back(POINT{ 0, 0 });
	triPoints.push_back(POINT{ 1, 1 });
	triPoints.push_back(POINT{ 0, 1 });
	p->Create(triPoints);
    p->SetScale(POINT(m_pBoardRect->GetSize().width, m_pBoardRect->GetSize().height));
	p->SetOffset(RANDOM.GenerateRandomPoint(0, m_nRowCols - 1));
    p->SetBackgroundColor(RANDOM.GenerateRandomColor());

	m_pShapes.push_back(p);
	m_ShapeTypes[m_pShapes.size() - 1] = SHAPE_TYPE_TRIANGLE;
}

void Demo2_12::ProcessR()
{
    if (m_pShapes.size() >= 10)
    {
        m_wstrErr = L"Shapes Full";
        return;
    }

	std::shared_ptr<shapes::Rectangle> p = make_shared<shapes::Rectangle>();
	p->Create(C_RECT(0, 0, 1, 1));
	p->SetScale(POINT(m_pBoardRect->GetSize().width, m_pBoardRect->GetSize().height));
	p->SetOffset(RANDOM.GenerateRandomPoint(0, m_nRowCols - 1));
	p->SetBackgroundColor(RANDOM.GenerateRandomColor());

	m_pShapes.push_back(p);
    m_ShapeTypes[m_pShapes.size() - 1] = SHAPE_TYPE_RECTANGLE;
}

void Demo2_12::ProcessC()
{
	SHAPE_TYPE type = m_ShapeTypes[m_Selected];

    if (m_bColorChanged == FALSE)
    {
		COLORREF color = RANDOM.GenerateRandomColor();
        for (int i = 0; i < m_pShapes.size(); i++)
        {
            if (m_ShapeTypes[i] == type)
            {
                m_ColorStored[i] = m_pShapes[i]->GetBackgroundColor();
				m_pShapes[i]->SetBackgroundColor(color);
            }
        }
    }
    else
    {
		for (int i = 0; i < m_ShapeTypes.size(); i++)
		{
			if (m_ShapeTypes[i] == type)
			{
				m_pShapes[i]->SetBackgroundColor(m_ColorStored[i]);
			}
		}
    }

	m_bColorChanged = !m_bColorChanged;
}

void Demo2_12::ProcessD()
{
    if (m_pShapes.size() > m_Selected)
    {
        if (m_pShapes[m_Selected] != nullptr)
        {
			m_pShapes.erase(m_pShapes.begin() + m_Selected);
        }
    }
}

void Demo2_12::ProcessP()
{
    m_pShapes.clear();
	m_ShapeTypes.fill(SHAPE_TYPE_NONE);
    m_ColorStored.fill(RGB(0,0,0));
    m_Selected = 0;
}

void Demo2_12::ProcessQ()
{
    DestroyWindow(CUR_HWND);
}

void Demo2_12::ProcessNum(WPARAM wParam)
{
    int num = (wParam - '1'); // Convert WPARAM to integer
    if (num >= 0 && num < m_pShapes.size())
    {
        m_Selected = num;
    }
    else
    {
        m_wstrErr = L"Invalid Selection";
    }

    ::InvalidateRect(CUR_HWND, NULL, TRUE);
}

void Demo2_12::ProcessArrow(WPARAM wParam)
{
    if (m_pShapes.empty())
    {
        m_wstrErr = L"There is no shapes";
        return;
    }

    if (wParam == VK_UP)
    {
        POINT set = m_pShapes[m_Selected]->GetOffset();
        set.y--;
        if (set.y < 0) set.y = m_nRowCols - 1;
		m_pShapes[m_Selected]->SetOffset(set);
    }
    else if (wParam == VK_DOWN)
    {
        POINT set = m_pShapes[m_Selected]->GetOffset();
        set.y++;
        if (set.y >= m_nRowCols) set.y = 0;
        m_pShapes[m_Selected]->SetOffset(set);
    }
    else if (wParam == VK_LEFT)
    {
        POINT set = m_pShapes[m_Selected]->GetOffset();
        set.x--;
        if (set.x < 0) set.x = m_nRowCols - 1;
        m_pShapes[m_Selected]->SetOffset(set);
    }
    else if (wParam == VK_RIGHT)
    {
        POINT set = m_pShapes[m_Selected]->GetOffset();
        set.x++;
        if (set.x >= m_nRowCols) set.x = 0;
        m_pShapes[m_Selected]->SetOffset(set);
    }
}

void Demo2_12::ProessPlus()
{
	auto& p = m_pShapes[m_Selected];

	POINT originScale = p->GetScale();
	if (originScale.x >= m_lBoardSize)
	{
		m_wstrErr = L"Max Scale";
		return;
	}
    else
    {
		p->AddScale(POINT{ 1, 1 });
    }
}

void Demo2_12::ProcessMinus()
{
    auto& p = m_pShapes[m_Selected];

    POINT originScale = p->GetScale();
    if (originScale.x <= 2)
    {
        m_wstrErr = L"Min Scale";
        return;
    }
    else
    {
        p->AddScale(POINT{ -1, -1 });
    }
}

void Demo2_12::DrawBoard(HDC hDC)
{
    int offset = 100;

	for (int i = 0; i < m_nRowCols; i++)
	{
        m_pBoardRect->SetOffset(POINT{ offset, (LONG)((m_pBoardRect->GetSize().height * i) + offset) });
		for (int j = 0; j < m_nRowCols; j++)
		{
            m_pBoardRect->DrawInWindowCoord(hDC);
			m_pBoardRect->AddOffset(POINT{(LONG)m_pBoardRect->GetSize().width, 0});
		}
	}
}

void Demo2_12::DrawShapes(HDC hDC)
{
    int offset = 100;

	// DrawAll Except Selected
    for(int i = 0; i < m_pShapes.size(); i++)
	{
		if (i == m_Selected) continue;
		auto& p = m_pShapes[i];
        POINT originOffset = p->GetOffset();

        p->SetOffset(POINT{ offset, (LONG)((m_pBoardRect->GetSize().height * originOffset.y) + offset) });
        p->AddOffset(POINT{ (LONG)(m_pBoardRect->GetSize().width * originOffset.x), 0 });
        p->DrawInWindowCoord(hDC);
        p->SetOffset(originOffset);
    }

    // DrawAll Selected
    if (m_pShapes.size() > m_Selected)
    {
        if (m_pShapes[m_Selected] != nullptr)
        {
            auto& p = m_pShapes[m_Selected];
            POINT originOffset = p->GetOffset();
			int originFrameWidth = p->GetFrameWidth();
			COLORREF originFrameColor = p->GetFrameColor();

			p->SetFrameColor(RGB(255, 0, 0));
			p->SetFrameWidth(3);
            p->SetOffset(POINT{ offset, (LONG)((m_pBoardRect->GetSize().height * originOffset.y) + offset) });
            p->AddOffset(POINT{ (LONG)(m_pBoardRect->GetSize().width * originOffset.x), 0 });

            p->DrawInWindowCoord(hDC);

            p->SetOffset(originOffset);
			p->SetFrameColor(originFrameColor);
            p->SetFrameWidth(originFrameWidth);
        }
    }
}

void Demo2_12::ProcessChar(WPARAM wParam)
{
    if (wParam == L's' || wParam == L'S')
    {
        ProcessS();
    }
    else if (wParam == L'm' || wParam == L'M')
    {
        ProcessM();
    }
    else if (wParam == L'l' || wParam == L'L')
    {
        ProcessL();
    }
    else if (wParam == L'e' || wParam == L'E')
    {
        ProcessE();
    }
    else if (wParam == L't' || wParam == L'T')
    {
        ProcessT();
    }
    else if (wParam == L'r' || wParam == L'R')
    {
        ProcessR();
    }
    else if (wParam == L'c' || wParam == L'C')
    {
        ProcessC();
    }
    else if (wParam == L'd' || wParam == L'D')
    {
        ProcessD();
    }
    else if (wParam == L'p' || wParam == L'P')
    {
        ProcessP();
    }
    else if (wParam == L'q' || wParam == L'Q')
    {
        ProcessQ();
    }
    else
    {
		ProcessNum(wParam);
    }


    ::InvalidateRect(CUR_HWND, NULL, TRUE);
}

LRESULT Demo2_12::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    std::shared_ptr<Demo2_12> pDemo = CUR_DEMO(Demo2_12);

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

