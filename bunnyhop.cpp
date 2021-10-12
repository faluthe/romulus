#include "bunnyhop.h"
#include "CUserCmd.h"
#include "Entity.h"
#include "interfaces.h"

void bunnyhop(CUserCmd* cmd)
{
	Entity* localplayer{ interfaces::entityList->GetClientEntity(interfaces::engine->GetLocalPlayer()) };

	if (!localplayer)
		return;
	if (localplayer->health() == 0)
		return;

	if (!(localplayer->flags() & 1) && localplayer->moveType() != 9 && localplayer->moveType() != 10) // 1 = ONGROUND, 9 = ONLADDER, 10 = OBSERVER
		cmd->buttons &= ~CUserCmd::IN_JUMP;
}