#pragma once
#include "AnimationBase.h"

class FadeTo : public AnimationBase
{
private:
	int m_alphaTarget;
	int m_currentAlpha;
	D3DXCOLOR m_color;
	float m_rate;

public:
	FadeTo(Image*, float time, int alpha);
	void update(float deltaTime);
};

