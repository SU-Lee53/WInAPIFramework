#pragma once
#include "../Application.h"

class TextBox;
class Caret;
class GameBoard;

/*
	- 렉트리스
		- 12X6 칸의 보드를 그린다. (보드 크기 변경 가능)
		- 위에서 내려오는 사각형은
			- 색상: 5종류
			- 모양: 사각형 1개, 또는 사각형 2개, 또는 사각형 3개 (사각형들은 같은 색 또는 다른 색)
		- 같은 색의 사각형이 3개 이상 나열되면 사각형이 터진다.
			- 가로 또는 세로로 같은 색의 사각형이 3개 이상 나열되면 사각형 삭제
			- 사각형들 삭제 후 아래칸이 비면 위의 사각형들은 아래로 내려온다.
		- 키보드 명령
			- 화살표: 사각형을 좌우 상하 이동. 아래로 이동은 속도를 빠르게 한다.
			- 엔터키: 사각형 회전
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
	GAME_STATE_READY_TO_DOWN = 0,	// 사각형을 생성하고 State 전환
	GAME_STATE_DOWN,				// 사각형 내려옴
	GAME_STATE_DOWN_DONE			// 사각형 고정하고 보드 한번 점검
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
	// - 내려오는 사각형의 원점
	// - 2개짜리의 경우
	//	- 가로 : 왼쪽 사각형
	//	- 세로 : 위쪽 사각형
	// - 3개짜리의 경우
	//	- 가로 : 가장 왼쪽 사각형
	//	- 세로 : 가장 위쪽 사각형


	ULONGLONG m_ullPrevUpdateTick = 0;
	ULONGLONG m_ullUpdateTick = 1000;

};

