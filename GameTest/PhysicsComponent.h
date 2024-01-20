#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "Component.h"
#include "2DMath.h"
#include <memory>

class PhysicsComponent : public Component, public std::enable_shared_from_this<PhysicsComponent>
{
public:

    PhysicsComponent(Component* parent, MATH::Vec2 pos_, MATH::Vec2 vel_, MATH::Vec2 accel_,
        float orientation_, float angVel_, float mass_, bool physicsEnabled_);
    virtual void Update(const float deltaTime_);
    virtual void Render()const {};
    virtual bool OnCreate() { return true; };
    virtual void OnDestroy() {};
    
    bool physicsEnabled;

    MATH::Vec2 pos;
    MATH::Vec2 vel;
    MATH::Vec2 accel;
    float maxVel;

    float orientation;
    float angVel;
    float angAccel;

    float mass;
};

#endif PHYSICSCOMPONENT_H

