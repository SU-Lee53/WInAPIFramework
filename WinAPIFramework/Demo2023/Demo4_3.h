#pragma once
#include "../Application.h"

class TextBox;
class Caret;
class GameBoard;

// MiniCircle
///////////////////////////////////////////////////////////////////////

enum MINI_CIRCLE_STATE
{
	MINI_CIRCLE_STATE_CW,
	MINI_CIRCLE_STATE_CCW,
	MINI_CIRCLE_STATE_STOP
};

class MiniCircle4_3 : public GameObject
{
public:
	MiniCircle4_3() {}
	virtual ~MiniCircle4_3() {}

public:
	BOOL Create(std::shared_ptr<GameObject> main);
	virtual BOOL Create() override { __debugbreak(); return FALSE; }
	virtual void Update() override;
	virtual void Draw(HDC hDC) override;
	virtual void HandleCollision(const std::string& otherName) override;

public:
	void SetState(MINI_CIRCLE_STATE state) 
	{
		if (state == MINI_CIRCLE_STATE_STOP)
		{
			if (m_curState == MINI_CIRCLE_STATE_STOP)
			{
				m_curState = m_beforeState;
			}
			else
			{
				m_beforeState = m_curState;
				m_curState = state;
			}
		}
		else
		{
			m_curState = state;
		}
	}
	MINI_CIRCLE_STATE GetState() { return m_curState; }

private:
	std::weak_ptr<class MainCircle4_3> m_wpMainCircle;
	float m_degree = 0.f;
	MINI_CIRCLE_STATE m_curState = MINI_CIRCLE_STATE_CW;
	MINI_CIRCLE_STATE m_beforeState = MINI_CIRCLE_STATE_CCW;
};

// MainCircle
///////////////////////////////////////////////////////////////////////

enum MAIN_CIRCLE_STATE
{
	MAIN_CIRCLE_STATE_CW,
	MAIN_CIRCLE_STATE_CCW,
	MAIN_CIRCLE_STATE_STOP
};

class MainCircle4_3 : public GameObject
{
public:
	MainCircle4_3() {}
	virtual ~MainCircle4_3() {}

public:
	virtual BOOL Create() override;
	virtual void Update() override;
	virtual void Draw(HDC hDC) override;
	virtual void HandleCollision(const std::string& otherName) override;

public:
	BOOL CheckCollision(POINT pos);

	void SetSateliteState(MINI_CIRCLE_STATE state) { m_pSatellite->SetState(state); }
	void SetState(MAIN_CIRCLE_STATE state)
	{
		if (state == MAIN_CIRCLE_STATE_STOP)
		{
			if (m_curState == MAIN_CIRCLE_STATE_STOP)
			{
				m_curState = m_beforeState;
			}
			else
			{
				m_beforeState = m_curState;
				m_curState = state;
			}
		}
		else
		{
			m_curState = state;
		}
	}
	
	MINI_CIRCLE_STATE GetSateliteState() { return m_pSatellite->GetState(); }
	MAIN_CIRCLE_STATE GetState() { return m_curState; }

private:
	std::shared_ptr<MiniCircle4_3> m_pSatellite = nullptr;

	float m_degree = 0.f;
	MAIN_CIRCLE_STATE m_curState = MAIN_CIRCLE_STATE_CW;
	MAIN_CIRCLE_STATE m_beforeState = MAIN_CIRCLE_STATE_CCW;
};


class Demo4_3 : public Application
{
public:
	Demo4_3() {}
	virtual ~Demo4_3() {}

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

private:
	std::vector<std::shared_ptr<MainCircle4_3>> m_pCircles = {};


public:
	const static int MAX_CIRCLE_SIZE = 80;
	const static int MIN_CIRCLE_SIZE = 30;
	const static int MAX_CIRCLE_COUNT = 20;
};

