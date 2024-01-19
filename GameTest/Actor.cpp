#include "stdafx.h"
#include "Actor.h"


Actor::Actor(Component* parent_) :Component(parent_) {}


Actor::~Actor() {
	OnDestroy();
}

void Actor::OnDestroy() {
	RemoveAllComponents();
	isCreated = false;
}

bool Actor::OnCreate() {
	if (isCreated) return isCreated;
	for (auto component : components) {
		if (component->OnCreate() == false) {
			isCreated = false;
			return isCreated;
		}
	}
	isCreated = true;
	return isCreated;
}

void Actor::Update(const float deltaTime) {}

void Actor::Render()const {}

void Actor::RemoveAllComponents() {
	components.clear();
}

void Actor::ListComponents() const {
	std::cout << typeid(*this).name() << " contains the following components:\n";
	for (auto component : components) {
		std::cout << typeid(*component.get()).name() << std::endl;
	}
	std::cout << '\n';
}


