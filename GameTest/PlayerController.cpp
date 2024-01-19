#include "stdafx.h"
#include "PlayerController.h"

MATH::Vec2 PlayerController::GetRightStick(int id = 0)
{
	MATH::Vec2 dir;

	switch (App::GetController(id).IsConnected()) {
	case true:
		// controller input
		dir.x = App::GetController().GetRightThumbStickX();
		dir.y = App::GetController().GetRightThumbStickY();

	default: 
		break;
	}
	
	return MATH::Vec2::normalize(dir);
}

MATH::Vec2 PlayerController::GetLeftStick(int id = 0)
{
	MATH::Vec2 dir;

	switch (App::GetController(id).IsConnected()) {
	case true:
		// controller input
		dir.x = App::GetController().GetLeftThumbStickX();
		dir.y = App::GetController().GetLeftThumbStickY();

		break;
	case false:
		// kbm input
		if (App::IsKeyPressed('W')) {
			dir.y = 1.0f;
		}
		if (App::IsKeyPressed('S')) {
			dir.y = -1.0f;
		}
		if (App::IsKeyPressed('D')) {
			dir.x = 1.0f;
		}
		if (App::IsKeyPressed('A')) {
			dir.x = -1.0f;
		}

		break;
	default:
		break;
	}

	return MATH::Vec2::normalize(dir);
}

int PlayerController::GetAnimState(MATH::Vec2 dir)
{
	if (MATH::Vec2::mag(dir) <= VERY_SMALL) {
		// no input
		return -1;
	}


	float rad = atan2f(dir.y, dir.x); // In radians
	float deg = rad * RADIANS_TO_DEGREES;
	 

	if (deg > 45.0f && deg <= 135.0f) {			// up, 0
		return 0;
	}
	else if (deg > 135.0f && deg <= 180.0f) {	// left, 2
		return 2;
	}
	else if (deg >= -180.0f && deg <= -135.0f) {	// left, 2
		return 2;
	}
	else if (deg > -135.0f && deg <= -45.0f) {	// down, 1
		return 1;
	}
	else if (deg > -45.0f && deg <= 45.0f) {		// right, 3
		return 3;
	}
	
    return -1;
}
