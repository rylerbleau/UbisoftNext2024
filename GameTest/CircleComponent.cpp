#include "stdafx.h"
#include "CircleComponent.h"

CircleComponent::CircleComponent(Component* parent, MATH::Vec2 centre_, float radius_, float numOfLines_, float r_, float g_, float b_, bool render_)
	:Component(parent)
{
	centre			= centre_;
	radius			= radius_;
	numOfLines		= numOfLines_;
	r				= r_;
	g				= g_;
	b				= b_;

	startR			= r;
	startG			= g;
	startB			= b;

	collidable		= true;
	render			= render_;

}

void CircleComponent::Render() const
{
	if (!render) return;
	App::DrawCircle(centre, radius, numOfLines, r, g, b);
}

void CircleComponent::UpdateCircleComponent(Ref<PhysicsComponent> body)
{
	centre = body->pos;
}

void CircleComponent::SetRGColour(MATH::Vec2 rg)
{
	r = rg.x;
	g = rg.y;
}
