#include <stdexcept>
#include <string>
#include <vector>
#include <Windows.h>

#include "config.h"
#include "convars.h"
#include "Entity.h"
#include "helper.h"
#include "infopanel.h"
#include "interfaces.h"
#include "netvars.h"
#include "Panel.h"

unsigned long infoFont{};
int screenW, screenH;

void debugpanel()
{
	static DynamicPanel debug{ L"Test", infoFont, screenW - (screenW / 5), screenH / 2 };

	static int flags{ debug.add_child(L"netvars::flags", std::to_wstring(netvars::flags)) };
	static int viewmodel{ debug.add_child(L"viewmodel_fov") };
	static int moveType{ debug.add_child(L"Move type") };
	static int health{ debug.add_child(L"Health") };
	static int playerFlags{ debug.add_child(L"Player's flags") };
	static int weaponType{ debug.add_child(L"Weapon type") };
	static int maxPlayers{ debug.add_child(L"Players") };

	debug.display(viewmodel, std::to_wstring(convars::viewmodel_fov->GetValue()));

	Entity* localplayer{ interfaces::entityList->GetClientEntity(interfaces::engine->GetLocalPlayer()) };

	if (localplayer)
	{
		debug.display(health, std::to_wstring(localplayer->health()));
		debug.display(moveType, std::to_wstring(localplayer->moveType()));
		debug.display(playerFlags, std::to_wstring(localplayer->flags()));
		if (localplayer->activeWeapon())
			debug.display(weaponType, weapontype_to_wstring(localplayer->activeWeapon()->weaponType()));
		int players{};
		for (int i{ 1 }; i < interfaces::engine->GetMaxClients(); i++)
		{
			if (interfaces::entityList->GetClientEntity(i))
				players++;
		}
		debug.display(maxPlayers, std::to_wstring(players));
	}
	else
	{
		debug.hide(health);
		debug.hide(moveType);
		debug.hide(playerFlags);
		debug.hide(weaponType);
		debug.hide(maxPlayers);
	}

	debug.draw();
}

void infopanel()
{
	if (!infoFont && !set_font(infoFont, 20))
		return;
	interfaces::surface->DrawSetTextFont(infoFont);

	interfaces::engine->GetScreenSize(screenW, screenH);

	static DynamicPanel info{ L"Romulus", infoFont, screenW - 101, 1, 100 };

	info.draw();

	if (config::mode == 0)
		debugpanel();
}