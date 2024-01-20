#pragma once
#include "Actor.h"
#include "PoolObject.h"
#include "array"
#include <vector>

class ObjectPool
{

private:
	static const int maxSize = 8;

public:
	ObjectPool();
	~ObjectPool() {};

	void Instantiate(MATH::Vec2 pos_, MATH::Vec2 vel_, Ref<Actor> owner_, float timeLeft_);
	void UpdatePool(float deltaTime);
	void Kill(const int i);
	void RenderBullets();

	int GetMaxSize() { return maxSize; }
	std::array<Ref<PoolObject>, maxSize> objects;
};

