#pragma once
#include "../Application.h"

/*
	- 벽돌 깨기 게임 만들기
		- 화면의 상단에 3*10 개의 벽돌이 있다. 벽돌들은 화면에 꽉 차지않고 양쪽에 공간이 있다.
			- 벽돌들은 시간에 따라 좌우로 왔다갔다한다.
			- 벽돌의 칸과 줄의 숫자는 변경 가능하다.
		- 화면의 하단에 bar(바)가 있고 마우스를 이용하여 바를 움직인다.
			- 바닥의 bar(바)를 마우스로 선택하고 드래그하여 이동한다. (좌우로만 이동)
			- 마우스를 놓으면 원래 자리로 이동한다.
		- 바 위에 공이 있고 시작 명령어를 누르면 공이 튀기기 시작한다. 공은 좌우의 벽과 위의 벽돌에 부딪치면 이동 방향을 바꾼 후 계속 튕긴다.
			- 아래의 바에 부딪히면 위쪽으로 바뀌고 튕긴다.
			- 튕기는 방향은 좌우상하가 아니라 대각선 (비스듬한 방향)으로 설정한다.
			- 아래 쪽에서 바가 공을 놓치면 공은 아래로 사라지고 바 위에 다시 나타나서 다시 튕기기 시작한다.
		- 공이 한 벽돌에 부딪치면 그 벽돌의 색이 바뀌며, 부딪친 벽돌은 크기가 작아지며 화면에서 사라진다.
			- 바뀌는 색은 랜덤하게 설정한다.
		- 잠시 멈추기 명령어를 누르면 (p 명령어) 색이 변한 벽돌의 개수와 없어진 개수를 화면에 출력한다.
		- 키보드 명령어
			- s/S: 공 튀기기 시작
			- p/P: 움직임이 잠시 멈춤/다시 시작
			- +/- 입력: 공의 이동 속도가 늘어난다.
			- n/N: 게임 리셋
			- q/Q: 프로그램 종료

*/

class TextBox;
class Caret;
class GameBoard;

// Brick
///////////////////////////////////////////////////////////////////////////////

enum BRICK_STATE
{
	BRICK_STATE_MOVE_LEFT,
	BRICK_STATE_MOVE_RIGHT,
	BRICK_STATE_DESTROY,
	BRICK_STATE_WAIT_FOR_ERASE
};

class Brick_3_2 : public GameObject
{
public:
	Brick_3_2() {}
	virtual ~Brick_3_2() {}

public:
	virtual BOOL Create() override;
	virtual void Update() override;
	virtual void Draw(HDC hDC) override;
	virtual void HandleCollision(const std::string& otherName) override;

	void SetOrigin() { m_Origin = m_Position; }
	void SetState(BRICK_STATE s) { m_State = s; }

public:
	BRICK_STATE m_State = BRICK_STATE_MOVE_LEFT;
	POINT m_Origin = POINT{ 0,0 };


};

// Bar
///////////////////////////////////////////////////////////////////////////////

class Bar_3_2 : public GameObject
{
public:
	Bar_3_2() {}
	virtual ~Bar_3_2() {}

public:
	virtual BOOL Create() override;
	virtual void Update() override;
	virtual void Draw(HDC hDC) override;
	virtual void HandleCollision(const std::string& otherName) override;

};

// Ball
///////////////////////////////////////////////////////////////////////////////

enum BALL_MOVE
{
	BALL_MOVE_RIGHT_TOP,
	BALL_MOVE_RIGHT_BOTTOM,
	BALL_MOVE_LEFT_TOP,
	BALL_MOVE_LEFT_BOTTOM
};

class Ball_3_2 : public GameObject
{
public:
	Ball_3_2() {}
	virtual ~Ball_3_2() {}

public:
	virtual BOOL Create() override;
	virtual void Update() override;
	virtual void Draw(HDC hDC) override;
	virtual void HandleCollision(const std::string& otherName) override;

	void SetMove(BALL_MOVE move) { m_ballMove = move; }

	void IncreaseBallSpeed()
	{
		m_ballSpeed++;
		if (m_ballSpeed > 10)
		{
			m_ballSpeed = 10;
		}
	}

	void DecreaseBallSpeed()
	{
		m_ballSpeed--;
		if (m_ballSpeed < 1)
		{
			m_ballSpeed = 1;
		}
	}

public:
	BALL_MOVE m_ballMove = BALL_MOVE_RIGHT_TOP;
	int m_ballSpeed = 1;

};


class Demo3_2 : public Application
{
public:
	Demo3_2() {}
	virtual ~Demo3_2() {}

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
	void SetGame();
	void CheckCollision();
	void CheckGameStatus();

public:
	std::shared_ptr<Ball_3_2> m_pBall = nullptr;
	std::vector<std::shared_ptr<Brick_3_2>> m_pBricks = {};
	std::shared_ptr<Bar_3_2> m_pBar = nullptr;

	BOOL m_bBallMove = FALSE;
	BOOL m_bGameRun = FALSE;

	POINT m_OriginBarPos = POINT{ 400, 820 };
	POINT m_OriginBallPos = POINT{ 400, 800 };
	BOOL m_bDrag = FALSE;

public:
	const static int BRICK_WIDTH = 60;
	const static int BRICK_HEIGHT = 30;
	const static int BRICK_BEGIN_OFFSET_X = 100;
	const static int BRICK_BEGIN_OFFSET_Y = 50;
};

