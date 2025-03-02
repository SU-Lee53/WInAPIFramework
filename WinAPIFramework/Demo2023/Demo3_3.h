#pragma once
#include "../Application.h"

class TextBox;
class Caret;
class GameBoard;

/*
	- 사거리 지나가는 자동차 구현하기
		- 화면에 십자가 형태의 사거리가 있고, 각 도로에 2대의 자동차 (사각형으로 표현)가 다른 속도로 달리고 있다.
			- 즉 화면에는 최소 8대의 자동차가 있다. 아래로 이동하는 차선에 2대, 위로 이동하는 차선에 2대, 왼쪽으로 이동하는 차선에 2대, 오른쪽으로 이동하는 차선에 2대
			- 반대편에 도달하면 자동차는 일부분씩 사라지고, 사라진 부분은 반대편에 나타나면서 계속 진행된다. (다음 페이지 설명)
		- 우측 상단에 상하로 이동하는 자동차 기준의 신호등이 있다. 마우스로 신호등 원 내부를 클릭한다.
			- 빨강: 상하로 이동하는 차들은 서 있다. 좌우로 이동하는 차들은 이동한다.
			- 파랑: 상하로 이동하는 차들은 이동한다. 좌우로 이동하는 차들은 서있다.
			- 노랑: 현재 신호등이 빨강이면 1초 후에 파랑으로, 파랑이면 빨강으로 바뀐다.
		- 키보드 명령
			- +/-: 자동차의 속도 증가/감소
			- a/A: 신호등이 특정시간마다 자동으로 바뀐다/멈춘다. (파랑 - 노랑 - 빨강 - 파랑 - 노랑 - 빨강)
			- q/Q: 프로그램 종료


*/

// TrafficLight
/////////////////////////////////////////////////////////////////////////

enum TRAFFIC_LIGHT_STATE : int
{
	TRAFFIC_LIGHT_STATE_BLUE,
	TRAFFIC_LIGHT_STATE_YELLOW,
	TRAFFIC_LIGHT_STATE_RED,
	TRAFFIC_LIGHT_STATE_CHANGE_AFTER_SECOND
};

class TrafficLight3_3
{
public:
	TrafficLight3_3() {}
	~TrafficLight3_3() {}

public:
	BOOL Create();
	void Update();
	void Draw(HDC hDC);

	void SetState(TRAFFIC_LIGHT_STATE state) { m_State = state; }
	TRAFFIC_LIGHT_STATE GetState() { return m_State; }

	void ChangeMode() { m_bChangeWhenClicked = !m_bChangeWhenClicked; }
	BOOL GetChangeMode() { return m_bChangeWhenClicked; }

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

class Car3_3 : public GameObject
{
public:
	Car3_3() {}
	virtual ~Car3_3() {}

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


class Demo3_3 : public Application
{
public:
	Demo3_3() {}
	virtual ~Demo3_3() {}

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
	void CreateCars();

public:
	void DrawCrossRoad(HDC hDC);

public:
	std::shared_ptr<TrafficLight3_3>& GetTrafficLight() { return m_pTrafficLight; }

public:
	std::shared_ptr<TrafficLight3_3> m_pTrafficLight = nullptr;
	std::vector<std::shared_ptr<Car3_3>> m_pCars = {};

};

