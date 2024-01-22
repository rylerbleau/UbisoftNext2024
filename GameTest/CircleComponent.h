#pragma once


#include "Component.h"
#include "vector"
#include "2DMath.h"
#include "PhysicsComponent.h"
#include "app\app.h"
class CircleComponent : public Component
{
public:
    CircleComponent(Component* parent, MATH::Vec2 centre_, float radius_, float numOfLines_, 
        float r_, float g_, float b_, bool render_, bool fill_);
    virtual void Update(const float deltaTime_) {};
    virtual void Render()const;
    virtual bool OnCreate() { return true; };
    virtual void OnDestroy() {};

    void UpdateCircleComponent(Ref<PhysicsComponent> body);
    MATH::Circle GetCircle() { return MATH::Circle{ radius, centre }; };

    bool GetCollidable() { return collidable; }
    void SetCollidable(bool c) { collidable = c; }

    bool GetRenderable() { return render; }
    void SetRenderable(bool r) { render = r; }

    void SetRGColour(MATH::Vec2 rg);
    MATH::Vec2 GetRGColour() { return MATH::Vec2(r, g); }
    MATH::Vec2 GetRGStartColour() { return MATH::Vec2(startR, startG); }

private:
    float radius;
    MATH::Vec2 centre;

    bool collidable;

    bool render;
    bool fill;
    float numOfLines;
    float r, g, b;

    float startR, startG, startB;

    

};



