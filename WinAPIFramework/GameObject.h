#pragma once

class GameObject
{
public:
	GameObject() {}
	virtual ~GameObject() {}

public:
	virtual BOOL Create() = 0;
	virtual void Update() = 0;
	void UpdateObjectStateToModel()
	{
		m_pModel->SetBackgroundColor(m_BkColor);
		m_pModel->SetFrameColor(m_FrameColor);
		m_pModel->SetFrameWidth(m_FrameWidth);
		m_pModel->SetOffset(m_Position);
		m_pModel->SetScale(m_Scale);
		m_pModel->Update();
	}

	// 대부분의 상황에선 쉬운 좌표계산을 위해 DrawInWindowCoord() 를 사용하는게 나을듯
	virtual void Draw(HDC hDC) = 0;

	virtual void HandleCollision(const std::string& otherName) = 0;


	std::shared_ptr<Shapes>& GetModel() { return m_pModel; }
	POINT& GetPosition() { return m_Position; }
	POINT& GetScale() { return m_Scale; }
	COLORREF GetBackgroundColor() { return m_BkColor; }
	COLORREF GetFrameColor() { return m_FrameColor; }	
	int GetFrameWidth() { return m_FrameWidth; }

	void SetModel(std::shared_ptr<Shapes> p) { m_pModel = p; }
	void SetModel(std::shared_ptr<Shapes>&& lp) { m_pModel = std::move(lp); }

	void SetPosition(POINT pos) { m_Position = pos; }
	void SetScale(POINT scale) { m_Scale = scale; }

	void SetBackgroundColor(COLORREF color) { m_BkColor = color; }
	void SetFrameColor(COLORREF color) { m_FrameColor = color; }
	void SetFrameWidth(int width) { m_FrameWidth = width; }


protected:
	std::shared_ptr<Shapes> m_pModel = nullptr;
	POINT m_Position = POINT{ 0,0 };
	POINT m_Scale = POINT{ 1,1 };
	COLORREF m_BkColor = RGB(255, 255, 255);
	COLORREF m_FrameColor = RGB(0, 0, 0);
	int m_FrameWidth = 1;
};

