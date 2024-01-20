#include "stdafx.h"
#include "PhysicsComponent.h"
#include <memory>
#include "Physics.h"


PhysicsComponent::PhysicsComponent(Component* parent, MATH::Vec2 pos_, MATH::Vec2 vel_, MATH::Vec2 accel_,
	float orientation_, float angVel_, float mass_, bool physicsEnabled_ = true)
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
	physicsEnabled  = physicsEnabled_;
}

void PhysicsComponent::Update(const float deltaTime_)
{
	if (!physicsEnabled) return; 
	PHYSICS::UpdatePosition(shared_from_this(), deltaTime_);
	PHYSICS::UpdateVelocity(shared_from_this(), deltaTime_);
}

