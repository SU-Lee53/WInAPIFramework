#include "../pch.h"
#include "Demo2_11.h"
#include "../TextBox.h"
#include "../Utils.h"
#include "../Caret.h"

using namespace std;
using namespace shapes;

BOOL Demo2_11::Initialize()
{
    m_pProcFunction = WndProc;

    m_AppDesc.wndName = L"Demo2-11";
    m_AppDesc.wndStyle = WS_OVERLAPPEDWINDOW;
    m_AppDesc.backgroundColor = WHITE_BRUSH;
    m_AppDesc.wndIcon = IDI_APPLICATION;
    m_AppDesc.wndCursor = IDC_ARROW;
    m_AppDesc.wndPosition.x = 100;
    m_AppDesc.wndPosition.y = 50;
    m_AppDesc.wndSize.width = 1200;
    m_AppDesc.wndSize.height = 800;

    return 0;
}

void Demo2_11::OnCreate(HWND hWnd)
{
    BOOL bResult = TRUE;

    m_pTextBox = make_shared<TextBox>();
    m_pTextBox->Initialize(C_RECT(400, 700, 800, 750), DT_VCENTER | DT_CENTER | DT_SINGLELINE);

    if (!bResult) __debugbreak();
}

void Demo2_11::OnPaint()
{
    HDC hDC = BeginAppPaint();
    if (!hDC)
        __debugbreak();

    m_pTextBox->Draw(hDC, m_wstrInput.c_str(), TEXTBOX_DRAW_TYPE_DRAW_OUTLINE);

    for (const auto& shape : m_pShapes)
    {
        shape->DrawInWindowCoord(hDC);
    }

    TextBox::DrawFormattedString(hDC, { 700, 0 }, m_wstrErr.c_str());
    m_wstrErr.clear();

    if (!EndAppPaint())
        __debugbreak;
}

void Demo2_11::OnChar(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    switch (wParam)
    {

    default:
        ProcessChar(wParam);
        break;

    }


    ::InvalidateRect(CUR_HWND, NULL, TRUE);
}

void Demo2_11::ProcessChar(WPARAM wParam)
{
    if (wParam == VK_BACK)
    {
        if (!m_wstrInput.empty())
            m_wstrInput.pop_back();
    }
    else if (wParam == VK_RETURN)
    {
        ProcessCommand(m_wstrInput, FALSE);
        return;
    }
    else
    {
        wchar_t in = wParam;

        if (iswdigit(in) || in == L' ')
        {
            m_wstrInput += in;
        }
    }

    ::InvalidateRect(CUR_HWND, NULL, TRUE);
}

void Demo2_11::ProcessCommand(const std::wstring& wstrCommand, BOOL bIsFromA)
{
    if (m_pShapes.size() >= MAX_SHAPE_COUNT)
    {
        m_wstrErr = L"Shape Full";
        return;
    }

    std::wstringstream stream;
    stream.str(wstrCommand);

    int shapeType;
    POINT pos1;
    POINT pos2;
    int frameWidth;

    stream >> shapeType >> pos1.x >> pos1.y >> pos2.x >> pos2.y >> frameWidth;

    if (shapeType < 1 || shapeType > 4)
    {
        m_wstrErr = L"Wrong Shape Type";
        return;
    }

    if (frameWidth < 1 || frameWidth > 10)
    {
        m_wstrErr = L"Wrong Frame Width size";
        return;
    }

    if (shapeType == 1)
    {
        shared_ptr<shapes::Line> p = make_shared<shapes::Line>();
        p->Create(pos1, pos2);
        p->SetFrameColor(RANDOM.GenerateRandomColor());
        p->SetFrameWidth(frameWidth);
        m_pShapes.push_back(p);
    }
    else if (shapeType == 2)
    {
        int rectWidth = pos2.x - pos1.x;
        int rectHeight = pos2.y - pos1.y;
        vector<POINT> triPoints(3);
        triPoints[0] = POINT{ (pos1.x + ((pos2.x - pos1.y) / 2)), pos1.y };
        triPoints[1] = POINT{ pos2.x, pos2.y };
        triPoints[2] = POINT{ pos1.x, pos2.y };

        shared_ptr<shapes::Polygon> p = make_shared<shapes::Polygon>();
        p->Create(triPoints);
        p->SetFrameColor(RANDOM.GenerateRandomColor());
        p->SetBackgroundColor(RANDOM.GenerateRandomColor());
        p->SetFrameWidth(frameWidth);
        m_pShapes.push_back(p);
    }
    else if (shapeType == 3)
    {
        shared_ptr<shapes::Rectangle> p = make_shared<shapes::Rectangle>();

        ULONG width = pos2.x - pos1.x;
        ULONG height = pos2.y - pos1.y;

        p->Create(C_RECT(pos1.x, pos1.y, pos2.x, pos2.y));
        p->SetFrameColor(RANDOM.GenerateRandomColor());
        p->SetBackgroundColor(RANDOM.GenerateRandomColor());
        p->SetFrameWidth(frameWidth);
        m_pShapes.push_back(p);
    }
    else if (shapeType == 4)
    {
        shared_ptr<shapes::Ellipse> p = make_shared<shapes::Ellipse>();
        p->Create(C_RECT(pos1.x, pos1.y, pos2.x, pos2.y));
        p->SetFrameColor(RANDOM.GenerateRandomColor());
        p->SetBackgroundColor(RANDOM.GenerateRandomColor());
        p->SetFrameWidth(frameWidth);
        m_pShapes.push_back(p);
    }

    m_CommandForN.clear();

    if(!bIsFromA)
        m_CommandRecord.push_back(wstrCommand);

    m_wstrInput.clear();
}

void Demo2_11::OnKeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    switch (wParam)
    {
    case VK_ADD:
        ProcessPlus();
        break;

    case VK_SUBTRACT:
        ProcessMinus();
        break;

    case VK_UP:
    case VK_DOWN:
    case VK_LEFT:
    case VK_RIGHT:
        ProcessArrow(wParam);
        break;

    case VK_F1:
        ProcessF1();
        break;

    case VK_F2:
        ProcessF2();
        break;

    case 'P':
        ProcessP();
        break;

    case 'N':
        ProcessN();
        break;

    case 'A':
        ProcessA();
        break;


    default:
        break;
    }

    ::InvalidateRect(CUR_HWND, NULL, TRUE);
}

void Demo2_11::ProcessArrow(WPARAM wParam)
{
    if (m_pShapes.empty())
    {
        m_wstrErr = L"There is no shapes";
        return;
    }

    POINT offset = { 0,0 };

    if (wParam == VK_UP)
    {
        offset.y--;
    }
    else if (wParam == VK_DOWN)
    {
        offset.y++;
    }
    else if (wParam == VK_LEFT)
    {
        offset.x--;
    }
    else if (wParam == VK_RIGHT)
    {
        offset.x++;
    }

    for_each(m_pShapes.begin(), m_pShapes.end(), 
        [&offset](shared_ptr<Shapes>& p) -> void
        {
            p->AddOffset(offset);
        }
    );
}

void Demo2_11::ProcessPlus()
{
    if (m_pShapes.empty())
    {
        m_wstrErr = L"There is no shapes";
        return;
    }

    for (auto& p : m_pShapes)
    {
        int frameWidth = p->GetFrameWidth();
        if (frameWidth < 10)
        {
            p->SetFrameWidth(++frameWidth);
        }
        else
        {
            p->AddScale({ 1,1 });
        }
    }
}

void Demo2_11::ProcessMinus()
{
    if (m_pShapes.empty())
    {
        m_wstrErr = L"There is no shapes";
        return;
    }

    for (auto& p : m_pShapes)
    {
        int frameWidth = p->GetFrameWidth();
        if (frameWidth > 0)
        {
            p->SetFrameWidth(--frameWidth);
        }
        else
        {
            p->AddScale({ -1,-1 });
        }
    }
}

void Demo2_11::ProcessF1()
{
    if (m_pShapes.empty())
    {
        m_wstrErr = L"There is no shapes";
        return;
    }

    for (auto& p : m_pShapes)
    {
        p->SetFrameColor(RANDOM.GenerateRandomColor());
    }
}

void Demo2_11::ProcessF2()
{
    if (m_pShapes.empty())
    {
        m_wstrErr = L"There is no shapes";
        return;
    }

    for (auto& p : m_pShapes)
    {
        p->SetBackgroundColor(RANDOM.GenerateRandomColor());
    }
}

void Demo2_11::ProcessP()
{
    if (m_pShapes.empty())
    {
        m_wstrErr = L"There is no shapes";
        return;
    }

    if ((m_CommandRecord.size() - 2) >= 0)
    {
        ProcessCommand(m_CommandRecord[m_pShapes.size() - 2], FALSE);
        m_CommandForN = m_CommandRecord[m_CommandRecord.size() - 2];
    }
    else
    {
        m_wstrErr = L"There is no prior command";
    }
}

void Demo2_11::ProcessN()
{
    if (m_pShapes.empty())
    {
        m_wstrErr = L"There is no shapes";
        return;
    }

    if (!m_CommandForN.empty())
    {
        ProcessCommand(m_CommandForN, FALSE);
    }
    else
    {
        m_wstrErr = L"There is no next command : Call P first";
    }
}

void Demo2_11::ProcessA()
{
    if (m_pShapes.empty())
    {
        m_wstrErr = L"There is no shapes";
        return;
    }

    m_pShapes.clear();

    for (int i = 0; i < m_CommandRecord.size(); i++)
    {
        ProcessCommand(m_CommandRecord[i], TRUE);
    }
}

LRESULT Demo2_11::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    std::shared_ptr<Demo2_11> pDemo = CUR_DEMO(Demo2_11);

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

