#include "FadeTo.h"

FadeTo::FadeTo(Image* target, float time, int alpha)
	: AnimationBase(target, time)
{
	m_alphaTarget = alpha;
	m_currentAlpha = 255; // TODO make this dynamic
	m_rate = .05; // 256/30 frames
	m_color = entity->getColorFilter();

}

//ALPHA25 = D3DCOLOR_ARGB(64, 255, 255, 255); 
//const COLOR_ARGB FB_METAL = D3DCOLOR_ARGB(255, 22, 242, 250); 

void FadeTo::update(float deltaTime)
{
	if (entity) {
		// reduce alpha
		m_currentAlpha -= m_rate;
		if (m_currentAlpha < m_alphaTarget) {
			m_currentAlpha = m_alphaTarget;
			mState = SUCCEEDED;
		}

		m_color.a = m_currentAlpha;
		entity->setColorFilter(m_color);
	}
}