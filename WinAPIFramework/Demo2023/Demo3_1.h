#pragma once
#include "../Application.h"

class TextBox;
class Caret;
class GameBoard;

// Tail
//////////////////////////////////////////////////////////////////////////////////////////////

enum TAIL_MOVE_TYPE
{
	TAIL_MOVE_UP = 0,
	TAIL_MOVE_DOWN,
	TAIL_MOVE_LEFT,
	TAIL_MOVE_RIGHT,
	TAIL_MOVE_TRIANGLE,
	TAIL_MOVE_STOP
};

enum TAIL_STATE_TYPE
{
	TAIL_STATE_FOOD = 0,
	TAIL_STATE_FREE,
	TAIL_STATE_FOLLOW_PLAYER,
	TAIL_STATE_FOLLOW_TAIL
};

class Tail3_1
{
public:
	Tail3_1() {}
	~Tail3_1() {}

public:
	BOOL Create(int ID);
	BOOL Draw(HDC hDC);

public:
	void Move();
	void ChangeState(TAIL_STATE_TYPE ty);
	void ChangeStateToFollowTail(int id);

public:
	void SetOffset(POINT pos) { m_Position = pos; }
	void SetSize(SIZE size) { m_Size = size; }

	void AddOffset(POINT pos) { m_Position.x += pos.x; m_Position.y += pos.y; }
	void AddSize(SIZE size) { m_Size.cx += size.cx; m_Size.cy += size.cy; }

	POINT GetOffset() { return m_Position; }

	TAIL_MOVE_TYPE GetMoveType() { return m_MoveType; }
	TAIL_STATE_TYPE GetStateType() { return m_StateType; }

	void SetCollisionGuard(BOOL bGuard) { m_bCollisionGuard = bGuard; }
	BOOL GetCollisionGuard() { return m_bCollisionGuard; }

	void SetFollowID(int ID) { m_FollowID = ID; }
	int GetFollowID() { return m_FollowID; }

	void SetSomeoneFollowMe(BOOL bFollow) { m_bSomeoneFollowMe = bFollow; }
	BOOL GetSomeoneFollowMe() { return m_bSomeoneFollowMe; }

	int GetID() { return m_TailID; }

	std::shared_ptr<Shapes>& GetModel() { return m_pTailModel; }

	void SetColor(COLORREF color) { m_Color = color; }
	COLORREF& GetColor() { return m_Color; }

private:
	std::shared_ptr<Shapes> m_pTailModel = nullptr;
	POINT m_Position = { 0,0 };
	SIZE m_Size = { 1,1 };
	TAIL_MOVE_TYPE m_MoveType = TAIL_MOVE_TYPE::TAIL_MOVE_TRIANGLE;
	TAIL_STATE_TYPE m_StateType = TAIL_STATE_TYPE::TAIL_STATE_FOOD;

	BOOL m_bCollisionGuard = FALSE;
	COLORREF m_Color = RGB(0, 0, 0);

	ULONGLONG m_TriangleMoveTick = 1000;
	ULONGLONG m_PrevTriangleMoveTick = 0;
	int m_TriangleMoveCount = 0;

	int m_TailID = 0;
	int m_FollowID = -1;
	BOOL m_bSomeoneFollowMe = FALSE;
};

// Player
//////////////////////////////////////////////////////////////////////////////////////////////

enum PLAYER_MOVE_DIRECTION
{
	PLAYER_MOVE_UP = 0,
	PLAYER_MOVE_DOWN,
	PLAYER_MOVE_LEFT,
	PLAYER_MOVE_RIGHT
};

class Player3_1
{
public:
	Player3_1() {}
	~Player3_1() {}

public:
	BOOL Create();
	BOOL Draw(HDC hDC);

public:
	void Move();
	void UpdateTailPos();

private:
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

public:
	void Jump();

public:
	void SetOffset(POINT pos) { m_Position = pos; }
	void SetSize(SIZE size) { m_Size = size; }

	void AddOffset(POINT pos) { m_Position.x += pos.x; m_Position.y += pos.y; }
	void AddSize(SIZE size) { m_Size.cx += size.cx; m_Size.cy += size.cy; }

	POINT GetOffset() { return m_Position; }

	void SetMoveDirection(PLAYER_MOVE_DIRECTION dir) { m_MoveDirection = dir; }
	void SetModel(std::shared_ptr<shapes::Ellipse> pModel) { m_pPlayerModel = pModel; }

	void AddTail(std::shared_ptr<class Tail3_1> pTail) { m_pTails.push_back(pTail); }
	void RemoveTail(int ID) { m_pTails.erase(std::remove_if(m_pTails.begin(), m_pTails.end(), [ID](std::shared_ptr<class Tail3_1> p) { return p->GetID() == ID; }), m_pTails.end()); }

public:
	void Inflate();
	void Deflate();

	void ChangePlayerToTail();

private:
	std::shared_ptr<shapes::Ellipse> m_pPlayerModel = nullptr;
	POINT m_Position = { 0,0 };
	SIZE m_Size = { 1,1 };
	PLAYER_MOVE_DIRECTION m_MoveDirection = PLAYER_MOVE_DIRECTION::PLAYER_MOVE_DOWN;

	COLORREF m_Color = RGB(0, 0, 0);

	std::vector<std::shared_ptr<class Tail3_1>> m_pTails = {};

	BOOL m_bJumped = FALSE;
	int m_JumpUpCount = 0;
	int m_JumpDownCount = 0;

};

// Demo
//////////////////////////////////////////////////////////////////////////////////////////////

class Demo3_1 : public Application
{
public:
	Demo3_1() {}
	virtual ~Demo3_1() {}

public:
	virtual BOOL Initialize() override;
	virtual void Update() override;
	virtual void Draw(HDC hDC) override;

	void DrawObstacle(HDC hDC);

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	void OnCreate(HWND hWnd);
	
public:
	void ProcessKeyboard();
	void ProcessMouse();
	void CheckCollision();

public:
	void CreateObstacle(POINT pos);

public:
	std::vector<std::shared_ptr<Tail3_1>>& GetTails() { return m_pTails; }
	std::vector<POINT>& GetObstaclePos() { return m_ObstaclePos; }

private:
	std::shared_ptr<GameBoard> m_pGameBoard = nullptr;
	std::shared_ptr<Player3_1> m_pPlayer = nullptr;
	std::vector<std::shared_ptr<Tail3_1>> m_pTails = {};

	ULONGLONG m_PrevPlayerUpdateTick = 0;
	ULONGLONG m_PlayerUpdateTick = 100;
	
	ULONGLONG m_PrevTailUpdateTick = 0;
	ULONGLONG m_TailUpdateTick = 50;

	ULONGLONG m_PrevCollisionGuardTick = 0;
	ULONGLONG m_TailCollisionGuardTick = 1000;

	BOOL m_bGameStart = FALSE;

	int nTails = 0;

	std::vector<POINT> m_ObstaclePos = {};

};

