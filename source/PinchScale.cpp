#include "PinchScale.h"

PinchScale::PinchScale(Image* target, float timeLimit, float scale)
	: AnimationBase(target, timeLimit) // initializer list, target was constructed already, we want to do this explicitly RIGHT NOW instead
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
			// at half should match 1.5s and 0 scale
			if (timer < m_halfTime) {
				timer += deltaTime;
				m_currentScale = 1.0f + m_targetScale - clampHighLow(timer / m_halfTime);
				entity->setScale(m_currentScale);
			} else {
				m_currentScale = m_targetScale;
				m_pinchComplete = true;
				timer = 0.0f;
			}
		} else {
			// initial pinch/shrink is complete
			if (timer < m_halfTime) {
				timer += deltaTime;
				m_currentScale = m_targetScale + clampHighLow(timer / m_halfTime);
				entity->setScale(m_currentScale);
			} else {
				entity->setScale(originalScale);
				mState = SUCCEEDED;
			}
		}
	}
}
