#ifndef LINECOMPONENT_H
#define LINECOMPONENT_H

#include "Component.h"
#include "vector"
#include "2DMath.h"
#include "PhysicsComponent.h"
#include "app\app.h"
class LineComponent : public Component
{
public:
    LineComponent(Component* parent, const std::vector<MATH::Line> &lines_, MATH::Vec2 centrePoint_);
    virtual void Update(const float deltaTime_) {};
    virtual void Render()const;
    virtual bool OnCreate() { return true; };
    virtual void OnDestroy() {};

    void UpdateLineComponent(Ref<PhysicsComponent> body);

private:
    std::vector<MATH::Line> lines;
    MATH::Vec2 centrePoint;

    MATH::Vec2 pos;
    float orientation;

};

#endif LINECOMPONENT_H

