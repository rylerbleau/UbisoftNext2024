#pragma once

#include "Actor.h"
#include "Interfaces.h"
class Bullet : public Actor
{
	Bullet(Component* parent, float timeLeft_);
	void Update(const float deltaTime) override;


	bool InUse() const { return alive; }
	void Kill() { if(alive) alive = false; }
	void Init(Ref<Actor> owner_, float timeLeft_);

protected:
	Ref<Actor> owner;
	float timeLeft;
	bool alive;

};

