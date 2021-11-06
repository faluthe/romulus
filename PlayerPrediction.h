#pragma once

#include "CUserCmd.h"
#include "Entity.h"
#include "helper.h"
#include "PlayerMoveHelper.h"

class PlayerPrediction
{
public:
	VIRTUAL_METHOD(void, SetupMove, 20, (Entity* ent, CUserCmd* cmd, PlayerMoveHelper* helper, void* data), (this, ent, cmd, helper, data))
	VIRTUAL_METHOD(void, FinishMove, 21, (Entity* ent, CUserCmd* cmd, void* data), (this, ent, cmd, data))
};