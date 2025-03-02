#include "../pch.h"
#include "Demo8_1.h"
#include "../TextBox.h"
#include "../Utils.h"
#include "../Caret.h"
#include <filesystem>

using namespace std;

BOOL Demo8_1::Initialize()
{
    m_pProcFunction = WndProc;

    m_AppDesc.wndName = L"Demo2-7";
    m_AppDesc.wndStyle = WS_OVERLAPPEDWINDOW;
    m_AppDesc.backgroundColor = WHITE_BRUSH;
    m_AppDesc.wndIcon = IDI_APPLICATION;
    m_AppDesc.wndCursor = IDC_ARROW;
    m_AppDesc.wndPosition.x = 100;
    m_AppDesc.wndPosition.y = 50;
    m_AppDesc.wndSize.width = 1200;
    m_AppDesc.wndSize.height = 800;
    m_AppDesc.menuName = IDR_MENU_8_1;

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

void Demo8_1::OnCreate(HWND hWnd)
{
    BOOL bResult = TRUE;
    m_pCaret->Create(hWnd, NULL, 5, 15);
    m_pCaret->Show(hWnd);

    if (!bResult) __debugbreak();
}

void Demo8_1::OnPaint()
{
    HDC hDC = BeginAppPaint();
    if (!hDC)
        __debugbreak();

    SIZE size = TextBox::GetTextExtent(hDC, m_wstrTextArr[m_CaretPos.row].substr(0, m_CaretPos.col));

    for (int i = 0; i < 10; i++)
    {
        TextBox::DrawFormattedString(hDC, { m_Offset.x, (ULONG)((size.cy * i) + m_Offset.y) }, m_wstrTextArr[i].c_str());
    }

    // 캐럿 위치의 계산
    m_pCaret->SetPos(size.cx + m_Offset.x + 1, (size.cy * m_CaretPos.row) + m_Offset.y);

    // 입력 모드
    std::wstring wstrInputMode = m_bOverwrite ? L"Overwrite" : L"Add";
    TextBox::DrawFormattedString(hDC, { 600, 700 }, wstrInputMode.c_str());


    if (!EndAppPaint())
        __debugbreak;
}

void Demo8_1::OnChar(HWND hWnd, WPARAM wParam, LPARAM lParam)
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

void Demo8_1::OnKeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
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

    }

}

void Demo8_1::WriteOnBack(WPARAM wParam)
{
    wchar_t in = wParam;
    in = m_bUpperMode ? std::toupper(in) : std::tolower(in);

    wstring rep(1, in);

    if (m_uiTextSizeArr[m_CaretPos.x] < MAX_LINE_SIZE)
    {
        m_wstrTextArr[m_CaretPos.row].insert(m_CaretPos.col++, rep);
        m_uiTextSizeArr[m_CaretPos.row]++;
    }
}

void Demo8_1::Overwrite(WPARAM wParam)
{
    wchar_t in = wParam;
    in = m_bUpperMode ? std::toupper(in) : std::tolower(in);
    if(m_wstrTextArr[m_CaretPos.row][m_CaretPos.col] != L' ')
    {
        m_wstrTextArr[m_CaretPos.row][m_CaretPos.col++] = in;
    }
    else
    {
        wstring rep(1, in);

        if (m_uiTextSizeArr[m_CaretPos.x] < MAX_LINE_SIZE)
        {
            m_wstrTextArr[m_CaretPos.row].insert(m_CaretPos.col++, rep);
            m_uiTextSizeArr[m_CaretPos.row]++;
        }
    }

}

void Demo8_1::ProcessEnter()
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

void Demo8_1::ProcessBackSpace()
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

void Demo8_1::ProcessEscape()
{
    for (int i = 0; i < 10; i++)
    {
        m_wstrTextArr[i].clear();
        m_wstrTextArr[i].resize((size_t)MAX_LINE_SIZE, L' ');
        m_uiTextSizeArr[i] = 0;
    }

    m_CaretPos = { 0,0 };
}

void Demo8_1::ProcessTab()
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

void Demo8_1::ProcessArrow(WPARAM wParam)
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

void Demo8_1::ProcessDelete()
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

void Demo8_1::ProcessHome()
{
    m_CaretPos.y = 0;
    m_bOverwrite = TRUE;
}

void Demo8_1::ProcessEnd()
{
    m_CaretPos.y = m_uiTextSizeArr[m_CaretPos.x];
    if (m_CaretPos.y >= MAX_LINE_SIZE)
    {
        m_CaretPos.x++;
        m_CaretPos.y = 0;
        m_bOverwrite = TRUE;
    }
}

void Demo8_1::ProcessInsert()
{
    m_bOverwrite = m_bOverwrite ? FALSE : TRUE;
}

void Demo8_1::ProcessChar(WPARAM wParam)
{
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

void Demo8_1::ProcessF1()
{
    m_bUpperMode = m_bUpperMode ? FALSE : TRUE;
}

BOOL Demo8_1::Save(LPTSTR filePath)
{
    HANDLE hFile = ::CreateFile(filePath, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 0, 0);
    //::WriteFile(hFile, )

    for (int i = 0; i < 10; i++)
    {
        UINT uiTextLength = m_uiTextSizeArr[i];
        
        DWORD bytesWritten = 0;
        TCHAR savestr[100];

        ::WriteFile(hFile, &uiTextLength, sizeof(UINT), &bytesWritten, NULL);
        ::WriteFile(hFile, m_wstrTextArr[i].c_str(), uiTextLength * sizeof(TCHAR), &bytesWritten, NULL);
    }

    ::CloseHandle(hFile);

    return 0;
}

BOOL Demo8_1::Load(LPTSTR filePath)
{
    return 0;
}

LRESULT Demo8_1::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    std::shared_ptr<Demo8_1> pDemo = CUR_DEMO(Demo8_1);

    switch (message)
    {
    case WM_CREATE:
        pDemo->OnCreate(hWnd);
        break;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_FILE_OPEN:
            ::ZeroMemory(&pDemo->m_loadStruct, sizeof(OPENFILENAME));
            pDemo->m_loadStruct.lStructSize = sizeof(OPENFILENAME);
            pDemo->m_loadStruct.hwndOwner = hWnd;
            pDemo->m_loadStruct.lpstrFilter = pDemo->m_wstrFilter;
            pDemo->m_loadStruct.lpstrFile = pDemo->m_wstrFile.data();
            pDemo->m_loadStruct.nMaxFile = 256;
            pDemo->m_loadStruct.lpstrInitialDir = L".";

            if (GetOpenFileName(&pDemo->m_loadStruct) != 0)
            {
                TCHAR str[100];
                ::wsprintf(str, L"Open %s ?", pDemo->m_loadStruct.lpstrFile);
                ::MessageBox(hWnd, str, L"Load", MB_OK);
                pDemo->Load(pDemo->m_loadStruct.lpstrFile);
            }

            break;

        case ID_FILE_SAVE:
            ::ZeroMemory(&pDemo->m_saveStruct, sizeof(OPENFILENAME));
            pDemo->m_saveStruct.lStructSize = sizeof(OPENFILENAME);
            pDemo->m_saveStruct.hwndOwner = hWnd;
            pDemo->m_saveStruct.lpstrFilter = pDemo->m_wstrFilter;
            pDemo->m_saveStruct.lpstrFile = pDemo->m_wstrFile.data();
            pDemo->m_saveStruct.nMaxFile = 256;
            pDemo->m_saveStruct.lpstrInitialDir = L".";

            if (GetSaveFileName(&pDemo->m_saveStruct) != 0)
            {
                TCHAR str[100];
                ::wsprintf(str, L"Save %s ?", pDemo->m_saveStruct.lpstrFile);
                ::MessageBox(hWnd, str, L"Save", MB_OK);
                pDemo->Save(pDemo->m_saveStruct.lpstrFile);
            }

            break;

        default:
            break;
        }

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
