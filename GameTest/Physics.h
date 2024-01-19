#pragma once
#include "2DMath.h"
#include "PhysicsComponent.h"


using namespace MATH;
namespace PHYSICS {
	// physics helper class

	
	// linear
	void UpdatePosition(Ref<PhysicsComponent> body, float deltaTime) {
		body->pos += body->vel * deltaTime;
	};

	void UpdateVelocity(Ref<PhysicsComponent> body, float deltaTime) {
		body->vel += body->accel * deltaTime;

		// cap velocity
		if (Vec2::mag(body->vel) > body->maxVel) {
			 body->vel = Vec2::normalize(body->vel) * body->maxVel;
		}

	};

	void AddForce(Ref<PhysicsComponent> body, MATH::Vec2 force) {

		MATH::Vec2 frictionForce = body->vel * -0.001f;
		MATH::Vec2 appliedforce = force / body->mass;

		body->accel = appliedforce + frictionForce;

	};

	// angular
	void UpdateOrientation(Ref<PhysicsComponent> body, float deltaTime) {
		body->orientation += body->angVel * deltaTime + (body->angAccel * 0.5f * deltaTime * deltaTime);
	};
		
	void UpdateAngVelocity(Ref<PhysicsComponent> body, float deltaTime) {
		body->angVel += body->angAccel * deltaTime;
	};

	void SetAngVelocity(Ref<PhysicsComponent> body, float angVel_) {
		body->angVel = angVel_;

	}

	void SetOrientation(Ref<PhysicsComponent> body, float orientation) {
		body->orientation = orientation;
	}
	











}