#include "DirectionBounce.h"

DirectionBounce::DirectionBounce(Image* target, float timeLimit, Vector2 moveToPos)
	: AnimationBase(target, timeLimit)
{
	m_moveComplete = false;
	m_targetPosition = moveToPos;
	m_halfTime = time / 2;
}

/// <summary>
/// Moves over time and returns to original position
/// </summary>
/// <param name="ms"></param>
void DirectionBounce::update(float deltaTime)
{
	if (entity) {
		if (!m_moveComplete) {
			// first half of time goes down
			if (timer < m_halfTime) {
				timer += deltaTime;
				// startValue, endValue, timeElapsed / lerpDuration
				m_currentPosition.x = lerp(originalPosition.x, m_targetPosition.x, clampHighLow(timer / m_halfTime));
				m_currentPosition.y = lerp(originalPosition.y, m_targetPosition.y, clampHighLow(timer / m_halfTime));
				
				entity->setPosition(m_currentPosition);
			} else {
				m_moveComplete = true;
				timer = 0.0f;
			}
		} else {
			// initial pinch/shrink is complete
			if (timer < m_halfTime) {
				timer += deltaTime;
				m_currentPosition.x = lerp(m_targetPosition.x, originalPosition.x, clampHighLow(timer / m_halfTime));
				m_currentPosition.y = lerp(m_targetPosition.y, originalPosition.y, clampHighLow(timer / m_halfTime));

				entity->setPosition(m_currentPosition);
			} else {
				mState = SUCCEEDED;
			}
		}
	}
}

void DirectionBounce::onSuccess()
{
	entity->setCurrentFrame(originalFrame);
	entity->onAnimationSuccess();
}
