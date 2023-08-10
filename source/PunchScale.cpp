#include "PunchScale.h"

PunchScale::PunchScale(Image* target, float timeLimit, float scale)
	: AnimationBase(target, timeLimit)
{
	m_punchComplete = false;
	m_targetScale = scale;
	m_currentScale = originalScale;
	m_halfTime = time / 2;
}

/// <summary>
/// Scales up over time and returns to original scale
/// </summary>
/// <param name="ms"></param>
void PunchScale::update(float deltaTime)
{
	if (entity) {
		if (!m_punchComplete) {
			// first half of time goes down
			if (timer < m_halfTime) {
				timer += deltaTime;
				// startValue, endValue, timeElapsed / lerpDuration
				m_currentScale = lerp(originalScale, m_targetScale, clampHighLow(timer / m_halfTime));
				entity->setScale(m_currentScale);
			} else {
				m_punchComplete = true;
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
