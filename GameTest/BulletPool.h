#pragma once
#include "Actor.h"
#include "Bullet.h"
#include "array"
#include <vector>

class BulletPool
{

private:
	static const int maxSize = 8;

public:
	BulletPool();
	~BulletPool() {};

	void Instantiate(MATH::Vec2 pos_, MATH::Vec2 vel_, Ref<Actor> owner_, float timeLeft_);
	void UpdatePool(float deltaTime);
	void Kill(const int i);
	void RenderBullets();
	std::array<Ref<Bullet>, maxSize>& GetBulletsAsArray() { return bullets; }

	int GetMaxSize() { return maxSize; }
	std::array<Ref<Bullet>, maxSize> bullets;
};

