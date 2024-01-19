#ifndef ACTOR_H
#define ACTOR_H

#include <vector> 
#include <iostream>
#include "Component.h"


class Actor : public Component {

protected:
	// Make a vector list of shared_ptrs for components
	std::vector<Ref<Component>> components;



public:
	Actor(Component* parent_);
	~Actor();
	bool OnCreate();
	void OnDestroy();
	void Update(const float deltaTime_);
	void Render() const;

    // Argument fwding
	template<typename ComponentTemplate, typename ... Args>
	void AddComponent(Args&& ... args_) {
		
		if (GetComponent<ComponentTemplate>().get() != nullptr) {
			std::cerr << "WARNING: Trying to add a component type that is already added - ignored\n";
			return;
		}
		// fwd arguments to component constructor
		components.push_back(std::make_shared<ComponentTemplate>(std::forward<Args>(args_)...));
	}

	template<typename ComponentTemplate>
	void AddComponent(Ref<ComponentTemplate> component_) {
		if (GetComponent<ComponentTemplate>().get() != nullptr) {
			std::cerr << "WARNING: Trying to add a component type that is already added - ignored\n";
			return;
		}
		components.push_back(component_);
	}

	template<typename ComponentTemplate>
	Ref<ComponentTemplate> GetComponent() const {
		for (auto component : components) {
			if (dynamic_cast<ComponentTemplate*>(component.get())) {
	
				return std::dynamic_pointer_cast<ComponentTemplate>(component);
			}
		}
		return Ref<ComponentTemplate>(nullptr);
	}

	// code needs to be in the header if it's a templated function
	template<typename ComponentTemplate>
	void RemoveComponent() {
		for (unsigned int i = 0; i < components.size(); i++) {
			if (dynamic_cast<ComponentTemplate*>(components[i].get()) != nullptr) {
				components.erase(components.begin() + i);
				break;
			}
		}
	}

	void RemoveAllComponents();
	void ListComponents() const;

};

#endif ACTOR_H