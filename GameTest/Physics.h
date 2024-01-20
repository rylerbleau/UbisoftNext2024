#ifndef PHYSICS_H

#define PHYSICS_H



#include "2DMath.h"
#include "PhysicsComponent.h"


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
#endif PHYSICS_H