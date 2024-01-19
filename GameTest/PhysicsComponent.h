#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "Component.h"
#include "2DMath.h"
class PhysicsComponent : public Component
{
public:

    PhysicsComponent(Component* parent, MATH::Vec2 pos_, MATH::Vec2 vel_, float orientation_, float angVel_, float mass_);
    virtual void Update(const float deltaTime_) {};
    virtual void Render()const {};
    virtual bool OnCreate() { return true; };
    virtual void OnDestroy() {};
    


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

