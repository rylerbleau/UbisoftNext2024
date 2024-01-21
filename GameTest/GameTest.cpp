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
#include "ProgressBar.h"
#include <vector>
#include "Timer.h"

//------------------------------------------------------------------------

#pragma region DATA

std::vector<MATH::Circle> stars;
Ref<Actor> playerActor;
ObjectPool bulletPool;
ObjectPool actorPool;
Timer* timer;
ProgressBar* AmmoBar;
ProgressBar* HealthBar;
float interval = 3.0f;
bool playing = false; 
float maxHeat = 10.0f;
float curHeat = 0.0f;
float maxHP = 5.0f;
float curHP = maxHP;
bool shooting = false;
bool released = true;

std::string text1 = "                     Keyboard:                           Controller:";
std::string text2 = " Move->            A/D                                Left Stick";
std::string text3 = "Shoot->           Space                                    A";
std::string text4 = "Start->                 E                                         X";

PlayerController* playerController;


#pragma endregion

//------------------------------------------------------------------------

void Init()
{
	playerActor = std::make_shared<Actor>(nullptr);
	Component* parent = dynamic_cast<Component*>(playerActor.get());
	
	playerActor->AddComponent<PhysicsComponent>(parent, MATH::Vec2(APP_VIRTUAL_WIDTH / 2, 100.0f), MATH::Vec2(), MATH::Vec2(), 0.0f, 0.0f, 1.0f, true);
	playerActor->AddComponent<CircleComponent>(parent, MATH::Vec2(0, 0), 10.0f, 20.0f, 0, 0, 0, false);

	std::vector<Line> lines;
	lines.push_back(Line{ MATH::Vec2(50.0f, -50.0f), MATH::Vec2(50.0f, 50.0f),1.0f, 0.0f, 0.0f });
	lines.push_back(Line{ MATH::Vec2(50.0f, 50.0f), MATH::Vec2(-50.0f, 50.0f) });
	lines.push_back(Line{ MATH::Vec2(-50.0f, 50.0f), MATH::Vec2(-50.0f, -50.0f) });
	lines.push_back(Line{ MATH::Vec2(-50.0f, -50.0f), MATH::Vec2(50.0f, -50.0f) });

	playerActor->AddComponent<LineComponent>(parent, lines, MATH::Vec2(0.0f, 0.0f));
	

	AmmoBar = new ProgressBar(MATH::Vec2(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT - 10.0f), MATH::Vec2(APP_VIRTUAL_WIDTH, 20), 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f);
	HealthBar = new ProgressBar(MATH::Vec2(), MATH::Vec2(100.0f, 20.0f), 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);

	timer = new Timer;
	timer->Start();
	
	playerActor->OnCreate();
}
//------------------------------------------------------------------------

void PreGameRender() {
	App::Print(APP_VIRTUAL_WIDTH / 2 - 200, 300, text1.c_str());
	App::Print(APP_VIRTUAL_WIDTH / 2 - 200, 250, text2.c_str());
	App::Print(APP_VIRTUAL_WIDTH / 2 - 200, 200, text3.c_str());
	App::Print(APP_VIRTUAL_WIDTH / 2 - 200, 150, text4.c_str());

}
//------------------------------------------------------------------------

void ResetGame() {
	timer->Stop();
	playing = false;
	actorPool.KillAll();
	bulletPool.KillAll();
	playerActor->GetComponent<PhysicsComponent>()->pos = MATH::Vec2(APP_VIRTUAL_WIDTH / 2, 100.0f);
	playerActor->GetComponent<PhysicsComponent>()->vel = MATH::Vec2();
	curHeat = 0.0f;
	curHP = maxHP;
}
//------------------------------------------------------------------------

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
			ResetGame();
			continue;
		}
	}
	COLLISIONS::BoundingBoxCircleCollision(playerActor->GetComponent<CircleComponent>(),
		playerActor->GetComponent<PhysicsComponent>(), 0.0f, APP_VIRTUAL_WIDTH, 0.0f, APP_VIRTUAL_HEIGHT);


}

bool CheckShooting() {
	shooting = App::IsKeyPressed(' ');
	if (shooting) {
		if (released) {
			released = false;
			return true;
		}
	}
	else {
		released = true;
		return false;
	}
}
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	
	if (!playing) {
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_X, true) || App::IsKeyPressed('E'))
		{
			timer->Start();
			playing = true;
		}
		else return;
	}


	float t = timer->GetTimeInterval();
	if (t >= interval) {
		actorPool.InstantiateRandom(nullptr);
		timer->ResetTimeInterval();
	}
	
	

	Ref<PhysicsComponent> body = playerActor->GetComponent<PhysicsComponent>();
	Ref<LineComponent> line = playerActor->GetComponent<LineComponent>();
	Ref<CircleComponent> circle = playerActor->GetComponent<CircleComponent>();

	
	// handle input ---------------------------------------------------------------------//

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true) || CheckShooting())
	{
		if (curHeat < maxHeat) {
			curHeat += 2.0f;
			bulletPool.Instantiate(body->pos, MATH::Vec2(0.0f, 0.5f), MATH::Vec2(), playerActor, 2.0f, 20.0f, 1.0f, 0,1,0, false);
		}
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
	circle->UpdateCircleComponent(body);

	// update object pools ----------------------------------------------------------------//

	bulletPool.UpdatePool(deltaTime);
	actorPool.UpdatePool(deltaTime);

	// UI --------------------------------------------------------------------------------//

	if (curHeat > 0.0f) {
		curHeat -= 0.005f * deltaTime;

	}
	AmmoBar->SetProgress(curHeat, maxHeat);
	AmmoBar->Update(deltaTime);
	
	// Collision --------------------------------------------------------------------------//

	HandleCollisions();


}

//------------------------------------------------------------------------
void Render()
{	

	if (!playing) {
		PreGameRender();
		return;
	}
	
	bulletPool.RenderObjects();
	actorPool.RenderObjects();

	playerActor->GetComponent<LineComponent>()->Render();
	AmmoBar->Render();
	int t = std::floor(timer->GetElapsedSeconds());
	App::Print(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_WIDTH / 2, std::to_string(t).c_str(), 1.0f, 0.0f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24);

}

//------------------------------------------------------------------------
void Shutdown()
{	
	delete playerController;
	delete timer;
	delete AmmoBar;
	delete HealthBar;
}
//------------------------------------------------------------------------