#pragma once

#include "Entity.h"
#include "helper.h"
#include "structs.h"

class PlayerGameMovement
{
public:
	VIRTUAL_METHOD(void, ProcessMovement, 1, (Entity* ent, player_move_data* move), (this, ent, move))
	VIRTUAL_METHOD(void, StartTracking, 3, (Entity* ent), (this, ent))
	VIRTUAL_METHOD(void, FinishTracking, 4, (Entity* ent), (this, ent))
};