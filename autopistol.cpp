#include "CUserCmd.h"
#include "localplayer.h"

void autopistol(CUserCmd* cmd)
{
	if (!localplayer || !localplayer->isAlive())
		return;

	const auto activeWeapon{ localplayer->activeWeapon() };
	
	if (!activeWeapon || !activeWeapon->isPistol())
		return;

	static bool firing{ false };

	if (firing && !activeWeapon->isRevolver())
		cmd->buttons &= ~CUserCmd::IN_ATTACK;

	firing = cmd->buttons & CUserCmd::IN_ATTACK ? true : false;
}