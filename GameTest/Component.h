#ifndef COMPONENT_H
#define COMPONENT_H

#include <memory>
#include <iostream>

// Ref is defined as making a ref to a shared ptr
// Thanks Scott!!
template<typename T>
using Ref = std::shared_ptr<T>;


class Component {
public:
	Component(Component* parent_) :parent(parent_), isCreated(false) {}

	virtual ~Component() = default;

	// pure virtuals, don't forget to override
	virtual bool OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Update(const float deltaTime_) = 0;
	virtual void Render()const = 0;

protected:
	Component* parent;
	
	bool isCreated;		// to stop onCreate being called more than once per component

};

#endif COMPONENT_H

