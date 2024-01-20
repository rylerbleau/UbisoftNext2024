#include "stdafx.h"
#include "CircleComponent.h"

CircleComponent::CircleComponent(Component* parent, MATH::Vec2 centre_, float radius_, float numOfLines_, float r_, float g_, float b_)
	:Component(parent)
{
	centre			= centre_;
	radius			= radius_;
	numOfLines		= numOfLines_;
	r				= r_;
	g				= g_;
	b				= b_;

	collidable = true;


}

void CircleComponent::Render() const
{
	
	App::DrawCircle(centre, radius, numOfLines, r, g, b);
}

void CircleComponent::UpdateCircleComponent(Ref<PhysicsComponent> body)
{
	centre = body->pos;
}
