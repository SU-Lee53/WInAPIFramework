#include "../pch.h"
#include "Demo2_4.h"
#include "../TextBox.h"
#include "../Utils.h"
#include "../Caret.h"

using namespace std;

BOOL Demo2_4::Initialize()
{
    m_pProcFunction = WndProc;

    m_AppDesc.wndName = L"Demo2-4";
    m_AppDesc.wndStyle = WS_OVERLAPPEDWINDOW;
    m_AppDesc.backgroundColor = WHITE_BRUSH;
    m_AppDesc.wndIcon = IDI_APPLICATION;
    m_AppDesc.wndCursor = IDC_ARROW;
    m_AppDesc.wndPosition.x = 100;
    m_AppDesc.wndPosition.y = 50;
    m_AppDesc.wndSize.width = 800;
    m_AppDesc.wndSize.height = 600;

    m_pInputText = make_shared<TextBox>();
    m_pInputText->Initialize(C_RECT(0, 0, 100, 100), DT_SINGLELINE | DT_LEFT | DT_TOP);
    
    m_pResultText = make_shared<TextBox>();
    m_pResultText->Initialize(C_RECT(0, 0, 0, 0), DT_EDITCONTROL | DT_LEFT | DT_TOP);

    m_pCaret = make_shared<Caret>();

    return 0;
}

void Demo2_4::OnCreate(HWND hWnd)
{
    BOOL bResult = TRUE;
    m_pCaret->Create(hWnd, NULL, 5, 15);
    m_pCaret->Show(hWnd);

    if (!bResult) __debugbreak();
}

void Demo2_4::OnPaint()
{
    HDC hDC = BeginAppPaint();
    if (!hDC)
        __debugbreak();

    SIZE size = TextBox::GetTextExtent(hDC, m_wstrInput);
    m_pInputText->Draw(hDC, m_wstrInput);
    m_pCaret->SetPos(size.cx, 0);

    m_pResultText->Draw(hDC, m_wstrOutput);

    if (!EndAppPaint())
        __debugbreak;
}

void Demo2_4::OnChar(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    if (wParam == VK_BACK)
    {
        if(!m_wstrInput.empty())
            m_wstrInput.pop_back();
    }
    else if (wParam == VK_RETURN)
    {
        m_pCaret->SetPos(0, 0);
        ProcessInput();
        return;
    }
    else
    {
        wchar_t in = wParam;
        m_wstrInput += in;
    }

    ::InvalidateRect(CUR_HWND, NULL, TRUE);
}

void Demo2_4::ProcessInput()
{
    m_wstrOutput.clear();
    std::wstringstream stream(m_wstrInput);

    int x = 0;
    int y = 0;
    int N = 0;
    int M = 0;

    stream >> x >> y >> N >> M;

    if (x == 0)
    {
        DestroyWindow(CUR_HWND);
    }

    BOOL bRangeOK = TRUE;

    if (N < 1 || N > 19)
    {
        m_wstrOutput += L"Invalid Input : N was " + ::to_wstring(N) + L"\n";
        bRangeOK = FALSE;
    }

    if (M < 1 || M > 30)
    {
        m_wstrOutput += L"Invalid Input : M was " + ::to_wstring(M) + L"\n";
        bRangeOK = FALSE;
    }

    if (!bRangeOK) goto lb_end;

    for (int i = 1; i < M + 1; i++)
    {
        m_wstrOutput += Utils::GenerateFormattedWString(L"%d * %d = %d\n", N, i, N * i);
    }

lb_end:
    m_wstrInput.clear();
    m_pResultText->SetRect(C_RECT(x, y, x + 200, y + 500));

    ::InvalidateRect(CUR_HWND, NULL, TRUE);
}

LRESULT Demo2_4::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    std::shared_ptr<Demo2_4> pDemo = CUR_DEMO(Demo2_4);

    switch (message)
    {
    case WM_CREATE:
        pDemo->OnCreate(hWnd);
        break;

    case WM_PAINT:
        pDemo->OnPaint();
        break;

    case WM_CHAR:
        pDemo->OnChar(hWnd, wParam, lParam);
        break;

    case WM_DESTROY:
        pDemo->m_pCaret->Hide(hWnd);
        pDemo->m_pCaret->Destroy();
        PostQuitMessage(0);
        return 0;

    default:
        break;
    }
    
    return DefWindowProc(hWnd, message, wParam, lParam);
}
