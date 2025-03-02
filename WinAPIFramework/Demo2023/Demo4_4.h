#pragma once
#include "../Application.h"

class TextBox;
class Caret;
class GameBoard;

// TrafficLight
/////////////////////////////////////////////////////////////////////////

enum TRAFFIC_LIGHT_STATE : int
{
	TRAFFIC_LIGHT_STATE_BLUE,
	TRAFFIC_LIGHT_STATE_YELLOW,
	TRAFFIC_LIGHT_STATE_RED,
	TRAFFIC_LIGHT_STATE_CHANGE_AFTER_SECOND
};

class TrafficLight4_4
{
public:
	TrafficLight4_4() {}
	~TrafficLight4_4() {}

public:
	BOOL Create();
	void Update();
	void Draw(HDC hDC);

	void SetState(TRAFFIC_LIGHT_STATE state) { m_State = state; }
	TRAFFIC_LIGHT_STATE GetState() { return m_State; }

	void ChangeMode() { m_bChangeWhenClicked = !m_bChangeWhenClicked; }
	BOOL GetMode() { return m_bChangeWhenClicked; }
	void SetMode(BOOL mode) { m_bChangeWhenClicked = mode; }

	void SetPrevTick(ULONGLONG tick) { m_ullPrevChangedTick = tick; }

private:
	std::shared_ptr<shapes::Rectangle> m_pLightFrame = nullptr;
	std::shared_ptr<shapes::Ellipse> m_pRedLight = nullptr;
	std::shared_ptr<shapes::Ellipse> m_pYellowLight = nullptr;
	std::shared_ptr<shapes::Ellipse> m_pBlueLight = nullptr;

	TRAFFIC_LIGHT_STATE m_State = TRAFFIC_LIGHT_STATE_RED;
	TRAFFIC_LIGHT_STATE m_TargetState = TRAFFIC_LIGHT_STATE_RED;

	BOOL m_bChangeWhenClicked = FALSE;

	ULONGLONG m_ullPrevChangedTick = 0;
	ULONGLONG m_ullYellowLightSettedTick = 0;

};

// Car
/////////////////////////////////////////////////////////////////////////

enum CAR_MOVE_TYPE
{
	CAR_MOVE_UP,
	CAR_MOVE_DOWN,
	CAR_MOVE_LEFT,
	CAR_MOVE_RIGHT
};

class Car4_4 : public GameObject
{
public:
	Car4_4() {}
	virtual ~Car4_4() {}

public:
	BOOL Create() override;
	void Update() override;
	void Draw(HDC hDC) override;
	void HandleCollision(const std::string& otherName) override;

	void SetMoveType(CAR_MOVE_TYPE type) { m_MoveType = type; }

	CAR_MOVE_TYPE GetMoveType() { return m_MoveType; }
	void AddSpeed(int add)
	{
		m_CarSpeed += add;
		if (m_CarSpeed > 10)
		{
			m_CarSpeed = 10;
		}
		else if (m_CarSpeed < 1)
		{
			m_CarSpeed = 1;
		}
	}

private:
	CAR_MOVE_TYPE m_MoveType = CAR_MOVE_UP;
	int m_CarSpeed = 1;

	BOOL m_bIsOut = FALSE;

	POINT m_CarSizeUpDown = { 60, 120 };
	POINT m_CarSizeLeftRight = { 120, 60 };

};

enum GAME_MODE
{
	GAME_MODE_UPDOWN_ONLY,
	GAME_MODE_LEFTRIGHT_ONLY,
	GAME_MODE_ALL,
	GAME_MODE_WALK_ACROSS
};

class Demo4_4 : public Application
{
public:
	Demo4_4() {}
	virtual ~Demo4_4() {}

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
	void CreateCars();

public:
	void DrawCrossRoad(HDC hDC);

public:
	std::shared_ptr<TrafficLight4_4>& GetTrafficLight() { return m_pTrafficLight; }

public:
	std::shared_ptr<TrafficLight4_4> m_pTrafficLight = nullptr;
	std::vector<std::shared_ptr<Car4_4>> m_pCars = {};

public:
	BOOL m_bGameBegin = FALSE;
	GAME_MODE m_curGameMode = GAME_MODE_ALL;

public:
	void UpdateHuman();
	void DrawHuman(HDC hDC);

	// Demo4_4 에서 추가된 길건너는 사람
	std::shared_ptr<shapes::Ellipse> m_pHuman = nullptr;
	std::array<POINT, 4> m_targetPos =
	{
		POINT{450, 550},	// LB
		POINT{750, 550},	// RB
		POINT{450, 250},	// LT
		POINT{750, 250}		// RT
	};

	BOOL m_bBeginCross = FALSE;	// 메뉴에서 건너기를 하면 TRUE 시작하면 FALSE 로 내림
	BOOL m_bCrossing = FALSE;	// 건너는중 -> m_targetPos 에 도달하면 끝
	int m_currentPosIndex = 0;
	int m_targetPosIndex = 0;
	int m_crossingProgress = 0;


private:
	ULONGLONG m_ullPrevUpdateTick = 17;
	ULONGLONG m_ullUpdateTick = 1000;

};

