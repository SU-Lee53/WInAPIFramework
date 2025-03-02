#include "../pch.h"
#include "Demo2_5.h"
#include "../TextBox.h"
#include "../Utils.h"
#include "../Caret.h"

using namespace std;

BOOL Demo2_5::Initialize()
{
    m_pProcFunction = WndProc;

    m_AppDesc.wndName = L"Demo2-5";
    m_AppDesc.wndStyle = WS_OVERLAPPEDWINDOW;
    m_AppDesc.backgroundColor = WHITE_BRUSH;
    m_AppDesc.wndIcon = IDI_APPLICATION;
    m_AppDesc.wndCursor = IDC_ARROW;
    m_AppDesc.wndPosition.x = 100;
    m_AppDesc.wndPosition.y = 50;
    m_AppDesc.wndSize.width = 800;
    m_AppDesc.wndSize.height = 600;

    m_pCaret = make_shared<Caret>();
    
    m_pInputTextBox = make_shared<TextBox>();
    m_pInputTextBox->Initialize(C_RECT(0, 0, m_AppDesc.wndSize.width, m_AppDesc.wndSize.height), DT_EDITCONTROL | DT_LEFT | DT_TOP);


    return 0;
}

void Demo2_5::OnCreate(HWND hWnd)
{
    BOOL bResult = TRUE;
    m_pCaret->Create(hWnd, NULL, 5, 15);
    m_pCaret->Show(hWnd);

    if (!bResult) __debugbreak();
}

void Demo2_5::OnPaint()
{
    HDC hDC = BeginAppPaint();
    if (!hDC)
        __debugbreak();

    SIZE size = TextBox::GetTextExtent(hDC, m_pTextArr[m_uiCurLine]);

    for (int i = 0; i < 10; i++)
    {
        TextBox::DrawFormattedString(hDC, { m_Offset.x, (ULONG)((20 * i) + m_Offset.y) }, m_pTextArr[i].c_str());
    }

    if (!m_bOverwrite)
        m_pCaret->SetPos(size.cx + m_Offset.x, 20 * m_uiCurLine + m_Offset.y);
    else
    {
        m_pTextArr[m_uiCurLine].substr(0, m_uiOverwriteIndex);
        size = TextBox::GetTextExtent(hDC, m_pTextArr[m_uiCurLine].substr(0, m_uiOverwriteIndex));
        m_pCaret->SetPos(size.cx + m_Offset.x, 20 * m_uiCurLine + m_Offset.y);
    }

    if (!EndAppPaint())
        __debugbreak;
}

void Demo2_5::OnChar(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    if (wParam == VK_RETURN)
    {
        if (m_bOverwrite) m_uiOverwriteIndex = 0;
        m_uiCurLine++;

        if (m_uiCurLine > 10) m_uiCurLine = 0;
    }
    else if (wParam == VK_BACK)
    {
        if (!m_bOverwrite)
        {
            if (m_pTextArr[m_uiCurLine].empty())
            {
                m_uiCurLine = m_uiCurLine > 0 ? --m_uiCurLine : m_uiCurLine;

                if (!m_pTextArr[m_uiCurLine].empty())
                    m_pTextArr[m_uiCurLine].pop_back();
            }
            else
            {
                m_pTextArr[m_uiCurLine].pop_back();
            }
        }
        else
        {
            if (m_uiOverwriteIndex <= 0)
                m_uiOverwriteIndex = 0;
            else
                m_uiOverwriteIndex--;

            m_pTextArr[m_uiCurLine].erase(m_pTextArr[m_uiCurLine].cbegin() + m_uiOverwriteIndex);
            
        }
    }
    else
    {
        m_bOverwrite ? Overwrite(wParam) : WriteOnBack(wParam);
        if (!m_bOverwrite)
        {
            if (m_pTextArr[m_uiCurLine].size() >= MAX_LINE_SIZE)
            {
                if (++m_uiCurLine < 10)
                {
                    // m_uiCurLine Already increased
                    m_uiOverwriteIndex = 0;
                }
                else
                {
                    m_uiOverwriteIndex = 0;
                    m_uiCurLine = 0;
                    m_bOverwrite = TRUE;
                }
            }
        }
        else
        {
            if (m_uiOverwriteIndex >= MAX_LINE_SIZE)
            {
                if (++m_uiCurLine < 10)
                {
                    // Already increased
                    m_uiOverwriteIndex = 0;
                }
                else
                {
                    m_uiOverwriteIndex = 0;
                    m_uiCurLine = 0;
                    m_bOverwrite = TRUE;
                }
            }
        }
    }


    ::InvalidateRect(CUR_HWND, NULL, TRUE);
}

void Demo2_5::WriteOnBack(WPARAM wParam)
{
    wchar_t in = wParam;
    m_pTextArr[m_uiCurLine].push_back(wParam);
}

void Demo2_5::Overwrite(WPARAM wParam)
{
    wchar_t in = wParam;
    m_pTextArr[m_uiCurLine][m_uiOverwriteIndex++] = in;
}

LRESULT Demo2_5::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    std::shared_ptr<Demo2_5> pDemo = CUR_DEMO(Demo2_5);

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
