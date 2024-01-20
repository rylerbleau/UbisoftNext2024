//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
//------------------------------------------------------------------------
#include "app\app.h"
#include <iostream>
#include "PlayerController.h"
#include <string>
#include "SpriteComponent.h"
#include "ObjectPool.h"
#include "LineComponent.h"
#include "CircleComponent.h"
#include "Actor.h"
#include "Physics.h"
#include <vector>

//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Eample data....
//------------------------------------------------------------------------



std::vector<Ref<Actor>> actors;
Ref<Actor> playerActor;
ObjectPool bulletPool;
ObjectPool actorPool;



PlayerController* playerController;

enum
{
	ANIM_FORWARDS,
	ANIM_BACKWARDS,
	ANIM_LEFT,
	ANIM_RIGHT,
};
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{

	playerActor = std::make_shared<Actor>(nullptr);
	Component* parent = dynamic_cast<Component*>(playerActor.get());
	

	playerActor->AddComponent<PhysicsComponent>(parent, MATH::Vec2(400, 400), MATH::Vec2(), MATH::Vec2(), 0.0f, 0.0f, 1.0f, true);


	std::vector<Line> lines;
	lines.push_back(Line{ MATH::Vec2(50.0f, -50.0f), MATH::Vec2(50.0f, 50.0f),1.0f, 0.0f, 0.0f });
	lines.push_back(Line{ MATH::Vec2(50.0f, 50.0f), MATH::Vec2(-50.0f, 50.0f) });
	lines.push_back(Line{ MATH::Vec2(-50.0f, 50.0f), MATH::Vec2(-50.0f, -50.0f) });
	lines.push_back(Line{ MATH::Vec2(-50.0f, -50.0f), MATH::Vec2(50.0f, -50.0f) });

	playerActor->AddComponent<LineComponent>(parent, lines, MATH::Vec2(0.0f, 0.0f));
	

	Ref<Actor> actor = std::make_shared<Actor>(nullptr);
	actor->AddComponent<PhysicsComponent>(dynamic_cast<Component*>(actor.get()), MATH::Vec2(400, 800), MATH::Vec2(), MATH::Vec2(0, -0.0005f),
		0, 0, 1, true);

	actor->AddComponent<CircleComponent>(dynamic_cast<Component*>(actor.get()), MATH::Vec2(0, 0), 100.0f, 20.0f, 1,0,0, true);
	
	actors.push_back(actor);
	//actorPool.Instantiate(MATH::Vec2(400, 800), MATH::Vec2(), MATH::Vec2(0, -0.0005f), nullptr, 10.0f, 100.0f, 1, 1, 0, 0);


	for (Ref<Actor> a : actors) {
		a->OnCreate();
		
	}

	playerActor->OnCreate();
	
}

void HandleCollisions() {
	for (Ref<Actor> a : actors) {
		//if (!a->InUse()) continue;
		Ref<CircleComponent> aCircle = a->GetComponent<CircleComponent>();
		Ref<PhysicsComponent> aBody = a->GetComponent<PhysicsComponent>();

		for (Ref<PoolObject> b : bulletPool.objects) {
			if (!b->InUse()) continue;
			Ref<CircleComponent> bCircle = b->GetComponent<CircleComponent>();
			Ref<PhysicsComponent> bBody = b->GetComponent<PhysicsComponent>();
			COLLISIONS::CircleCircleCollision(aCircle, bCircle, aBody, bBody);
		}
		if (COLLISIONS::BoundingBoxCircleCollision(aCircle, aBody, 0.0f, APP_VIRTUAL_WIDTH, 0.0f, APP_VIRTUAL_HEIGHT)) {
			// ball hit the floor *DEAD*
			continue;
		}
	}


}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{

	

	Ref<PhysicsComponent> body = playerActor->GetComponent<PhysicsComponent>();
	Ref<LineComponent> line = playerActor->GetComponent<LineComponent>();

	
	// handle input ---------------------------------------------------------------------//

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_RIGHT_SHOULDER, true))
	{
		bulletPool.Instantiate(body->pos, MATH::Vec2(0.0f, 0.5f), MATH::Vec2(), playerActor, 2000.0f, 20.0f, 1.0f, 0,1,0);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
	{
		App::PlaySound(".\\TestData\\Test.wav");
	}

	MATH::Vec2 move = playerController->GetLeftStick(0);
	MATH::Vec2 aim = playerController->GetRightStick(0);


	// updating player ------------------------------------------------------------------//
	

	if (aim.x != 0.0f && aim.y != 0.0f) {

		PHYSICS::SetOrientation(body, atan2(aim.y, aim.x) * RADIANS_TO_DEGREES);
	}
	body->Update(deltaTime);
	PHYSICS::AddForce(body, move / 1000.0f);
	line->UpdateLineComponent(body);

	// update bullet pool ----------------------------------------------------------------//

	bulletPool.UpdatePool(deltaTime);

	// update all other actors ------------------------------------------------------------//

	for (Ref<Actor> a : actors) {
		a->GetComponent<PhysicsComponent>()->Update(deltaTime);
	}



}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{	

	// CURRENT WORK: bullets, object pooling / interfaces
	// 

	for (Ref<Actor> actor : actors)
	{

		Ref<CircleComponent> c = actor->GetComponent<CircleComponent>();
		c->Render();
		c->UpdateCircleComponent(actor->GetComponent<PhysicsComponent>());
		
	}
	bulletPool.RenderBullets();

	playerActor->GetComponent<LineComponent>()->Render();


	App::DrawLine(400, 860, 400, 400, 0, 1, 0);


	//App::Print(100, 100, text.c_str());

	HandleCollisions();
}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{	
	
	
	delete playerController;
	//------------------------------------------------------------------------
}