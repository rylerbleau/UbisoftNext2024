#include "stdafx.h"
#include "ObjectPool.h"
#include <iterator>



ObjectPool::ObjectPool() : currentSize(0)
{
	for (int i = 0; i < maxSize; i++) {
		objects[i] = std::make_shared<PoolObject>(nullptr, 0.0f);
	}

}

void ObjectPool::Instantiate(MATH::Vec2 pos_, MATH::Vec2 vel_, MATH::Vec2 acc_, Ref<Actor> owner_, float timeLeft_, float rad_, float m_,
		float r_, float g_, float b_)
{
	Ref<PoolObject> mostLikely = nullptr;;
	float lowestTime = FLT_MAX;
	timeLeft_ *= 1000.0f;


	for (Ref<PoolObject> ob : objects) {
		if (!ob->InUse()) {
			ob->Init(pos_, vel_, acc_, owner_, timeLeft_, rad_, m_, r_, g_, b_);
			return;
		}
		// track oldest, just in case full
		if (ob->GetTimeLeft() < lowestTime) {
			lowestTime = ob->GetTimeLeft();
			mostLikely = ob;
		}
	}

	// if we are full, override the oldest
	mostLikely->Init(pos_, vel_, acc_, owner_, timeLeft_, rad_, m_, r_, g_, b_);
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

void ObjectPool::RenderObjects()
{
	for (Ref<PoolObject> ob : objects) {
		if (ob->InUse()) {
			ob->GetComponent<CircleComponent>()->Render();
		}
	}
}
