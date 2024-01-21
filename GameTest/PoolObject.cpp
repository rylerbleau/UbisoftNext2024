#include "stdafx.h"
#include "PoolObject.h"
#include <string>



PoolObject::PoolObject(Component* parent, float timeLeft_) :Actor(parent){
	timeLeft		= timeLeft_;
	owner			= nullptr;
	alive			= false;

	startTime		= 0.0f;
	colourUpdate	= false;
	EndColour		= MATH::Vec2(0.0f, 0.0f);
	colourT			= 1.0f;
	
}

void PoolObject::Update(const float deltaTime)
{
	if (!alive)  return;
	if (timeLeft <= 0.0f) { Kill(); }

	timeLeft -= deltaTime;
	Ref<CircleComponent> c = GetComponent<CircleComponent>();

	GetComponent<PhysicsComponent>()->Update(deltaTime);
	c->UpdateCircleComponent(GetComponent<PhysicsComponent>());

	if (colourUpdate) {
		colourT = timeLeft / startTime;
		c->SetRGColour(MATH::Vec2::lerp(EndColour, c->GetRGStartColour(),colourT));
	}

	App::Print(100, 100, std::to_string(colourT).c_str());



}

void PoolObject::Init(MATH::Vec2 pos_, MATH::Vec2 vel_, MATH::Vec2 acc_, Ref<Actor> owner_, float timeLeft_, float rad_, float m_,
	float r_, float g_, float b_, bool colourUpdate_, bool fill_)
{
	owner			= owner_;
	timeLeft		= timeLeft_;
	alive			= true;
	startTime		= timeLeft;
	colourUpdate	= colourUpdate_;

	// if overriding previous, reset physics.
	RemoveAllComponents();


	
	AddComponent<PhysicsComponent>(this, pos_, vel_, acc_, 0.0f, 0.0f, m_, true);

	AddComponent<CircleComponent>(this, MATH::Vec2(0, 0), rad_, 20.0f, r_, g_, b_, true, fill_);

	GetComponent<CircleComponent>()->UpdateCircleComponent(GetComponent<PhysicsComponent>());

	
}

