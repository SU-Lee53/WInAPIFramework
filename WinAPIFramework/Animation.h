#pragma once

class Animation
{
public:
	Animation();
	~Animation();

public:
	void LoadFromFile(const std::wstring& wstrimgName);
	void Update();
	void Draw(HDC hDC, DWORD Rop = SRCCOPY);
	void DrawInRect(HDC hDC, RECT r, RECT srcRect = { 0,0,-1,-1 }, DWORD Rop = SRCCOPY);

	void RegisterAnimation(const std::string strAnimName, RECT beginRect, int offset, int nSprites);
	void SetAnimation(const std::string strAnimName) { m_strCurAnimation = strAnimName; }

	void SetAnimTick(ULONGLONG tick) { m_playTick = tick; }
	void SetDrawRect(RECT rect) { m_drawRect = rect; }
	RECT GetDrawRect() { return m_drawRect; }


private:
	CImage m_SpriteImage;
	RECT m_drawRect;
	
	int m_originWidth = 0;
	int m_originHeight = 0;

	struct AnimStruct
	{
		RECT beginRect;
		int offset;
		int nSprites;
	};

	std::unordered_map<std::string, std::shared_ptr<AnimStruct>> m_pAnimationMap = {};
	std::string m_strCurAnimation = "";

	int m_curAnimIndex = 0;
	ULONGLONG m_prevPlayTick = 0;
	ULONGLONG m_playTick = 50;

	RECT m_curAnimRect = {};
};

