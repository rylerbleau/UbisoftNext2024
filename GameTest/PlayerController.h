#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "app\app.h"
#include "2DMath.h"

class PlayerController
{
public:
	
	MATH::Vec2 GetRightStick(int id);
	MATH::Vec2 GetLeftStick(int id);

	int GetAnimState(MATH::Vec2 dir);

};

#endif PLAYERCONTROLLER_H
