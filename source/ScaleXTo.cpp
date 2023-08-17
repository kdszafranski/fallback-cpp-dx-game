#include "ScaleXTo.h"
#include <cmath>

ScaleXTo::ScaleXTo(Image* target, float timeLimit, float targetScale)
	: AnimationBase(target, timeLimit)
{
	m_scaleTarget = targetScale;
	m_currentXScale = entity->getXScale();
	// hold on to original x scale
	originalScale = m_currentXScale;
}

void ScaleXTo::update(float deltaTime)
{
	if (entity) {
		// reduce alpha
		if (timer < time) {
			timer += deltaTime;

			// startValue, endValue, timeElapsed / lerpDuration
			m_currentXScale = lerp(originalScale, m_scaleTarget, clampHighLow(timer / time));

			entity->setScale(m_currentXScale, entity->getYScale());

		} else {
			mState = SUCCEEDED;
		}
	}
}

void ScaleXTo::onSuccess()
{
	entity->onAnimationSuccess();
}