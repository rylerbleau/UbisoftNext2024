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
		float r_, float g_, float b_, bool colourUpdate, bool fill_)
{
	Spawn(pos_, vel_, acc_, owner_, timeLeft_, rad_, m_, r_, g_, b_, colourUpdate, fill_);
}


void ObjectPool::InstantiateRandom(Ref<Actor> owner)
{
	// random spawn parameters
	float rad			= FRAND_RANGE(50.0f, 110.0f);

	float t				= FRAND_RANGE(0, 1);

	float timeLeft		= 3.0f + (5.0f * t);
	float r				= FRAND_RANGE(0.5f, 1.0f);
	float g				= 0.0f; 
	float b				= 0.0f;	

	MATH::Vec2 pos		= MATH::Vec2(FRAND_RANGE(rad, APP_VIRTUAL_WIDTH - rad), APP_VIRTUAL_HEIGHT + rad);
	MATH::Vec2 acc		= MATH::Vec2(0.0f, FRAND_RANGE(-0.0001, -0.0005));
	MATH::Vec2 vel		= MATH::Vec2(FRAND_RANGE(-0.2f, 0.2f), 0.0f);


	Spawn(pos, vel, acc, owner, timeLeft, rad, 1.0f, r, g, b, true, true);


}

void ObjectPool::Spawn(MATH::Vec2 pos_, MATH::Vec2 vel_, MATH::Vec2 acc_, Ref<Actor> owner_, float timeLeft_, float rad_, float m_, 
	float r_, float g_, float b_, bool colourUpdate, bool fill_)
{
	
	Ref<PoolObject> mostLikely = nullptr;
	float lowestTime = FLT_MAX;
	timeLeft_ *= 1000.0f;



	for (Ref<PoolObject> ob : objects) {
		if (!ob->InUse()) {
			ob->Init(pos_, vel_, acc_, owner_, timeLeft_, rad_, m_, r_, g_, b_, colourUpdate, fill_);
			currentSize += 1;
			return;
		}
		// track oldest, just in case full
		if (ob->GetTimeLeft() < lowestTime) {
			lowestTime = ob->GetTimeLeft();
			mostLikely = ob;
		}
	}

	// if we are full, override the oldest
	mostLikely->Init(pos_, vel_, acc_, owner_, timeLeft_, rad_, m_, r_, g_, b_, colourUpdate, fill_);

}

void ObjectPool::KillAll()
{
	currentSize = 0;
	for (Ref<PoolObject> ob : objects) {
		ob->Kill();
	}
}


void ObjectPool::UpdatePool(float deltaTime)
{
	for (Ref<PoolObject> ob : objects) {
		if (ob->InUse()) {
			ob->Update(deltaTime);

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

