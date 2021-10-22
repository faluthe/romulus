#include "CUserCmd.h"
#include "localplayer.h"

void bunnyhop(CUserCmd* cmd)
{
	if (!localplayer || !localplayer->isAlive())
		return;
	
	if (!(localplayer->flags() & 1) && localplayer->moveType() != 9 && localplayer->moveType() != 10) // 1 = ONGROUND, 9 = ONLADDER, 10 = OBSERVER
		cmd->buttons &= ~CUserCmd::IN_JUMP;
}