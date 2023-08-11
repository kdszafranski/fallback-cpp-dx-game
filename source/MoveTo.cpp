#include "MoveTo.h"

MoveTo::MoveTo(Image* target, float timeLimit, Vector2 moveToPos)
	: AnimationBase(target, timeLimit)
{
	m_targetPosition = moveToPos;
}

/// <summary>
/// Moves along line from original position to target position
/// </summary>
/// <param name="ms"></param>
void MoveTo::update(float deltaTime)
{
	if (entity) {
		if (timer < time) {
			timer += deltaTime;
			// startValue, endValue, timeElapsed / lerpDurations
			m_currentPosition.x = lerp(originalPosition.x, m_targetPosition.x, clampHighLow(timer / time));
			m_currentPosition.y = lerp(originalPosition.y, m_targetPosition.y, clampHighLow(timer / time));

			entity->setPosition(m_currentPosition);
		} else {
			entity->setPosition(m_targetPosition);// make sure it's exact
			mState = SUCCEEDED;
		}
	}
}

void MoveTo::onSuccess()
{
	entity->setCanDestroy(true);
}
