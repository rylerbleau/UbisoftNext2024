#include "stdafx.h"
#include "ProgressBar.h"
#include "app\app.h"

ProgressBar::ProgressBar(MATH::Vec2 centre_, MATH::Vec2 dim_, float r_, float g_, float b_, float fr_, float fg_, float fb_)
{
	max				= 1.0f;
	cur				= 1.0f; 
	lerpT			= 1.0f;
	decayRate		= 0.1f;

	centre			= centre_;
	dimensions		= dim_;

	r				= r_;
	g				= g_;
	b				= b_;
	fillR			= fr_;
	fillG			= fg_;
	fillB			= fb_;

}

void ProgressBar::Update(float deltaTime)
{
	
}

void ProgressBar::Render()
{
	//App::DrawRect();
}

void ProgressBar::SetProgress(float cur_, float max_)
{
}
