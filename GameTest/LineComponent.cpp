#include "stdafx.h"
#include "LineComponent.h"

LineComponent::LineComponent(Component* parent, const std::vector<MATH::Line> &lines_, MATH::Vec2 centrePoint_)
	: Component(parent)
{
	lines			= lines_;
	centrePoint		= centrePoint_;

	orientation		= 0.0f;
	pos				= MATH::Vec2();

}

void LineComponent::Render() const
{
	for (MATH::Line line : lines) {

		line.start = MATH::Mat2::RotateAround2D(orientation, line.start);
		line.end = MATH::Mat2::RotateAround2D(orientation, line.end);
		line.start += pos;
		line.end += pos;
		App::DrawLine(line.start.x, line.start.y, line.end.x, line.end.y, line.r, line.g, line.b);
		
	}

}

void LineComponent::UpdateLineComponent(Ref<PhysicsComponent> body)
{
	pos = body->pos;
	orientation = body->orientation;

}
