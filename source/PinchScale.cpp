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
		if (timer < time) {
			timer += deltaTime;
			m_currentScale = 1.0f - clampHighLow(timer / time / 2);

			if (m_currentScale < m_targetScale) {
				m_currentScale = m_targetScale;
			}

			entity->setScale(m_currentScale);
		} else {
			mState = SUCCEEDED;

			//entity->setScale(currentScale + deltaTime / time);
			//if (entity->getScale() > originalScale) {
			//	entity->setScale(originalScale);
			//}
		}
	}
}
