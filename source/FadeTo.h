#pragma once
#include "AnimationBase.h"

class FadeTo : public AnimationBase
{
private:
	float m_alphaTarget;
	float m_currentAlpha;
	float m_rate;
	D3DXCOLOR m_color;

public:
	// Construction
	FadeTo(Image*, float time, float alpha);
	void update(float deltaTime);
};

