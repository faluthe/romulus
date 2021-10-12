#pragma once

#include "netvars.h"

class Entity
{
public:
	int health()
	{
		return *reinterpret_cast<int*>(this + netvars::health);
	}

	int flags()
	{
		return *reinterpret_cast<int*>(this + netvars::flags);
	}

	int moveType()
	{
		return *reinterpret_cast<int*>(this + netvars::moveType);
	}

	unsigned char dormant()
	{
		return *reinterpret_cast<unsigned char*>(this + 0xED);
	}

	int team()
	{
		return *reinterpret_cast<int*>(this + netvars::team);
	}
};