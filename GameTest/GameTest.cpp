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
#include "Timer.h"

//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Eample data....
//------------------------------------------------------------------------



std::vector<MATH::Circle> stars;
Ref<Actor> playerActor;
ObjectPool bulletPool;
ObjectPool actorPool;
Timer* timer;
float interval = 3.0f;

std::string text;
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
	
	playerActor->AddComponent<PhysicsComponent>(parent, MATH::Vec2(APP_VIRTUAL_WIDTH / 2, 100.0f), MATH::Vec2(), MATH::Vec2(), 0.0f, 0.0f, 1.0f, true);

	std::vector<Line> lines;
	lines.push_back(Line{ MATH::Vec2(50.0f, -50.0f), MATH::Vec2(50.0f, 50.0f),1.0f, 0.0f, 0.0f });
	lines.push_back(Line{ MATH::Vec2(50.0f, 50.0f), MATH::Vec2(-50.0f, 50.0f) });
	lines.push_back(Line{ MATH::Vec2(-50.0f, 50.0f), MATH::Vec2(-50.0f, -50.0f) });
	lines.push_back(Line{ MATH::Vec2(-50.0f, -50.0f), MATH::Vec2(50.0f, -50.0f) });

	playerActor->AddComponent<LineComponent>(parent, lines, MATH::Vec2(0.0f, 0.0f));
	
	actorPool.Instantiate(MATH::Vec2(400, 800), MATH::Vec2(), MATH::Vec2(0, -0.0005f), nullptr, 2.0f, 100.0f, 1, 1, 0, 0);

	timer = new Timer;
	timer->Start();
	
	playerActor->OnCreate();
}

void HandleCollisions() {
	for (Ref<PoolObject> a : actorPool.objects) {
		if (!a->InUse()) continue;
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
	float t = timer->GetTimeInterval();
	if (t >= interval) {
		actorPool.InstantiateRandom(nullptr);
		timer->ResetTimeInterval();
	}
	
	

	Ref<PhysicsComponent> body = playerActor->GetComponent<PhysicsComponent>();
	Ref<LineComponent> line = playerActor->GetComponent<LineComponent>();

	
	// handle input ---------------------------------------------------------------------//

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_RIGHT_SHOULDER, true))
	{
		bulletPool.Instantiate(body->pos, MATH::Vec2(0.0f, 0.5f), MATH::Vec2(), playerActor, 2.0f, 20.0f, 1.0f, 0,1,0);
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
	PHYSICS::AddForce(body, MATH::Vec2(move.x, 0.0f) / 1000.0f);
	line->UpdateLineComponent(body);

	// update bullet pool ----------------------------------------------------------------//

	bulletPool.UpdatePool(deltaTime);
	actorPool.UpdatePool(deltaTime);

	// update all other actors ------------------------------------------------------------//

	
	text = std::to_string(t);

	HandleCollisions();


}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{	

	// CURRENT WORK: bullets, object pooling / interfaces
	// 

	
	bulletPool.RenderObjects();
	actorPool.RenderObjects();

	playerActor->GetComponent<LineComponent>()->Render();




	//App::Print(100, 100, text.c_str());

}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{	
	
	
	delete playerController;
	delete timer;
	//------------------------------------------------------------------------
}