#include "../pch.h"
#include "Demo6_2.h"
#include "../TextBox.h"
#include "../Utils.h"
#include "../Caret.h"
#include "../GameBoard.h"
#include "../resource.h"

using namespace std;
using namespace shapes;

BOOL Demo6_2::Initialize()
{
    m_pProcFunction = WndProc;

    m_AppDesc.wndName = L"Demo6-1";
    m_AppDesc.wndStyle = WS_OVERLAPPEDWINDOW;
    m_AppDesc.backgroundColor = WHITE_BRUSH;
    m_AppDesc.wndIcon = IDI_APPLICATION;
    m_AppDesc.wndCursor = IDC_ARROW;
    m_AppDesc.wndPosition.x = 100;
    m_AppDesc.wndPosition.y = 10;
    m_AppDesc.wndSize.width = 1200;
    m_AppDesc.wndSize.height = 900;
	m_AppDesc.appRunMode = APP_RUN_MODE_GAME_LOOP;

    // 메뉴 설정
    //m_AppDesc.menuName = IDR_MENU_5_2;

    return 0;
}

void Demo6_2::OnCreate(HWND hWnd)
{
    BOOL bResult = TRUE;
    TIMER.Initialize(hWnd);

    m_pCalc = make_shared<Calculator62>();
    m_pCalc->Create(IDD_DIALOG_6_2);
    m_pCalc->Show();

    if (!bResult) __debugbreak();
}

void Demo6_2::HandleMenu(WORD param)
{
}

void Demo6_2::Update()
{
    ProcessKeyboard();
    ProcessMouse();

    m_pCalc->Update();

}

void Demo6_2::Draw(HDC hDC)
{
    DrawCoord(hDC);
}

void Demo6_2::ProcessKeyboard()
{
}

void Demo6_2::ProcessMouse()
{
}

LRESULT Demo6_2::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    std::shared_ptr<Demo6_2> pDemo = CUR_DEMO(Demo6_2);

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

LONGLONG Demo6_2::DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    std::shared_ptr<Demo6_2> pDemo = CUR_DEMO(Demo6_2);

    switch (message)
    {
    case WM_INITDIALOG:
        CheckRadioButton(hDlg, IDC_RADIO1, IDC_RADIO4, IDC_RADIO1);
        break;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            break;

        case IDCANCEL:
            EndDialog(hDlg, 0);
            break;

        default:
            break;
        }
        break;

    case WM_CLOSE:
        EndDialog(hDlg, 0);
        break;


    }

    return 0;
}

// Calc
///////////////////////////////////////////////////////////////////////////////

void Calculator62::Create(int diagMacro)
{
    m_pDialogBox = make_shared<ModalessDialog>();
    m_pDialogBox->Create(diagMacro, CalcProc);
    
}

void Calculator62::Show()
{
    m_pDialogBox->ShowDialog();
}

void Calculator62::Update()
{
}

void Calculator62::Draw()
{
}

void Calculator62::ProcessR()
{
}

void Calculator62::ProcessCE()
{
}

void Calculator62::ProcessC()
{
}

void Calculator62::ProcessBinary()
{
}

void Calculator62::ProcessInverse()
{
}

void Calculator62::ProcessMul10()
{
}

void Calculator62::ProcessPow10()
{
}

void Calculator62::ProcessDel()
{
}

LONGLONG Calculator62::CalcProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    std::shared_ptr<Calculator62> pCalc = CUR_DEMO(Demo6_2)->GetCalculator();

    TCHAR editText[100];
    TCHAR add[100];

    switch (msg)
    {
    case WM_INITDIALOG:
        break;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON0:
            GetDlgItemText(hDlg, IDC_EDIT1, editText, 100);
            *add = L'0';
            lstrcat(editText, add);
            SetDlgItemText(hDlg, IDC_EDIT1, editText);

            break;
        case IDC_BUTTON1:
            pCalc->AddText(L'1');
            SetDlgItemText(hDlg, IDC_EDIT1, pCalc->m_wstrCalcText.c_str());
            break;
        case IDC_BUTTON2:
            pCalc->AddText(L'2');
            SetDlgItemText(hDlg, IDC_EDIT1, pCalc->m_wstrCalcText.c_str());
            break;
        case IDC_BUTTON3:
            pCalc->AddText(L'3');
            SetDlgItemText(hDlg, IDC_EDIT1, pCalc->m_wstrCalcText.c_str());
            break;
        case IDC_BUTTON4:
            pCalc->AddText(L'4');
            SetDlgItemText(hDlg, IDC_EDIT1, pCalc->m_wstrCalcText.c_str());
            break;
        case IDC_BUTTON5:
            pCalc->AddText(L'5');
            SetDlgItemText(hDlg, IDC_EDIT1, pCalc->m_wstrCalcText.c_str());
            break;
        case IDC_BUTTON6:
            pCalc->AddText(L'6');
            SetDlgItemText(hDlg, IDC_EDIT1, pCalc->m_wstrCalcText.c_str());
            break;
        case IDC_BUTTON7:
            pCalc->AddText(L'7');
            SetDlgItemText(hDlg, IDC_EDIT1, pCalc->m_wstrCalcText.c_str());
            break;
        case IDC_BUTTON8:
            pCalc->AddText(L'8');
            SetDlgItemText(hDlg, IDC_EDIT1, pCalc->m_wstrCalcText.c_str());
            break;
        case IDC_BUTTON9:
            pCalc->AddText(L'9');
            SetDlgItemText(hDlg, IDC_EDIT1, pCalc->m_wstrCalcText.c_str());
            break;
        case IDC_BUTTON_SUM:
            break;
        case IDC_BUTTON_SUB:
            break;
        case IDC_BUTTON_MUL:
            break;
        case IDC_BUTTON_DIV:
            break;
        case IDC_BUTTON_X10:
            break;
        case IDC_BUTTON_POW:
            break;
        case IDC_BUTTON_INV:
            break;
        case IDC_BUTTON_BIN:
            break;
        case IDC_BUTTON_C:
            break;
        case IDC_BUTTON_CE:
            break;
        case IDC_BUTTON_EQ:
            break;
        case IDC_BUTTON_DEL:
            break;
        case IDC_BUTTON_FIN:
            break;

        default:
            break;
        }
        break;

    case WM_CLOSE:
        EndDialog(hDlg, 0);
        break;


    }

    return 0;
}
