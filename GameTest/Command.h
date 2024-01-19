#pragma once

#include "Actor.h"
class Command
{
public:
	virtual ~Command() {}
	virtual void execute(Ref<Actor> actor) = 0;
};

class ChargeFireCommand : public Command
{
public:
	virtual void execute(Ref<Actor> actor)
	{
		
	}
};