#include "stdafx.h"
#include "RectangleComponent.h"

RectangleComponent::RectangleComponent(Component* parent, MATH::Vec2 centre_, MATH::Vec2 dim_, float r_, float g_, float b_, bool render_, bool fill_)
	: Component(parent)
{
	centre		= centre_;
	dim			= dim_;
	r			= r_;
	g			= g_;
	b			= b_;
	fill		= fill_;
	render		= render_;
}

void RectangleComponent::Render() const
{
	if (!render) return;
	App::DrawRect(centre, dim, fill, r, g, b);
}

void RectangleComponent::UpdateRectangleComponent(Ref<PhysicsComponent> body)
{
	centre = body->pos;
}
