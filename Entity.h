#pragma once

#include "netvars.h"

class Entity
{
public:
	int health()
	{
		return *(int*)(this + netvars::health);
	}
	int flags()
	{
		return *(int*)(this + 0x104);
	}
};