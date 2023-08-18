#include "FadeTo.h"
#include <cmath>

FadeTo::FadeTo(Image* target, float timeLimit, float alpha)
	: AnimationBase(target, timeLimit)
{
	m_color = entity->getColorFilter();
	m_alphaTarget = alpha;
}

void FadeTo::update(float deltaTime)
{
	if (entity) {
		// reduce alpha
		if (timer < time) {
			timer += deltaTime;

			// lerp(startValue, endValue, timeElapsed / lerpDuration)
			if (m_alphaTarget >= 1) {
				// fade in (up to 1)
				m_color.a = lerp(0, m_alphaTarget, clampHighLow(timer / time));
			} else {
				// fade out (from 1)
				m_color.a = lerp(1.0f, m_alphaTarget, clampHighLow(timer / time));
			}

			entity->setColorFilter(m_color);

		} else {
			mState = SUCCEEDED;
		}		
	}
}