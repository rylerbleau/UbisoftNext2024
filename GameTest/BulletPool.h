#pragma once
#include "Actor.h"
#include "Bullet.h"
#include "array"

class BulletPool
{
public:
	BulletPool();
	~BulletPool() {};

	void Instantiate(MATH::Vec2 pos_, MATH::Vec2 vel_, Ref<Actor> owner_, float timeLeft_);
	void UpdatePool(float deltaTime);
	void Kill(const int i);
	void RenderBullets();

private:
	static const int maxSize = 8;
	std::array<Ref<Bullet>, maxSize> bullets;
};

