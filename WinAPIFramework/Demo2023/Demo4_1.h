#pragma once
#include "../Application.h"

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

class Brick_4_1 : public GameObject
{
public:
	Brick_4_1() {}
	virtual ~Brick_4_1() {}

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

class Bar_4_1 : public GameObject
{
public:
	Bar_4_1() {}
	virtual ~Bar_4_1() {}

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

class Ball_4_1 : public GameObject
{
public:
	Ball_4_1() {}
	virtual ~Ball_4_1() {}

public:
	virtual BOOL Create() override;
	virtual void Update() override;
	virtual void Draw(HDC hDC) override;
	virtual void HandleCollision(const std::string& otherName) override;

	void SetMove(BALL_MOVE move) { m_ballMove = move; }

	void SetBallSpeed(int speed) { m_ballSpeed = speed; }

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
	int m_ballSpeed = 5;

};


class Demo4_1 : public Application
{
public:
	Demo4_1() {}
	virtual ~Demo4_1() {}

public:
	virtual BOOL Initialize() override;
	virtual void Update() override;
	virtual void Draw(HDC hDC) override;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	void OnCreate(HWND hWnd);
	void HandleMenu(WORD param);
	
public:
	void ProcessKeyboard();
	void ProcessMouse();

public:
	void SetGame();
	void CheckCollision();
	void CheckGameStatus();
	void ResetBricks();


public:
	std::shared_ptr<Ball_4_1> m_pBall = nullptr;
	std::vector<std::shared_ptr<Brick_4_1>> m_pBricks = {};
	std::shared_ptr<Bar_4_1> m_pBar = nullptr;

	BOOL m_bBallMove = FALSE;
	BOOL m_bGameRun = FALSE;

	POINT m_OriginBarPos = POINT{ 400, 820 };
	POINT m_OriginBallPos = POINT{ 400, 800 };
	BOOL m_bDrag = FALSE;

	int m_nBrickRows = 3;
	int m_nBrickCols = 10;

public:
	const static int BRICK_WIDTH = 60;
	const static int BRICK_HEIGHT = 30;
	const static int BRICK_BEGIN_OFFSET_X = 100;
	const static int BRICK_BEGIN_OFFSET_Y = 50;

	ULONGLONG m_ullUpdateTick = 17;
	ULONGLONG m_ullPrevUpdateTick = 0;

};

