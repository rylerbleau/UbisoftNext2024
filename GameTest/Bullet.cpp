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
}

void Bullet::Init(Ref<Actor> owner_, float timeLeft_)
{
	owner		= owner_;
	timeLeft	= timeLeft_;

	
}
