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
#include "Collectible.h"
#include <stdlib.h>

//------------------------------------------------------------------------

#pragma region DATA

Ref<Collectible> powerup;
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
bool shooting = false;
bool released = true;

float meteorTimeCheckpoint = 0.0f;
float meteorTimeThreshold = 3.0f;

float powerupTimeCheckpoint = 0.0f;
float powerupTimeThreshold = 10.0f;

// upgradable --------------------------//
float heatGainRate = 3.0f;
float curHP = maxHP;
float projectileSize = 5.0f;
// -------------------------

float maxProjectileSize = 15.0f;

std::string text1 = "Best Time:";
std::string text2 = "                     Keyboard:                           Controller:";
std::string text3 = " Move->            A/D                                Left Stick";
std::string text4 = "Shoot->           Space                                    A";
std::string text5 = "Start->                 E                                         X";

PlayerController* playerController;
int bestTime = 0;


#pragma endregion

//------------------------------------------------------------------------

// TODO next:

// add powerups, high score, title screen?

void Init()
{
	playerActor = std::make_shared<Actor>(nullptr);
	powerup = std::make_shared<Collectible>(nullptr);
	Component* parent = dynamic_cast<Component*>(playerActor.get());
	
	playerActor->AddComponent<PhysicsComponent>(parent, MATH::Vec2(APP_VIRTUAL_WIDTH / 2, 100.0f), MATH::Vec2(), MATH::Vec2(), 0.0f, 0.0f, 1.0f, true);
	playerActor->AddComponent<CircleComponent>(parent, MATH::Vec2(0, 0), 50.0f, 20.0f, 0, 0, 0, true, true);

	std::vector<Line> lines;
	lines.push_back(Line{ MATH::Vec2(50.0f, -50.0f), MATH::Vec2(50.0f, 50.0f),1.0f, 0.0f, 0.0f });
	lines.push_back(Line{ MATH::Vec2(50.0f, 50.0f), MATH::Vec2(-50.0f, 50.0f) });
	lines.push_back(Line{ MATH::Vec2(-50.0f, 50.0f), MATH::Vec2(-50.0f, -50.0f) });
	lines.push_back(Line{ MATH::Vec2(-50.0f, -50.0f), MATH::Vec2(50.0f, -50.0f) });

	playerActor->AddComponent<LineComponent>(parent, lines, MATH::Vec2(0.0f, 0.0f));
	


	AmmoBar = new ProgressBar(MATH::Vec2(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT - 10.0f), MATH::Vec2(APP_VIRTUAL_WIDTH, 20), 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f);
	HealthBar = new ProgressBar(MATH::Vec2(400.0f, 100.0f), MATH::Vec2(100.0f, 20.0f), 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);

	timer = new Timer;
	timer->Start();
	
	playerActor->OnCreate();
}
//------------------------------------------------------------------------

void PreGameRender() {
	
	App::Print(APP_VIRTUAL_WIDTH / 2 - 200, 350, (text1 + std::to_string(bestTime)).c_str());
	App::Print(APP_VIRTUAL_WIDTH / 2 - 200, 300, text2.c_str());
	App::Print(APP_VIRTUAL_WIDTH / 2 - 200, 250, text3.c_str());
	App::Print(APP_VIRTUAL_WIDTH / 2 - 200, 200, text4.c_str());
	App::Print(APP_VIRTUAL_WIDTH / 2 - 200, 150, text5.c_str());

}
//------------------------------------------------------------------------

void ResetGame() {
	if (timer->GetElapsedSeconds() > bestTime) {
		bestTime = timer->GetElapsedSeconds();
	}
	timer->Stop();
	playing = false;
	actorPool.KillAll();
	bulletPool.KillAll();
	powerup->Kill();
	playerActor->GetComponent<PhysicsComponent>()->pos = MATH::Vec2(APP_VIRTUAL_WIDTH / 2, 100.0f);
	playerActor->GetComponent<PhysicsComponent>()->vel = MATH::Vec2();
	curHeat = 0.0f;
	curHP = maxHP;
	heatGainRate = 3.0f;
	projectileSize = 5.0f;

	meteorTimeCheckpoint = 0.0f;
	powerupTimeCheckpoint = 0.0f;
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
			curHP -= 1.0f;
			a->Kill();
			continue;
		}
	}

	Ref<CircleComponent> pCircle = playerActor->GetComponent<CircleComponent>();
	COLLISIONS::BoundingBoxCircleCollision(pCircle,
		playerActor->GetComponent<PhysicsComponent>(), 0.0f, APP_VIRTUAL_WIDTH, 0.0f, APP_VIRTUAL_HEIGHT);

	if (powerup->InUse()) {
		if (COLLISIONS::CircleCircleCollisionTest(pCircle, powerup->GetComponent<CircleComponent>())) {
			powerup->OnCollect(curHP, maxHP, heatGainRate, projectileSize, maxProjectileSize);
			powerup->Kill();
		}
	}

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


	float t = timer->GetElapsedSeconds();
	if(t - meteorTimeCheckpoint >= meteorTimeThreshold){
		actorPool.InstantiateRandom(nullptr);
		meteorTimeCheckpoint = t;
	}
	if (t - powerupTimeCheckpoint >= powerupTimeThreshold) {

		powerup->Init(static_cast<PROJECTILE_TYPE>(FRAND_RANGE(1, 3.999)));
		powerupTimeCheckpoint = t;
	}
	
	

	Ref<PhysicsComponent> body = playerActor->GetComponent<PhysicsComponent>();
	Ref<LineComponent> line = playerActor->GetComponent<LineComponent>();
	Ref<CircleComponent> circle = playerActor->GetComponent<CircleComponent>();

	
	// handle input ---------------------------------------------------------------------//

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true) || CheckShooting())
	{
		if (curHeat < maxHeat) {
			curHeat += heatGainRate;
			bulletPool.Instantiate(body->pos, MATH::Vec2(0.0f, 0.5f), MATH::Vec2(), playerActor, 2.0f, projectileSize, 1.0f, 0,1,0, false, true);
		}
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_Y, true)) {
		powerup->Init(static_cast<PROJECTILE_TYPE>(rand() % 3 + 1));
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
	powerup->Update(deltaTime);

	// UI --------------------------------------------------------------------------------//

	if (curHeat > 0.0f) {
		curHeat -= 0.005f * deltaTime;

	}
	AmmoBar->SetProgress(curHeat, maxHeat);
	AmmoBar->Update(deltaTime);

	HealthBar->SetProgress(curHP, maxHP);
	HealthBar->Update(deltaTime);
	HealthBar->SetPosition(MATH::Vec2(body->pos.x, HealthBar->GetPos().y));
	
	// Collision --------------------------------------------------------------------------//

	HandleCollisions();

	if (curHP <= 0.0f) {
		ResetGame();
	}
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
	powerup->Render();

	playerActor->GetComponent<LineComponent>()->Render();
	AmmoBar->Render();
	HealthBar->Render();
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