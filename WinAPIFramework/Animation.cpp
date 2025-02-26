#include "pch.h"
#include "Animation.h"

using namespace std;

Animation::Animation()
{
}

Animation::~Animation()
{
}

void Animation::LoadFromFile(const std::wstring& wstrimgName)
{
	m_SpriteImage.Load(wstrimgName.c_str());
	m_originWidth = m_SpriteImage.GetWidth();
	m_originHeight = m_SpriteImage.GetHeight();
}

void Animation::Update()
{
	ULONGLONG curTick = GetTickCount64();
	if (curTick - m_prevPlayTick > m_playTick)
	{
		shared_ptr<AnimStruct>& refAnim = m_pAnimationMap.at(m_strCurAnimation);

		RECT animRect = refAnim->beginRect;
		int curLeft = animRect.left + (refAnim->offset * m_curAnimIndex);
		int curRight = curLeft + refAnim->offset;
		m_curAnimRect = C_RECT(curLeft, animRect.top, curRight, animRect.bottom);

		m_curAnimIndex = ++m_curAnimIndex % refAnim->nSprites;

		m_prevPlayTick = curTick;
	}
}

void Animation::Draw(HDC hDC, DWORD Rop)
{
	m_SpriteImage.Draw(hDC, m_drawRect, m_curAnimRect);
}

void Animation::DrawInRect(HDC hDC, RECT r, RECT srcRect, DWORD Rop)
{
	m_SpriteImage.Draw(hDC, r, m_curAnimRect);
}

void Animation::RegisterAnimation(const std::string strAnimName, RECT beginRect, int offset, int nSprites)
{
	shared_ptr<AnimStruct> p = make_shared<AnimStruct>();
	p->beginRect = beginRect;
	p->offset = offset;
	p->nSprites = nSprites;

	m_pAnimationMap.insert(make_pair(strAnimName, std::move(p)));
}
