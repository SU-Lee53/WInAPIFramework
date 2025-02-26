#include "pch.h"
#include "Dialog.h"

// Modal
////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL ModalDialog::Create(int dialogMacro, DLGPROC m_DialogFunc)
{
	m_dialogMacro = dialogMacro;
	m_dialogFunc = m_DialogFunc;

	return TRUE;
}

void ModalDialog::ShowDialog()
{
	::DialogBox(CUR_HINSTANCE, MAKEINTRESOURCE(m_dialogMacro), CUR_HWND, m_dialogFunc);
}

void ModalDialog::SetControlState(int controlMacro, BOOL bEnable)
{
	HWND controlHwnd = GetDlgItem(m_hDlg, controlMacro);
	::EnableWindow(controlHwnd, bEnable);
}

// Modalless
////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL ModallessDialog::Create(int dialogMacro, DLGPROC m_DialogFunc)
{
	m_dialogMacro = dialogMacro;
	m_dialogFunc = m_DialogFunc;
	m_hDlg = ::CreateDialog(CUR_HINSTANCE, MAKEINTRESOURCE(m_dialogMacro), CUR_HWND, m_DialogFunc);

	return TRUE;
}

void ModallessDialog::ShowDialog()
{
	::ShowWindow(m_hDlg, SW_SHOW);
}

void ModallessDialog::DestroyDialog()
{
	::DestroyWindow(m_hDlg);
}

void ModallessDialog::SetControlState(int controlMacro, BOOL bEnable)
{
	HWND controlHwnd = GetDlgItem(m_hDlg, controlMacro);
	::EnableWindow(controlHwnd, bEnable);
}
