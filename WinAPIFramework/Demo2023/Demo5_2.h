#pragma once
#include "../Application.h"

// 때려침 : 시간없음

class TextBox;
class Caret;
class GameBoard;
class Bitmap;

// Puzzle
///////////////////////////////////////////////////////////////////////////////////////

enum PUZZLE_STATE
{
	PUZZLE_STATE_IDLE,
	PUZZLE_STATE_MOVE_LEFT,
	PUZZLE_STATE_MOVE_RIGHT,
	PUZZLE_STATE_MOVE_UP,
	PUZZLE_STATE_MOVE_DOWN
};

class Puzzle5_2
{
public:
	Puzzle5_2() {}
	~Puzzle5_2() {}

public:
	void Create(int width, int height);
	void Update();
	void Draw(HDC hDC);

public:
	void ReDivide(int row, int col);
	void Shuffle();
	void PushBitmapToDrawVector();

public:
	void SetImage(int index);

	void SetState(PUZZLE_STATE state) { m_State = state; }
	void SetBeginMove() { m_bMove = TRUE; }

	PUZZLE_STATE GetState(PUZZLE_STATE state) { return m_State; }
	BOOL IsMoving() { return m_bMoving; }
private:
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	BOOL IsMoveComplete();

private:
	std::array<TiledBitmap, 2> m_Tiled = {};
	std::vector<int> m_printSequence = {};
	int m_blankedTiled = 0;
	POS m_currentBlankedPos = { 2,2 };
	std::vector<BitmapRect> m_Bitmaps = {};

	PUZZLE_STATE m_State = PUZZLE_STATE_IDLE;
	BOOL m_bMove = FALSE;
	BOOL m_bMoving = FALSE;

	int m_Selected = 0;
	int m_divRow = 3;
	int m_divCol = 3;

	int m_moveSpeed = 10;
	LPRECT m_moveTarget = NULL;
	RECT m_moveEndRect = {};
	POS m_targetPos = {};

};



class Demo5_2 : public Application
{
public:
	Demo5_2() {}
	virtual ~Demo5_2() {}

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
	void ResetGame();
	void Divide(int row, int col);

private:
	std::shared_ptr<Puzzle5_2> m_pPuzzle = nullptr;

	BOOL m_bGameStart = TRUE;
	BOOL m_bDrag = FALSE;
	POINT m_DragStartedPos = {};
};

