#pragma once


class IPoolable {
public:
	virtual void UpdateObject(float deltaTime) const = 0;
	virtual bool InUse() const = 0;
	virtual void Kill() = 0;

};