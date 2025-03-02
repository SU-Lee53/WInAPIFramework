#pragma once
#include "../Application.h"

class TextBox;
class Caret;
class GameBoard;

/*
	- ��Ÿ� �������� �ڵ��� �����ϱ�
		- ȭ�鿡 ���ڰ� ������ ��Ÿ��� �ְ�, �� ���ο� 2���� �ڵ��� (�簢������ ǥ��)�� �ٸ� �ӵ��� �޸��� �ִ�.
			- �� ȭ�鿡�� �ּ� 8���� �ڵ����� �ִ�. �Ʒ��� �̵��ϴ� ������ 2��, ���� �̵��ϴ� ������ 2��, �������� �̵��ϴ� ������ 2��, ���������� �̵��ϴ� ������ 2��
			- �ݴ��� �����ϸ� �ڵ����� �Ϻκо� �������, ����� �κ��� �ݴ��� ��Ÿ���鼭 ��� ����ȴ�. (���� ������ ����)
		- ���� ��ܿ� ���Ϸ� �̵��ϴ� �ڵ��� ������ ��ȣ���� �ִ�. ���콺�� ��ȣ�� �� ���θ� Ŭ���Ѵ�.
			- ����: ���Ϸ� �̵��ϴ� ������ �� �ִ�. �¿�� �̵��ϴ� ������ �̵��Ѵ�.
			- �Ķ�: ���Ϸ� �̵��ϴ� ������ �̵��Ѵ�. �¿�� �̵��ϴ� ������ ���ִ�.
			- ���: ���� ��ȣ���� �����̸� 1�� �Ŀ� �Ķ�����, �Ķ��̸� �������� �ٲ��.
		- Ű���� ���
			- +/-: �ڵ����� �ӵ� ����/����
			- a/A: ��ȣ���� Ư���ð����� �ڵ����� �ٲ��/�����. (�Ķ� - ��� - ���� - �Ķ� - ��� - ����)
			- q/Q: ���α׷� ����


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

