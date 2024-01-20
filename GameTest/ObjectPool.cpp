#include "stdafx.h"
#include "ObjectPool.h"
#include <iterator>



ObjectPool::ObjectPool()
{
	for (int i = 0; i < maxSize; i++) {
		objects[i] = std::make_shared<PoolObject>(nullptr, 0.0f);
	}

}

void ObjectPool::Instantiate(MATH::Vec2 pos_, MATH::Vec2 vel_, Ref<Actor> owner_, float timeLeft_)
{
	Ref<PoolObject> mostLikely = nullptr;;
	float lowestTime = FLT_MAX;


	for (Ref<PoolObject> bullet : objects) {
		if (!bullet->InUse()) {
			bullet->Init(pos_, vel_, owner_, timeLeft_);
			return;
		}
		// track oldest, just in case full
		if (bullet->GetTimeLeft() < lowestTime) {
			lowestTime = bullet->GetTimeLeft();
			mostLikely = bullet;
		}
	}

	// if we are full, override the oldest
	mostLikely->Init(pos_, vel_, owner_, timeLeft_);
}

void ObjectPool::UpdatePool(float deltaTime)
{
	for (Ref<PoolObject> bullet : objects) {
		if (bullet->InUse()) {
			bullet->Update(deltaTime);

		}
	}

}

void ObjectPool::Kill(const int i)
{
	objects[i]->Kill();
}

void ObjectPool::RenderBullets()
{
	for (Ref<PoolObject> bullet : objects) {
		if (bullet->InUse()) {
			bullet->GetComponent<CircleComponent>()->Render();
		}
	}
}
