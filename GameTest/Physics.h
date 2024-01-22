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
		if (d <= c1.r + c2.r && circle2->GetCollidable()) {
			// collision response

			
			Vec2 normal = (c1.centre - c2.centre) / d;
			float p = 2.0f * (Vec2::dot(body1->vel, normal) - Vec2::dot(body2->vel, normal)) /  (body1->mass + body2->mass);

			body1->vel = body1->vel - (normal * p * body1->mass);
			body2->vel = body2->vel + (normal * p * body2->mass);

			circle2->SetCollidable(false);
			body2->accel = Vec2(0.0f, -0.1f);
		}
	}
	inline static bool CircleCircleCollisionTest(Ref<CircleComponent> circle1, Ref<CircleComponent> circle2) {
		Circle c1 = circle1->GetCircle();
		Circle c2 = circle2->GetCircle();
		float d = Vec2::distance(c1.centre, c2.centre);
		if (d <= c1.r + c2.r) return true;
		return false;
	}



	inline static bool BoundingBoxCircleCollision(Ref<CircleComponent> circle, Ref<PhysicsComponent> body, float xNeg, float xPos, float yNeg, float yPos) {
		if (circle->GetCircle().centre.x - circle->GetCircle().r <= xNeg) {
			// hit left side
			body->pos.x += 2.0f;
			body->vel.x *= -1;
			return false;
		}
		else if (circle->GetCircle().centre.x + circle->GetCircle().r >= xPos) {
			// hit right side
			body->pos.x -= 2.0f;

			body->vel.x *= -1;
			return false;
		}
		else if (circle->GetCircle().centre.y - circle->GetCircle().r <= yNeg) {
			body->vel.y *= -1;
			return true;
			// hit bottom
		}
		return false;

	}


}

#endif PHYSICS_H