#include "stdafx.h"
#include "BulletPool.h"
#include <iterator>



BulletPool::BulletPool()
{
	for (int i = 0; i < maxSize; i++) {
		bullets[i] = std::make_shared<Bullet>(nullptr, 0.0f);
	}

}

void BulletPool::Instantiate(MATH::Vec2 pos_, MATH::Vec2 vel_, Ref<Actor> owner_, float timeLeft_)
{
	Ref<Bullet> mostLikely = nullptr;;
	float lowestTime = FLT_MAX;


	for (Ref<Bullet> bullet : bullets) {
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

void BulletPool::UpdatePool(float deltaTime)
{
	for (Ref<Bullet> bullet : bullets) {
		if (bullet->InUse()) {
			bullet->Update(deltaTime);

		}
	}

}

void BulletPool::Kill(const int i)
{
	bullets[i]->Kill();
}

void BulletPool::RenderBullets()
{
	for (Ref<Bullet> bullet : bullets) {
		if (bullet->InUse()) {
			bullet->GetComponent<CircleComponent>()->Render();
		}
	}
}
