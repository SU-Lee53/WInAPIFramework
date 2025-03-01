#pragma once

class ModalDialog
{
public:
	ModalDialog() {}
	~ModalDialog() {}

public:
	BOOL Create(int dialogMacro, DLGPROC m_DialogFunc = NULL);
	void ShowDialog();

	void SetHandle(HWND hDlg) { m_hDlg = hDlg; }

	void SetControlState(int controlMacro, BOOL bEnable);

public:
	DLGPROC m_dialogFunc = NULL;
	int m_dialogMacro = 0;
	HWND m_hDlg = 0;
};

class ModalessDialog
{
public:
	ModalessDialog() {}
	~ModalessDialog() {}

public:
	BOOL Create(int dialogMacro, DLGPROC m_DialogFunc = NULL);
	void ShowDialog();
	void DestroyDialog();

	void SetControlState(int controlMacro, BOOL bEnable);

	RECT GetDialogSize();

public:
	DLGPROC m_dialogFunc = NULL;
	int m_dialogMacro = 0;
	HWND m_hDlg = 0;
};