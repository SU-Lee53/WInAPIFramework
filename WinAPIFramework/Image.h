#pragma once
class Image
{
public:
	Image();
	~Image();

public:
	void LoadFromFile(const std::wstring& wstrimgName);
	void Update();
	void Draw(HDC hDC);
	void DrawInRect(HDC hDC, RECT r, RECT srcRect = { 0,0,-1,-1 }, DWORD Rop = SRCCOPY);


	void SetDrawRect(RECT rect) { m_drawRect = rect; }

private:
	CImage m_Image;
	RECT m_drawRect;
	int m_Width = 0;
	int m_Height = 0;

};

