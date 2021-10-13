#include "autopistol.h"
#include "CUserCmd.h"
#include "interfaces.h"

void autopistol(CUserCmd* cmd)
{
	const auto localplayer{ interfaces::entityList->GetClientEntity(interfaces::engine->GetLocalPlayer()) };
	const auto activeWeapon{ localplayer->activeWeapon() };
	
	if (!activeWeapon || activeWeapon->weaponType() != 1)
		return;

	static bool firing{ false };

	if (firing && activeWeapon->itemDefinitionIndex() != 64)
		cmd->buttons &= ~CUserCmd::IN_ATTACK;

	firing = cmd->buttons & CUserCmd::IN_ATTACK ? true : false;
}