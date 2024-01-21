#include "stdafx.h"
#include "ProgressBar.h"
#include "app\app.h"

ProgressBar::ProgressBar(MATH::Vec2 centre_, MATH::Vec2 dim_, float r_, float g_, float b_, float fr_, float fg_, float fb_)
{
	max				= 1.0f;
	cur				= 1.0f; 
	lerpT			= 1.0f;
	lerpRate		= 0.1f;

	centre			= centre_;
	dimensions		= dim_;

	r				= r_;
	g				= g_;
	b				= b_;
	fillR			= fr_;
	fillG			= fg_;
	fillB			= fb_;

	percentage		= 1.0f;

}

void ProgressBar::Update(float deltaTime)
{

	percentage = cur / max;
}

void ProgressBar::Render()
{
	MATH::Vec2 fillCentre = MATH::Vec2(centre.x - (dimensions.x / 2 * (1.0f - percentage)), centre.y);
	MATH::Vec2 fillDim = MATH::Vec2(dimensions.x * percentage, dimensions.y);
	App::DrawRect(fillCentre, fillDim, true, fillR, fillG, fillB);
	App::DrawRect(centre, dimensions, false, r, g, b);
}

void ProgressBar::SetProgress(float cur_, float max_)
{
	if (!max_ == 0.0f) {
		max = max_;
	}
	cur = cur_;
}
