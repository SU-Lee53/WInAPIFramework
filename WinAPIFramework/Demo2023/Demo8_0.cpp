#include "../pch.h"
#include "Demo8_0.h"
#include "../TextBox.h"
#include "../Utils.h"
#include "../Caret.h"
#include "../GameBoard.h"
#include "../resource.h"
#include "../ChildControls.h"
#include "../ChildWindow.h"

using namespace std;
using namespace shapes;

BOOL Demo8_0::Initialize()
{
    m_pProcFunction = WndProc;

    m_AppDesc.wndName = L"Demo7-1";
    m_AppDesc.wndStyle = WS_OVERLAPPEDWINDOW;
    m_AppDesc.backgroundColor = WHITE_BRUSH;
    m_AppDesc.wndIcon = IDI_APPLICATION;
    m_AppDesc.wndCursor = IDC_ARROW;
    m_AppDesc.wndPosition.x = 100;
    m_AppDesc.wndPosition.y = 10;
    m_AppDesc.wndSize.width = 1200;
    m_AppDesc.wndSize.height = 900;
	m_AppDesc.appRunMode = APP_RUN_MODE_WNDPROC;

    m_AppDesc.menuName = IDR_MENU_8_0;

    return 0;
}

void Demo8_0::OnPaint()
{
    PAINTSTRUCT ps = {};
    HDC hDC = ::BeginPaint(CUR_HWND, &ps);

    DrawCoord(hDC);

    ::EndPaint(CUR_HWND, &ps);
}

void Demo8_0::OnCreate(HWND hWnd)
{
    BOOL bResult = TRUE;
    TIMER.Initialize(hWnd);

    if (!bResult) __debugbreak();
}

void Demo8_0::HandleMenu(WORD param)
{
}

void Demo8_0::ProcessKeyboard()
{
}

void Demo8_0::ProcessMouse()
{
}

#define ID_FILEOPEN 100

LRESULT Demo8_0::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    std::shared_ptr<Demo8_0> pDemo = CUR_DEMO(Demo8_0);

    // FILE I/O
    OPENFILENAME OFN;
    OPENFILENAME SFN;
    TCHAR str[150], lpstrFile[150] = L"";
    TCHAR filter[100] = L"소스파일(*.cpp)\0*.cpp\0헤더파일(*.h)\0*.h\0문서파일(*.txt, *.doc)\0*.txt;*.doc\0";

    // FONT
    CHOOSEFONT FONT;
    HFONT hFont, OldFont;
    static LOGFONT LogFont;
    static COLORREF fColor;

    // COLOR
    CHOOSECOLOR COLOR;
    static COLORREF tmp[16], color;

    switch (message)
    {
    case WM_CREATE:
        pDemo->OnCreate(hWnd);
        break;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_FILE_OPEN:
            ::ZeroMemory(&OFN, sizeof(OPENFILENAME));
            OFN.lStructSize = sizeof(OPENFILENAME);
            OFN.hwndOwner = hWnd;
            OFN.lpstrFilter = filter;
            OFN.lpstrFile = lpstrFile;
            OFN.nMaxFile = 256;
            OFN.lpstrInitialDir = L".";

            if (GetOpenFileName(&OFN) != 0)
            {
                wsprintf(str, L"%s 파일을 여시겠습니까?", OFN.lpstrFile);
                MessageBox(hWnd, str, L"열기 선택", MB_OK);
            }
            break;

        case ID_FILE_SAVE:
            ::ZeroMemory(&SFN, sizeof(OPENFILENAME));
            SFN.lStructSize = sizeof(OPENFILENAME);
            SFN.hwndOwner = hWnd;
            SFN.lpstrFilter = filter;
            SFN.lpstrFile = lpstrFile;
            SFN.nMaxFile = 256;
            SFN.lpstrInitialDir = L".";

            if (GetSaveFileName(&SFN) != 0)
            {
                wsprintf(str, L"%s 파일에 저장하시겠습니까?", SFN.lpstrFile);
                MessageBox(hWnd, str, L"저장하기 선택", MB_OK);
            }
            break;

        case ID_FILE_FONT:
            ::ZeroMemory(&FONT, sizeof(CHOOSEFONT));
            FONT.lStructSize = sizeof(CHOOSEFONT);
            FONT.hwndOwner = hWnd;
            FONT.lpLogFont = &LogFont;
            FONT.Flags = CF_EFFECTS | CF_SCREENFONTS;

            if (ChooseFont(&FONT) != 0)
            {
                fColor = FONT.rgbColors;
                InvalidateRect(hWnd, NULL, TRUE);
            }
            break;

        case ID_FILE_COLOR:
            for (int i = 0; i < 16; i++) tmp[i] = RANDOM.GenerateRandomColor();
            
            ::ZeroMemory(&COLOR, sizeof(CHOOSECOLOR));
            COLOR.lStructSize = sizeof(CHOOSECOLOR);
            COLOR.hwndOwner = hWnd;
            COLOR.lpCustColors = tmp;
            COLOR.Flags = CC_FULLOPEN;

            if (ChooseColor(&COLOR) != 0)
            {
                color = COLOR.rgbResult;
                InvalidateRect(hWnd, NULL, TRUE);
            }


        default:
            break;
        }

    case WM_PAINT:
        //pDemo->OnPaint();
    {
        PAINTSTRUCT ps;
        HDC hDC = ::BeginPaint(hWnd, &ps);

        // FONT
        hFont = CreateFontIndirect(&LogFont);
        OldFont = (HFONT)::SelectObject(hDC, hFont);
        ::SetTextColor(hDC, fColor);
        ::TextOut(hDC, 10, 10, L"Hello World", 11);
        ::SelectObject(hDC, OldFont);
        ::DeleteObject(hFont);

        // COLOR
        HBRUSH hBrush = C_SOLID_HBRUSH(color);
        HBRUSH oldBrush = (HBRUSH)::SelectObject(hDC, hBrush);
        ::Ellipse(hDC, 100, 100, 200, 200);
        ::SelectObject(hDC, oldBrush);
        ::DeleteObject(hBrush);
        
        ::EndPaint(hWnd, &ps);

        break;
    }

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
