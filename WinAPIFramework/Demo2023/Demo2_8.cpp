#include "../pch.h"
#include "Demo2_8.h"
#include "../TextBox.h"
#include "../Utils.h"
#include "../Caret.h"

using namespace std;

BOOL Demo2_8::Initialize()
{
    m_pProcFunction = WndProc;

    m_AppDesc.wndName = L"Demo2-8";
    m_AppDesc.wndStyle = WS_OVERLAPPEDWINDOW;
    m_AppDesc.backgroundColor = WHITE_BRUSH;
    m_AppDesc.wndIcon = IDI_APPLICATION;
    m_AppDesc.wndCursor = IDC_ARROW;
    m_AppDesc.wndPosition.x = 100;
    m_AppDesc.wndPosition.y = 50;
    m_AppDesc.wndSize.width = 1200;
    m_AppDesc.wndSize.height = 800;

    m_pCaret = make_shared<Caret>();
    
    for (int i = 0; i < 10; i++)
    {
        m_wstrTextArr[i].resize((size_t)MAX_LINE_SIZE, L' ');
        m_uiTextSizeArr[i] = 0;
    }

    m_pInputTextBox = make_shared<TextBox>();
    m_pInputTextBox->Initialize(C_RECT(0, 0, m_AppDesc.wndSize.width, m_AppDesc.wndSize.height), DT_EDITCONTROL | DT_LEFT | DT_TOP);


    return 0;
}

void Demo2_8::OnCreate(HWND hWnd)
{
    BOOL bResult = TRUE;
    m_pCaret->Create(hWnd, NULL, 5, 15);
    m_pCaret->Show(hWnd);

    if (!bResult) __debugbreak();
}

void Demo2_8::OnPaint()
{
    HDC hDC = BeginAppPaint();
    if (!hDC)
        __debugbreak();

    for (int i = 0; i < 10; i++)
    {
        if (m_bRemoveBlankMode)
        {
            std::wstring out = RemoveBlank(m_wstrTextArr[i]);
            TextBox::DrawFormattedString(hDC, { m_Offset.x, (ULONG)((20 * i) + m_Offset.y) }, out.c_str());
        }
        else if (m_bWrapWordMode)
        {
            std::wstring out = WrapWord(m_wstrTextArr[i]);
            TextBox::DrawFormattedString(hDC, { m_Offset.x, (ULONG)((20 * i) + m_Offset.y) }, out.c_str());
        }
        else if (m_bPasswordMode)
        {
            TextBox::DrawFormattedString(hDC, { m_Offset.x, (ULONG)((20 * i) + m_Offset.y) }, m_wstrPasswordArr[i].c_str());
        }
        else
        {
            TextBox::DrawFormattedString(hDC, { m_Offset.x, (ULONG)((20 * i) + m_Offset.y) }, m_wstrTextArr[i].c_str());
        }
    }

    // Extent 계산
    SIZE size;

    if (m_bRemoveBlankMode)
    {
        std::wstring out = RemoveBlank(m_wstrTextArr[m_CaretPos.row]);
        size = TextBox::GetTextExtent(hDC, out.substr(0, m_CaretPos.col));
    }
    if (m_bWrapWordMode)
    {
        std::wstring out = WrapWord(m_wstrTextArr[m_CaretPos.row]);
        size = TextBox::GetTextExtent(hDC, out.substr(0, m_CaretPos.col));
    }
    if (m_bPasswordMode)
    {
        size = TextBox::GetTextExtent(hDC, m_wstrPasswordArr[m_CaretPos.row].substr(0, m_CaretPos.col));
    }
    else
    {
        size = TextBox::GetTextExtent(hDC, m_wstrTextArr[m_CaretPos.row].substr(0, m_CaretPos.col));
    }


    // 캐럿 위치의 계산
    m_pCaret->SetPos(size.cx + m_Offset.x + 1, (20 * m_CaretPos.row) + m_Offset.y);

    // 입력 모드
    std::wstring wstrInputMode = m_bOverwrite ? L"Overwrite" : L"Add";
    TextBox::DrawFormattedString(hDC, { 600, 700 }, wstrInputMode.c_str());


    if (!EndAppPaint())
        __debugbreak;
}

void Demo2_8::OnChar(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    switch (wParam)
    {
    case VK_RETURN:
        ProcessEnter();
        break;

    case VK_BACK:
        ProcessBackSpace();
        break;

    case VK_ESCAPE:
        ProcessEscape();
        break;

    case VK_TAB:
        ProcessTab();
        break;

    default:
        ProcessChar(wParam);
        break;

    }


    ::InvalidateRect(CUR_HWND, NULL, TRUE);
}

void Demo2_8::OnKeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    switch (wParam)
    {
    case VK_INSERT:
        ProcessInsert();
        ::InvalidateRect(CUR_HWND, NULL, TRUE);
        break;

    case VK_UP:
    case VK_DOWN:
    case VK_LEFT:
    case VK_RIGHT:
        ProcessArrow(wParam);
        ::InvalidateRect(CUR_HWND, NULL, TRUE);
        break;

    case VK_F1:
        ProcessF1();
        ::InvalidateRect(CUR_HWND, NULL, TRUE);
        break;
        
    case VK_F2:
        ProcessF2();
        ::InvalidateRect(CUR_HWND, NULL, TRUE);
        break;
        
    case VK_F3:
        ProcessF3();
        ::InvalidateRect(CUR_HWND, NULL, TRUE);
        break;
        
    case VK_F4:
        ProcessF4();
        ::InvalidateRect(CUR_HWND, NULL, TRUE);
        break;

    case VK_DELETE:
        ProcessDelete();
        ::InvalidateRect(CUR_HWND, NULL, TRUE);
        break;

    case VK_HOME:
        ProcessHome();
        ::InvalidateRect(CUR_HWND, NULL, TRUE);
        break;

    case VK_END:
        ProcessEnd();
        ::InvalidateRect(CUR_HWND, NULL, TRUE);
        break;

    case VK_PRIOR:
        ProcessPageUp();
        ::InvalidateRect(CUR_HWND, NULL, TRUE);
        break;

    case VK_NEXT:
        ProcessPageDown();
        ::InvalidateRect(CUR_HWND, NULL, TRUE);
        break;

    case VK_ADD:
        ProcessPlus();
        break;

    case VK_SUBTRACT:
        ProcessMinus();
        break;


        break;

    }

}

void Demo2_8::WriteOnBack(WPARAM wParam)
{
    wchar_t in = wParam;
    in = m_bUpperMode ? std::toupper(in) : std::tolower(in);

    wstring rep(1, in);

    if (m_uiTextSizeArr[m_CaretPos.x] < MAX_LINE_SIZE)
    {
        m_wstrTextArr[m_CaretPos.row].insert(m_CaretPos.col++, rep);
        if (m_bPasswordMode)
        {
            wstring aster(1, L'*');
            m_wstrPasswordArr[m_CaretPos.row].insert(--m_CaretPos.col, aster);
            m_CaretPos.col++;
        }
        m_uiTextSizeArr[m_CaretPos.row]++;
    }
}

void Demo2_8::Overwrite(WPARAM wParam)
{
    wchar_t in = wParam;
    in = m_bUpperMode ? std::toupper(in) : std::tolower(in);
    if(m_wstrTextArr[m_CaretPos.row][m_CaretPos.col] != L' ')
    {
        m_wstrTextArr[m_CaretPos.row][m_CaretPos.col++] = in;
        if (m_bPasswordMode)
        {
            m_wstrPasswordArr[m_CaretPos.row][--m_CaretPos.col] = '*';
            m_CaretPos.col++;
        }
    }
    else
    {
        wstring rep(1, in);

        if (m_uiTextSizeArr[m_CaretPos.x] < MAX_LINE_SIZE)
        {
            m_wstrTextArr[m_CaretPos.row].insert(m_CaretPos.col++, rep);

            if (m_bPasswordMode)
            {
                m_wstrPasswordArr[m_CaretPos.row][--m_CaretPos.col] = '*';
                m_CaretPos.col++;
            }

            m_uiTextSizeArr[m_CaretPos.row]++;
        }
    }

}

#pragma region Demo2_7
void Demo2_8::ProcessEnter()
{
    if (m_CaretPos.row >= 9)
        m_CaretPos.row = 0;
    else
        m_CaretPos.row++;

    if (m_CaretPos.col > m_uiTextSizeArr[m_CaretPos.row])
    {
        m_CaretPos.col = m_uiTextSizeArr[m_CaretPos.row];
    }
}

void Demo2_8::ProcessBackSpace()
{
    //m_wstrTextArr[m_CaretPos.x].erase(m_wstrTextArr[m_CaretPos.x].cbegin() + m_CaretPos.y);
    
    size_t deletePos = 0;
    if (m_CaretPos.y <= 0)
        deletePos = 0;
    else
        deletePos = m_CaretPos.y - 1;

    m_wstrTextArr[m_CaretPos.x].replace(deletePos, 1, L"");

    if(m_uiTextSizeArr[m_CaretPos.x] > 1)
        m_uiTextSizeArr[m_CaretPos.x]--;

    // 캐럿이 맨 앞이면 위로 올림
    if (m_CaretPos.y <= 0)
    {
        // 근데 캐럿이 첫줄에 있으면 위로 올라가면 안됨
        if (m_CaretPos.x > 0)
        {
            m_CaretPos.x--;
            m_CaretPos.y = m_uiTextSizeArr[m_CaretPos.x];
        }
        else
        {
            // 캐럿이 첫줄이면 아무것도 안하고 그냥 유지
        }

    }
    else
    {
        m_CaretPos.y--;
    }
}

void Demo2_8::ProcessEscape()
{
    for (int i = 0; i < 10; i++)
    {
        m_wstrTextArr[i].clear();
        m_wstrTextArr[i].resize((size_t)MAX_LINE_SIZE, L' ');
        m_uiTextSizeArr[i] = 0;
    }

    m_CaretPos = { 0,0 };
}

void Demo2_8::ProcessTab()
{
    int nTabs = 4;
    int expectedLength = m_uiTextSizeArr[m_CaretPos.x] + nTabs;
    if (expectedLength > 30)
    {
        int over = expectedLength - 30;
        int tabDiff = nTabs - over;
        if (tabDiff < 0) // 탭이 추가되면 안됨
        {
            nTabs = 0;
        }
        else
        {
            nTabs = tabDiff;
        }
    }

    for (int i = 0; i < nTabs; i++)
    {
        m_wstrTextArr[m_CaretPos.x].insert(m_wstrTextArr[m_CaretPos.x].cbegin() + m_CaretPos.y++, ' ');
    }
    
    
    m_uiTextSizeArr[m_CaretPos.x] += nTabs;
}

void Demo2_8::ProcessArrow(WPARAM wParam)
{
    if (wParam == VK_UP)
    {
        if (m_CaretPos.row <= 0)
            m_CaretPos.row = 0;
        else
            m_CaretPos.row--;

        if (m_CaretPos.col > m_uiTextSizeArr[m_CaretPos.row])
        {
            m_CaretPos.col = m_uiTextSizeArr[m_CaretPos.row];
        }
    }
    else if (wParam == VK_DOWN)
    {
        if (m_CaretPos.row >= 9) 
            m_CaretPos.row = 9;
        else
            m_CaretPos.row++;

        if (m_CaretPos.col > m_uiTextSizeArr[m_CaretPos.row])
        {
            m_CaretPos.col = m_uiTextSizeArr[m_CaretPos.row];
        }
    }
    else if (wParam == VK_LEFT)
    {
        if (m_CaretPos.col <= 0)
            m_CaretPos.col = 0;
        else
            m_CaretPos.col--;
    }
    else if (wParam == VK_RIGHT)
    {
        if (m_CaretPos.col >= m_uiTextSizeArr[m_CaretPos.row])
            m_CaretPos.col = m_uiTextSizeArr[m_CaretPos.row];
        else
            m_CaretPos.col++;


    }
}

void Demo2_8::ProcessDelete()
{
    // 캐럿 위치에서 앞에서 가장 가까운 공백 찾음
    size_t wordFrontPos = m_wstrTextArr[m_CaretPos.x].find_last_of(' ', m_CaretPos.y);

    if (wordFrontPos == wstring::npos)  // 공백이 없다 -> 처음부터 여기까지 한단어임
    {
        wordFrontPos = 0;
    }

    // 이번에는 캐럿 위치에서 뒤에서 가장 가까운 공백을 찾음
    size_t wordEndPos = m_wstrTextArr[m_CaretPos.x].find(' ', m_CaretPos.y);
    if (wordEndPos == wstring::npos) // 공백을 못찾았다 -> 여기부터 끝까지 한단어임
    {
        wordEndPos = m_uiTextSizeArr[m_CaretPos.x]; // 문자열 길이 == 마지막 위치
    }

    // 제거
    m_wstrTextArr[m_CaretPos.x].erase(m_wstrTextArr[m_CaretPos.x].cbegin() + wordFrontPos, m_wstrTextArr[m_CaretPos.x].cbegin() + wordEndPos);

    m_uiTextSizeArr[m_CaretPos.x] -= (wordEndPos - wordFrontPos);

    m_CaretPos.y = m_uiTextSizeArr[m_CaretPos.x];
}

void Demo2_8::ProcessHome()
{
    m_CaretPos.y = 0;
    m_bOverwrite = TRUE;
}

void Demo2_8::ProcessEnd()
{
    m_CaretPos.y = m_uiTextSizeArr[m_CaretPos.x];
    if (m_CaretPos.y >= MAX_LINE_SIZE)
    {
        m_CaretPos.x++;
        m_CaretPos.y = 0;
        m_bOverwrite = TRUE;
    }
}

void Demo2_8::ProcessInsert()
{
    m_bOverwrite = m_bOverwrite ? FALSE : TRUE;
}

void Demo2_8::ProcessChar(WPARAM wParam)
{
    if (wParam == '+')
    {
        ProcessPlus();
        return;
    }
    
    if (wParam == '-')
    {
        ProcessMinus();
        return;
    }

    if (m_bOverwrite)
    {
        Overwrite(wParam);
    }
    else
    {
        WriteOnBack(wParam);
    }

    if (m_uiTextSizeArr[m_CaretPos.row] >= MAX_LINE_SIZE)
    {
        m_CaretPos.row++;
        m_CaretPos.col = m_uiTextSizeArr[m_CaretPos.row];
    }
}

void Demo2_8::ProcessF1()
{
    m_bUpperMode = m_bUpperMode ? FALSE : TRUE;
}

#pragma endregion Demo2_7

#pragma region DEMO2_8

void Demo2_8::ProcessF2()
{
    // TODO : COMPLETE
    m_bPasswordMode = m_bPasswordMode ? FALSE : TRUE;

    m_wstrPasswordArr = m_wstrTextArr;
}

void Demo2_8::ProcessF3()
{
    for (int i = 9; i > 0; i--)
    {
        m_wstrTextArr[i] = std::move(m_wstrTextArr[i - 1]);
        m_uiTextSizeArr[i] = std::move(m_uiTextSizeArr[i - 1]);
    }

    m_wstrTextArr[0].clear();
    m_wstrTextArr[0].resize(MAX_LINE_SIZE, L' ');
    m_uiTextSizeArr[0] = 0;

    m_CaretPos.y = m_uiTextSizeArr[m_CaretPos.x];
}

void Demo2_8::ProcessF4()
{
    m_wstrTextArr[m_CaretPos.x].clear();
    m_wstrTextArr[m_CaretPos.x].resize(MAX_LINE_SIZE, L' ');
    m_uiTextSizeArr[m_CaretPos.x] = 0;

    m_CaretPos.y = m_uiTextSizeArr[m_CaretPos.x];
}

void Demo2_8::ProcessPageUp()
{
    m_bRemoveBlankMode = m_bRemoveBlankMode ? FALSE : TRUE;
}

void Demo2_8::ProcessPageDown()
{
    m_bWrapWordMode = m_bWrapWordMode ? FALSE : TRUE;
}

void Demo2_8::ProcessPlus()
{
    for (auto& wstr : m_wstrTextArr)
    {
        for (wchar_t& ch : wstr)
        {
            if (std::isdigit(ch))
            {
                ch = ((ch - '0' + 1 + 10) % 10) + '0';
            }
        }
    }
}

void Demo2_8::ProcessMinus()
{
    for (auto& wstr : m_wstrTextArr)
    {
        for (wchar_t& ch : wstr)
        {
            if (std::isdigit(ch))
            {
                ch = ((ch - '0' - 1 + 10) % 10) + '0';
            }
        }
    }
}

std::wstring Demo2_8::RemoveBlank(const std::wstring& input)
{
    std::wstring in = input;
    std::wstring res = L"";

    for (const wchar_t& ch : in)
    {
        if (ch != L' ')
        {
            res += ch;
        }
    }

    return res;
}

std::wstring Demo2_8::WrapWord(const std::wstring& input)
{
    wstringstream ss;
    ss.str(input);

    std::wstring word;
    std::wstringstream res;

    while (ss >> word)
    {
        res << L"(" << word << L")";
    }

    return res.str();
}



#pragma endregion DEMO2_8

LRESULT Demo2_8::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    std::shared_ptr<Demo2_8> pDemo = CUR_DEMO(Demo2_8);

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
        pDemo->m_pCaret->Hide(hWnd);
        pDemo->m_pCaret->Destroy();
        PostQuitMessage(0);
        return 0;

    default:
        break;
    }
    
    return DefWindowProc(hWnd, message, wParam, lParam);
}
