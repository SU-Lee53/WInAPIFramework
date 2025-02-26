#include "pch.h"
#include "Image.h"

using namespace std;

Image::Image()
{
}

Image::~Image()
{
}

void Image::LoadFromFile(const std::wstring& wstrimgName)
{
	m_Image.Load(wstrimgName.c_str());
	m_Width = m_Image.GetWidth();
	m_Height = m_Image.GetHeight();
}

void Image::Update()
{
}

void Image::Draw(HDC hDC)
{
	m_Image.Draw(hDC, m_drawRect);
}

void Image::DrawInRect(HDC hDC, RECT r, RECT srcRect, DWORD Rop)
{
	m_Image.Draw(hDC, r);
}
