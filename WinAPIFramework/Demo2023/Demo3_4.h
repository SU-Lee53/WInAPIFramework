#pragma once
#include "../Application.h"

class TextBox;
class Caret;
class GameBoard;

/*
	- ��Ʈ����
		- 12X6 ĭ�� ���带 �׸���. (���� ũ�� ���� ����)
		- ������ �������� �簢����
			- ����: 5����
			- ���: �簢�� 1��, �Ǵ� �簢�� 2��, �Ǵ� �簢�� 3�� (�簢������ ���� �� �Ǵ� �ٸ� ��)
		- ���� ���� �簢���� 3�� �̻� �����Ǹ� �簢���� ������.
			- ���� �Ǵ� ���η� ���� ���� �簢���� 3�� �̻� �����Ǹ� �簢�� ����
			- �簢���� ���� �� �Ʒ�ĭ�� ��� ���� �簢������ �Ʒ��� �����´�.
		- Ű���� ���
			- ȭ��ǥ: �簢���� �¿� ���� �̵�. �Ʒ��� �̵��� �ӵ��� ������ �Ѵ�.
			- ����Ű: �簢�� ȸ��
*/

enum RECT_OBJ_TYPE
{
	RECT_OBJ_ONE = 0,
	RECT_OBJ_TWO_V,
	RECT_OBJ_TWO_H,
	RECT_OBJ_THREE_V,
	RECT_OBJ_THREE_H,
	RECT_OBJ_NONE
};

enum GAME_STATE
{
	GAME_STATE_READY_TO_DOWN = 0,	// �簢���� �����ϰ� State ��ȯ
	GAME_STATE_DOWN,				// �簢�� ������
	GAME_STATE_DOWN_DONE			// �簢�� �����ϰ� ���� �ѹ� ����
};

class Demo3_4 : public Application
{
public:
	Demo3_4() {}
	virtual ~Demo3_4() {}

public:
	virtual BOOL Initialize() override;
	virtual void Update() override;
	virtual void Draw(HDC hDC) override;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	void OnCreate(HWND hWnd);
	
public:
	void ProcessKeyboard();
	void ProcessMouse();

public:
	void CreateRect();
	void DownRect();
	void CheckBoard();

	BOOL CheckCanGoDown();

public:
	void MoveLeft();
	void MoveRight();

public:
	void ClearCurrentPos();
	void FillCurrentPos();

private:
	std::shared_ptr<GameBoard> m_pBoard = nullptr;
	std::array<COLORREF, 5> m_Colors = {
		RGB(255,0,0),
		RGB(0,255,0),
		RGB(0,0,255),
		RGB(255,255,0),
		RGB(0,255,255)
	};

	GAME_STATE m_CurGameState = GAME_STATE_READY_TO_DOWN;

	RECT_OBJ_TYPE m_CurRect;
	COLORREF m_CurColor = RGB(255, 255, 255);
	POINT m_CurPos = { 0,0 };
	// - �������� �簢���� ����
	// - 2��¥���� ���
	//	- ���� : ���� �簢��
	//	- ���� : ���� �簢��
	// - 3��¥���� ���
	//	- ���� : ���� ���� �簢��
	//	- ���� : ���� ���� �簢��


	ULONGLONG m_ullPrevUpdateTick = 0;
	ULONGLONG m_ullUpdateTick = 1000;

};

