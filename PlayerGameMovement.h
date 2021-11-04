#pragma once

#include "Entity.h"
#include "helper.h"
#include "structs.h"

class PlayerGameMovement
{
public:
	void processMovement(Entity* ent, player_move_data* move)
	{
		return call_virtual_method<void(__thiscall*)(void*, Entity*, player_move_data*)>(this, 1)(this, ent, move);
	}

	void startTracking(Entity* ent)
	{
		return call_virtual_method<void(__thiscall*)(void*, Entity*)>(this, 3)(this, ent);
	}

	void finishTracking(Entity* ent)
	{
		return call_virtual_method<void(__thiscall*)(void*, Entity*)>(this, 4)(this, ent);
	}
};