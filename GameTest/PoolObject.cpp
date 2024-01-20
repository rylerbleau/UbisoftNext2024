#include "stdafx.h"
#include "PoolObject.h"



PoolObject::PoolObject(Component* parent, float timeLeft_) :Actor(parent){
	timeLeft	= timeLeft_;
	owner		= nullptr;
	alive		= false;

	
}

void PoolObject::Update(const float deltaTime)
{
	if (!alive)  return;
	if (timeLeft <= 0.0f) { Kill(); }

	timeLeft -= deltaTime;
	GetComponent<PhysicsComponent>()->Update(deltaTime);
	GetComponent<CircleComponent>()->UpdateCircleComponent(GetComponent<PhysicsComponent>());



}

void PoolObject::Init(MATH::Vec2 pos_, MATH::Vec2 vel_, MATH::Vec2 acc_, Ref<Actor> owner_, float timeLeft_, float rad_, float m_,
	float r_, float g_, float b_)
{
	owner		= owner_;
	timeLeft	= timeLeft_;
	alive		= true;

	// if overriding previous, reset physics.
	RemoveAllComponents();


	
	AddComponent<PhysicsComponent>(this, pos_, vel_, acc_, 0.0f, 0.0f, m_, true);

	AddComponent<CircleComponent>(this, MATH::Vec2(0, 0), rad_, 20.0f, r_, g_, b_, true);

	GetComponent<CircleComponent>()->UpdateCircleComponent(GetComponent<PhysicsComponent>());

	
}

