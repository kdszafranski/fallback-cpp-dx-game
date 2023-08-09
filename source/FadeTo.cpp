#include "FadeTo.h"

FadeTo::FadeTo(Image* target, float runTime, float alpha)
	: AnimationBase(target, time)
{
	m_color = entity->getColorFilter();
	m_alphaTarget = alpha;
	m_currentAlpha = m_color.a;
	time = runTime;
}

void FadeTo::update(float deltaTime)
{
	if (entity) {
		// reduce alpha
		timer += deltaTime;
		if (timer < time) {
			// in order for it to take the full time to get there
			// we need to spread the delta out
			m_currentAlpha -= deltaTime / time;

			// cap to our target
			if (m_currentAlpha < m_alphaTarget) {
				m_currentAlpha = m_alphaTarget;
			}

			m_color.a = m_currentAlpha;
			entity->setColorFilter(m_color);
		} else {
			mState = SUCCEEDED;
		}		
	}
}