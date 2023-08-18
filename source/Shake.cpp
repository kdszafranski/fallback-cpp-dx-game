#include "Shake.h"
#include <cmath>
#include <ctime>

Shake::Shake(Image* target, float timeLimit, Vector2 moveBounds)
	: AnimationBase(target, timeLimit)
{
	m_movementBounds = moveBounds;
	m_currentPosition = originalPosition;
}

/// <summary>
/// Moves along line from original position to target position
/// </summary>
/// <param name="ms"></param>
void Shake::update(float deltaTime)
{
	if (entity) {
		if (timer < time) {
			timer += deltaTime;

			// pick a spot at most bounds away from original
			float xOffset = rand() % static_cast<int>(m_movementBounds.x * 2) - m_movementBounds.x;
			m_currentPosition.x = originalPosition.x + xOffset;
			float yOffset = rand() % static_cast<int>(m_movementBounds.y * 2) - m_movementBounds.y;
			m_currentPosition.y = originalPosition.y + yOffset;

			entity->setPosition(m_currentPosition);
		} else {
			entity->setPosition(originalPosition);// make sure it's exact
			mState = SUCCEEDED;
		}
	}
}

void Shake::onSuccess()
{
}
