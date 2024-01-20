#ifndef PHYSICS_H

#define PHYSICS_H



#include "2DMath.h"
#include "PhysicsComponent.h"
#include "CircleComponent.h"


using namespace MATH;
namespace PHYSICS {
	// physics helper class

	
	// linear
	inline static void UpdatePosition(Ref<PhysicsComponent> body, float deltaTime) {
		body->pos += body->vel * deltaTime;
	};

	inline static void UpdateVelocity(Ref<PhysicsComponent> body, float deltaTime) {
		body->vel += body->accel * deltaTime;

		// cap velocity
		if (Vec2::mag(body->vel) > body->maxVel) {
			 body->vel = Vec2::normalize(body->vel) * body->maxVel;
		}

	};

	inline static void AddForce(Ref<PhysicsComponent> body, MATH::Vec2 force) {

		MATH::Vec2 frictionForce = body->vel * -0.001f;
		MATH::Vec2 appliedforce = force / body->mass;

		body->accel = appliedforce + frictionForce;

	};

	// angular
	inline static void UpdateOrientation(Ref<PhysicsComponent> body, float deltaTime) {
		body->orientation += body->angVel * deltaTime + (body->angAccel * 0.5f * deltaTime * deltaTime);
	};
		
	inline static void UpdateAngVelocity(Ref<PhysicsComponent> body, float deltaTime) {
		body->angVel += body->angAccel * deltaTime;
	};

	inline static void SetAngVelocity(Ref<PhysicsComponent> body, float angVel_) {
		body->angVel = angVel_;

	}

	inline static void SetOrientation(Ref<PhysicsComponent> body, float orientation) {
		body->orientation = orientation;
	}
	
	



}



namespace COLLISIONS {

	

	inline static void CircleCircleCollision(Ref<CircleComponent> circle1, Ref<CircleComponent> circle2,
		Ref<PhysicsComponent> body1, Ref<PhysicsComponent> body2) {
		Circle c1 = circle1->GetCircle();
		Circle c2 = circle2->GetCircle();
		float d = Vec2::distance(c1.centre, c2.centre);
		if (d <= c1.r + c2.r) {
			// collision response

			
			Vec2 normal = (c1.centre - c2.centre) / d;
			float p = 2.0f * (Vec2::dot(body1->vel, normal) - Vec2::dot(body2->vel, normal)) / (body1->mass + body2->mass);

			body1->vel = body1->vel - (normal * p * body1->mass);
			body2->vel = body2->vel + (normal * p * body2->mass);
		}


	}


}

//double d = Math.sqrt(Math.pow(cx1 - cx2, 2) + Math.pow(cy1 - cy2, 2));
//double nx = (cx2 - cx1) / d;
//double ny = (cy2 - cy1) / d;
//double p = 2 * (circle1.vx * nx + circle1.vy * n_y - circle2.vx * nx - circle2.vy * n_y) /
//(circle1.mass + circle2.mass);
//vx1 = circle1.vx - p * circle1.mass * n_x;
//vy1 = circle1.vy - p * circle1.mass * n_y;
//vx2 = circle2.vx + p * circle2.mass * n_x;
//vy2 = circle2.vy + p * circle2.mass * n_y;
#endif PHYSICS_H