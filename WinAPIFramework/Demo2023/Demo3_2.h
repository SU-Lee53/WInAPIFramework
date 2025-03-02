#pragma once
#include "../Application.h"

/*
	- ���� ���� ���� �����
		- ȭ���� ��ܿ� 3*10 ���� ������ �ִ�. �������� ȭ�鿡 �� �����ʰ� ���ʿ� ������ �ִ�.
			- �������� �ð��� ���� �¿�� �Դٰ����Ѵ�.
			- ������ ĭ�� ���� ���ڴ� ���� �����ϴ�.
		- ȭ���� �ϴܿ� bar(��)�� �ְ� ���콺�� �̿��Ͽ� �ٸ� �����δ�.
			- �ٴ��� bar(��)�� ���콺�� �����ϰ� �巡���Ͽ� �̵��Ѵ�. (�¿�θ� �̵�)
			- ���콺�� ������ ���� �ڸ��� �̵��Ѵ�.
		- �� ���� ���� �ְ� ���� ��ɾ ������ ���� Ƣ��� �����Ѵ�. ���� �¿��� ���� ���� ������ �ε�ġ�� �̵� ������ �ٲ� �� ��� ƨ���.
			- �Ʒ��� �ٿ� �ε����� �������� �ٲ�� ƨ���.
			- ƨ��� ������ �¿���ϰ� �ƴ϶� �밢�� (�񽺵��� ����)���� �����Ѵ�.
			- �Ʒ� �ʿ��� �ٰ� ���� ��ġ�� ���� �Ʒ��� ������� �� ���� �ٽ� ��Ÿ���� �ٽ� ƨ��� �����Ѵ�.
		- ���� �� ������ �ε�ġ�� �� ������ ���� �ٲ��, �ε�ģ ������ ũ�Ⱑ �۾����� ȭ�鿡�� �������.
			- �ٲ�� ���� �����ϰ� �����Ѵ�.
		- ��� ���߱� ��ɾ ������ (p ��ɾ�) ���� ���� ������ ������ ������ ������ ȭ�鿡 ����Ѵ�.
		- Ű���� ��ɾ�
			- s/S: �� Ƣ��� ����
			- p/P: �������� ��� ����/�ٽ� ����
			- +/- �Է�: ���� �̵� �ӵ��� �þ��.
			- n/N: ���� ����
			- q/Q: ���α׷� ����

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

