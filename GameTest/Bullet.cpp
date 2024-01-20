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
	PHYSICS::UpdatePosition(GetComponent<PhysicsComponent>(), deltaTime);
	GetComponent<LineComponent>()->UpdateLineComponent(GetComponent<PhysicsComponent>());



}

void Bullet::Init(MATH::Vec2 pos_, MATH::Vec2 vel_, Ref<Actor> owner_, float timeLeft_)
{
	owner		= owner_;
	timeLeft	= timeLeft_;
	alive		= true;

	// if overriding previous, reset physics.
	RemoveAllComponents();


	
	AddComponent<PhysicsComponent>(this, pos_, vel_, 0.0f, 0.0f, 1.0f);

	std::vector<Line> lines;
	lines.push_back(Line{ MATH::Vec2(0.0f, 0.0f), MATH::Vec2(0.0f, 10.0f),0.0f, 1.0f, 0.0f });
	AddComponent<LineComponent>(this, lines, MATH::Vec2(0.0f, 0.0f ));

	GetComponent<LineComponent>()->UpdateLineComponent(GetComponent<PhysicsComponent>());

	
}

void Bullet::AddLine()
{
	
}
