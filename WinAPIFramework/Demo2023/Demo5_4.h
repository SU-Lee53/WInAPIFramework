#pragma once
#include "../Application.h"

// 이동, 확대/축소까지만 구현


class TextBox;
class Caret;
class GameBoard;
class Animation;
class Image;

enum MOVE_DIR_5_4
{
	MOVE_DIR_UP,
	MOVE_DIR_DOWN,
	MOVE_DIR_LEFT,
	MOVE_DIR_RIGHT
};

enum SHOW_MODE_5_4
{
	SHOW_MODE_DEFAULT,
	SHOW_MODE_BIG,
	SHOW_MODE_SMALL
};

class Demo5_4 : public Application
{
public:
	Demo5_4() {}
	virtual ~Demo5_4() {}

public:
	virtual BOOL Initialize() override;
	virtual void Update() override;
	virtual void Draw(HDC hDC) override;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	void OnCreate(HWND hWnd);
	void HandleMenu(WORD param);
	void CheckCollision();

public:
	void ProcessKeyboard();
	void ProcessMouse();

	void ChangeMode(SHOW_MODE_5_4 mode)
	{
		SHOW_MODE_5_4 before = m_showMode;
		m_showMode = mode;
		if (mode == SHOW_MODE_BIG)
		{
			RECT r = m_pAnim->GetDrawRect();
			r.left *= 2;
			r.top *= 2;
			r.right *= 2;
			r.bottom *= 2;
			m_pAnim->SetDrawRect(r);
		}
		else if (mode == SHOW_MODE_SMALL)
		{
			RECT r = m_pAnim->GetDrawRect();
			r.left /= 2;
			r.top /= 2;
			r.right /= 2;
			r.bottom /= 2;
			m_pAnim->SetDrawRect(r);
		}
		else if (mode == SHOW_MODE_DEFAULT)
		{
			if (before == SHOW_MODE_BIG)
			{
				RECT r = m_pAnim->GetDrawRect();
				r.left /= 2;
				r.top /= 2;
				r.right /= 2;
				r.bottom /= 2;
				m_pAnim->SetDrawRect(r);
			}
			else if (before == SHOW_MODE_SMALL)
			{
				RECT r = m_pAnim->GetDrawRect();
				r.left *= 2;
				r.top *= 2;
				r.right *= 2;
				r.bottom *= 2;
				m_pAnim->SetDrawRect(r);
			}
		}
	}

private:
	std::shared_ptr<Animation> m_pAnim = nullptr;
	std::shared_ptr<Image> m_pBkImg = nullptr;

	MOVE_DIR_5_4 m_moveDir;
	SHOW_MODE_5_4 m_showMode = SHOW_MODE_DEFAULT;
	int m_moveSpeed = 1;

	ULONGLONG m_modeChangedTime = 0;
	ULONGLONG m_modeTime = 3000;
	
};

