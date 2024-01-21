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
	void SetPosition(MATH::Vec2 centre_) { centre = centre_; }
	MATH::Vec2 GetPos() { return centre; }

	
private:
	// real values
	float max;
	float cur;

	// 0-1
	float percentage;
	float lerpRate;
	float lerpT;
	float startPercent;
	float targetPercent;


	float r, g, b;
	float fillR, fillG, fillB;

	MATH::Vec2 centre;
	MATH::Vec2 dimensions;


};

