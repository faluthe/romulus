#pragma once

#include "CUserCmd.h"
#include "Entity.h"
#include "helper.h"
#include "PlayerMoveHelper.h"

class PlayerPrediction
{
public:
	void SetupMove(Entity* ent, CUserCmd* cmd, PlayerMoveHelper* helper, void* data)
	{
		return call_virtual_method<void(__thiscall*)(void*, Entity*, CUserCmd*, PlayerMoveHelper*, void*)>(this, 20)(this, ent, cmd, helper, data);
	}

	void FinishMove(Entity* ent, CUserCmd* cmd, void* data)
	{
		return call_virtual_method<void(__thiscall*)(void*, Entity*, CUserCmd*, void*)>(this, 21)(this, ent, cmd, data);
	}
};