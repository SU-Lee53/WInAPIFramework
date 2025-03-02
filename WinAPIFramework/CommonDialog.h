#pragma once

enum COMMON_DIALOG_TYPE
{
	COMMON_DIALOG_TYPE_FILE = 0,
	COMMON_DIALOG_TYPE_FONT,
	COMMON_DIALOG_TYPE_COLOR
};

class CommonDialog
{
	DECLARE_SINGLE(CommonDialog)

public:
	BOOL Open(COMMON_DIALOG_TYPE type, void* rpDiagStruct);
	BOOL Close();



};

