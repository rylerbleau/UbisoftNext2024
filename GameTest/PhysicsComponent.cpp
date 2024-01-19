#include "stdafx.h"
#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(Component* parent, MATH::Vec2 pos_, MATH::Vec2 vel_, float orientation_, float angVel_, float mass_)
	: Component(parent)
{
	pos				= pos_;
	vel				= vel_;
	accel			= MATH::Vec2();
	maxVel			= 0.4f;

	orientation		= orientation_;
	angVel			= angVel_;
	mass			= mass_;
	angAccel		= 0.0f;
}

