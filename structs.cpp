#include "CUserCmd.h"
#include "localplayer.h"
#include "structs.h"

float CGlobalVarsBase::serverTime(CUserCmd* cmd)
{
	static int tick;
	static CUserCmd* lastCmd;

	if (cmd)
	{
		if (localplayer && (!lastCmd || lastCmd->predicted))
			tick = localplayer->tickBase();
		else
			tick++;
		lastCmd = cmd;
	}
	return tick * interval_per_tick;
}