#include "stdafx.h"
#include "Bullet.h"



Bullet::Bullet(Component* parent, float timeLeft_) :Actor(parent){
	timeLeft	= timeLeft_;
	owner		= nullptr;
	alive		= false;

	
}

void Bullet::Update(const float deltaTime)
{
	if (!alive)  return;
	if (timeLeft <= 0.0f) { Kill(); }

	timeLeft -= deltaTime;
	GetComponent<PhysicsComponent>()->Update(deltaTime);
	GetComponent<CircleComponent>()->UpdateCircleComponent(GetComponent<PhysicsComponent>());



}

void Bullet::Init(MATH::Vec2 pos_, MATH::Vec2 vel_, Ref<Actor> owner_, float timeLeft_)
{
	owner		= owner_;
	timeLeft	= timeLeft_;
	alive		= true;

	// if overriding previous, reset physics.
	RemoveAllComponents();


	
	AddComponent<PhysicsComponent>(this, pos_, vel_, MATH::Vec2(), 0.0f, 0.0f, 1.0f, true);

	AddComponent<CircleComponent>(this, MATH::Vec2(0, 0), 20.0f, 20.0f, 0, 1, 0);

	GetComponent<CircleComponent>()->UpdateCircleComponent(GetComponent<PhysicsComponent>());

	
}

void Bullet::AddLine()
{
	
}
