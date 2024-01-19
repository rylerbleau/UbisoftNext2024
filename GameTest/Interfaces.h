#pragma once


class IProjectile {
public:
	virtual void Update(float deltaTime) const = 0;


protected:
	Ref<Actor> owner;
	float timeLeft;

};