#include "PinchScale.h"

PinchScale::PinchScale(Image* target, float timeLimit, float scale)
	// initializer list, target was constructed already, we want to do this explicitly RIGHT NOW instead
	: AnimationBase(target, timeLimit) 
{
	m_pinchComplete = false;
	m_targetScale = scale;
	m_currentScale = originalScale;
	m_halfTime = time / 2;
}

void PinchScale::update(float deltaTime)
{
	if (entity) {
		if (!m_pinchComplete) {
			// first half of time goes down
			if (timer < m_halfTime) {
				timer += deltaTime;
				// startValue, endValue, timeElapsed / lerpDuration
				m_currentScale = lerp(1.0f, m_targetScale, clampHighLow(timer / m_halfTime));
				entity->setScale(m_currentScale);
			} else {
				m_pinchComplete = true;
				timer = 0.0f;
			}
		} else {
			// initial pinch/shrink is complete
			if (timer < m_halfTime) {
				timer += deltaTime;
				m_currentScale = lerp(m_targetScale, originalScale, clampHighLow(timer / m_halfTime));
				entity->setScale(m_currentScale);
			} else {
				mState = SUCCEEDED;
			}
		}
	}
}

/// <summary>
/// See if the Entity wants to do anything after this animation
/// </summary>
void PinchScale::onSuccess()
{
	entity->onAnimationSuccess();
}
