#include "FadeTo.h"
#include <cmath>

FadeTo::FadeTo(Image* target, float timeLimit, float alpha)
	: AnimationBase(target, time)
{
	m_color = entity->getColorFilter();
	m_alphaTarget = alpha;
	m_currentAlpha = m_color.a;
	time = timeLimit;
	m_alphaDiff = m_currentAlpha - m_alphaTarget;
	// 0 / duration
}

void FadeTo::update(float deltaTime)
{

	/*while (elapsedTime < fadeTime)
	{
		yield return null;
		elapsedTime += Time.deltaTime;
		if (fadeIn)
		{
			c.a = Mathf.Clamp01(elapsedTime / fadeTime);
		} else
		{
			c.a = 1f - Mathf.Clamp01(elapsedTime / fadeTime);
		}

		image.color = c;
	}*/

	if (entity) {
		// reduce alpha
		if (timer < time) {
			timer += deltaTime;
			// raise upper limit by the desired amount
			// target = .25  ->  1.0 + 0.25 - 1.0 = .25
			
			// startValue, endValue, timeElapsed / lerpDuration
			m_currentAlpha = lerp(1.0f, m_alphaTarget, clampHighLow(timer / time));
			//m_currentAlpha = 1.0f + m_alphaTarget - clampHighLow(timer / time);
			
			// cap to our target
			if (m_currentAlpha <= m_alphaTarget) {
				m_currentAlpha = m_alphaTarget;
			}

			m_color.a = m_currentAlpha;
			entity->setColorFilter(m_color);
		} else {
			mState = SUCCEEDED;
		}		
	}
}