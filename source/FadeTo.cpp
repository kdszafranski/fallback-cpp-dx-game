#include "FadeTo.h"
#include <cmath>

FadeTo::FadeTo(Image* target, float timeLimit, float alpha)
	: AnimationBase(target, time)
{
	m_color = entity->getColorFilter();
	m_alphaTarget = alpha;
	m_currentAlpha = m_color.a;
}

void FadeTo::update(float deltaTime)
{
	if (entity) {
		// reduce alpha
		if (timer < time) {
			timer += deltaTime;

			// startValue, endValue, timeElapsed / lerpDuration
			m_currentAlpha = lerp(1.0f, m_alphaTarget, clampHighLow(timer / time));
			m_color.a = m_currentAlpha;

			entity->setColorFilter(m_color);

		} else {
			mState = SUCCEEDED;
		}		
	}
}