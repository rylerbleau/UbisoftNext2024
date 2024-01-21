#pragma once
#include "2DMath.h"

class ProgressBar
{
public:

	ProgressBar(MATH::Vec2 centre_, MATH::Vec2 dim_, float r_ = 1.0f, float g_ = 1.0f, float b_ = 1.0f, 
		float fr_ = 1.0f, float fg_ = 1.0f, float fb_ = 1.0f);

	void Update(float deltaTime);
	void Render();
	void SetProgress(float cur_, float max_ = 0.0f);

	
private:
	float lerpT;
	float max;
	float cur;
	float percentage;
	float lerpRate;

	float r, g, b;
	float fillR, fillG, fillB;

	MATH::Vec2 centre;
	MATH::Vec2 dimensions;


};

