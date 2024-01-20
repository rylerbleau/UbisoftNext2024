#pragma once

#include "Actor.h"
#include "Interfaces.h"
#include "2DMath.h"
#include "PhysicsComponent.h"
#include "CircleComponent.h"
#include "LineComponent.h"
#include "Physics.h"
#include <vector>

class Bullet : public Actor
{
public:

	Bullet(Component* parent, float timeLeft_);
	void Update(const float deltaTime) override;


	bool InUse() const { return alive; }
	void Kill() { if(alive) alive = false; }
	void Init(MATH::Vec2 pos_, MATH::Vec2 vel_, Ref<Actor> owner_, float timeLeft_);
	float GetTimeLeft() { return timeLeft; }

	static void AddLine();

	static Line line;

private:
	static bool bulletCreated;

protected:
	Ref<Actor> owner;
	float timeLeft;
	bool alive;

	

};


