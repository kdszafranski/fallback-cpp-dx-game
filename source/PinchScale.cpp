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

			if (timer < m_halfTime) {
				timer += deltaTime;
				m_currentScale = 1.0f - clampHighLow(timer / m_halfTime);

				if (m_currentScale <= m_targetScale) {
					m_currentScale = m_targetScale;
					m_pinchComplete = true;
				}

				entity->setScale(m_currentScale);
			}
		} else {
			// initial pinch/shrink is complete
			if (timer < time) {
				timer += deltaTime;
				m_currentScale = m_targetScale + clampHighLow(timer / m_halfTime);

				if (m_currentScale >= originalScale) {
					m_currentScale = originalScale;
					mState = SUCCEEDED;
				}

				entity->setScale(m_currentScale);
			}
			entity->setScale(m_currentScale);
		}
	}
}
