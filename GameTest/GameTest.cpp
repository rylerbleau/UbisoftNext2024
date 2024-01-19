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
#include "PhysicsComponent.h"
#include "LineComponent.h"
#include "Actor.h"
#include "Physics.h"

//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Eample data....
//------------------------------------------------------------------------



std::vector<Ref<Actor>> actors;


std::string text;
PlayerController* player;
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
	//------------------------------------------------------------------------
	// Example Sprite Code....
	
	Ref<Actor> actor = std::make_shared<Actor>(nullptr);
	Component* parent = dynamic_cast<Component*>(actor.get());
	

	actor->AddComponent<PhysicsComponent>(parent, MATH::Vec2(400, 400), MATH::Vec2(), 0.0f, 0.0f, 1.0f);


	std::vector<Line> lines;
	lines.push_back(Line{ MATH::Vec2(50.0f, -50.0f), MATH::Vec2(50.0f, 50.0f),1.0f, 0.0f, 0.0f });
	lines.push_back(Line{ MATH::Vec2(50.0f, 50.0f), MATH::Vec2(-50.0f, 50.0f) });
	lines.push_back(Line{ MATH::Vec2(-50.0f, 50.0f), MATH::Vec2(-50.0f, -50.0f) });
	lines.push_back(Line{ MATH::Vec2(-50.0f, -50.0f), MATH::Vec2(50.0f, -50.0f) });

	actor->AddComponent<LineComponent>(parent, lines, MATH::Vec2(0.0f, 0.0f));

	
	actors.push_back(actor);


	for (Ref<Actor> a : actors) {
		a->OnCreate();
		a->GetComponent<PhysicsComponent>();

	}

	
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	//------------------------------------------------------------------------
	// Example Sprite Code....

	// sound
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
	{
		App::PlaySound(".\\TestData\\Test.wav");
	}
	

	MATH::Vec2 move = player->GetLeftStick(0);
	MATH::Vec2 aim = player->GetRightStick(0);
	

	for (Ref<Actor> actor : actors) {
		

		Ref<PhysicsComponent> body = actor->GetComponent<PhysicsComponent>();

		if (aim.x != 0.0f && aim.y != 0.0f) {

			PHYSICS::SetOrientation(body, atan2(aim.y, aim.x) * RADIANS_TO_DEGREES);
		}

		PHYSICS::UpdatePosition(body, deltaTime);
		PHYSICS::UpdateVelocity(body, deltaTime);
		PHYSICS::AddForce(body, move / 1000.0f);

		Ref<LineComponent> line = actor->GetComponent<LineComponent>();
		line->UpdateLineComponent(body);


		text = std::to_string(body->vel.x) +"  " + std::to_string(body->vel.y);
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

		Ref<LineComponent> line = actor->GetComponent<LineComponent>();
		line->Render();
		
	}
	App::DrawCircle(MATH::Vec2(400.0f, 400.0f), 0.5f, 20.0f, 1.0f, 0.0f, 0.0f);


	App::Print(100, 100, text.c_str());

}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{	
	//------------------------------------------------------------------------
	// Example Sprite Code....
	
	delete player;
	//------------------------------------------------------------------------
}