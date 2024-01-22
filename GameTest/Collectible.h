#pragma once
#include "Actor.h"
#include "2DMath.h"
#include "CircleComponent.h"
#include "PhysicsComponent.h"
#include "LineComponent.h"
#include "RectangleComponent.h"

enum PROJECTILE_TYPE{
	NONE = 0,
	HP,
	HEAT,
	BULLET_SIZE
};

class Collectible : public Actor
{
public:
	Collectible(Component* parent) : Actor(parent), inUse(false), type(PROJECTILE_TYPE::NONE) {};

	virtual void Update(const float deltaTime) override;
	void Render();

	void Init(PROJECTILE_TYPE type_);
	void OnCollect(float& curHP, float maxHp, float& heatGainRate, float& bulletSize, float maxBsize);
	void Kill();
	bool InUse() { return inUse; }

private:
	bool inUse;
	PROJECTILE_TYPE type;
};

