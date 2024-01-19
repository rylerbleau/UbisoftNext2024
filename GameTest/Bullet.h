#pragma once

#include "Actor.h"
#include "Interfaces.h"
class Bullet : public Actor, public IProjectile
{
	Bullet(Component* parent, float timeLeft, Ref<Actor> owner_) :Actor(parent) {};
	virtual void Update(float deltaTime) {};

};

