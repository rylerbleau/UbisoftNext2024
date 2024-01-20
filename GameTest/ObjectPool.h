#pragma once
#include "Actor.h"
#include "PoolObject.h"
#include "array"
#include <vector>

class ObjectPool
{

private:
	static const int maxSize = 8;
	int currentSize;


public:
	ObjectPool();
	~ObjectPool() {};

	void Instantiate(MATH::Vec2 pos_, MATH::Vec2 vel_, MATH::Vec2 acc_, Ref<Actor> owner_, float timeLeft_, float rad_, float m_,
	float r_, float g_, float b_);
	void UpdatePool(float deltaTime);
	void Kill(const int i);
	void RenderObjects();

	int GetCurrentSize() { return currentSize; }
	std::array<Ref<PoolObject>, maxSize> objects;
};

