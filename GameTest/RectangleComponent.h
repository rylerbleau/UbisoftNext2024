#pragma once
#include "Component.h"
#include "2DMath.h"
#include "PhysicsComponent.h"
#include "app\app.h"


class RectangleComponent : public Component
{
public:

    RectangleComponent(Component* parent, MATH::Vec2 centre_, MATH::Vec2 dim_,
        float r_, float g_, float b_, bool render_, bool fill_);
    virtual void Update(const float deltaTime_) {};
    virtual void Render()const;
    virtual bool OnCreate() { return true; };
    virtual void OnDestroy() {};

    void UpdateRectangleComponent(Ref<PhysicsComponent> body);

private:
    MATH::Vec2 centre;
    MATH::Vec2 dim;

    float r, g, b;
    bool fill;
    bool render;
};

