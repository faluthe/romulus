#include <string>

#include "backtrack.h"
#include "config.h"
#include "convars.h"
#include "Entity.h"
#include "helper.h"
#include "interfaces.h"
#include "localplayer.h"
#include "netvars.h"
#include "Panel.h"
#include "structs.h"

void debugpanel()
{
	static DynamicPanel debug{ L"Debug", infoFont, screenW - (screenW / 3), 3 };

	static int viewmodel{ debug.add_child(L"viewmodel_fov") };
	static int moveType{ debug.add_child(L"Move type") };
	static int health{ debug.add_child(L"Health") };
	static int playerFlags{ debug.add_child(L"Player's flags") };
	static int weaponType{ debug.add_child(L"Weapon type") };
	static int defIndex{ debug.add_child(L"Weapon index") };
	static int weaponClassId{ debug.add_child(L"Weapon class") };
	static int maxPlayers{ debug.add_child(L"Players") };
	static int maxEnts{ debug.add_child(L"Entities") };
	static int flashDuration{ debug.add_child(L"Flash duration") };
	static int flashAlpha{ debug.add_child(L"Flash Alpha") };
	static int globalTime{ debug.add_child(L"Time") };
	static int inaccuracy{ debug.add_child(L"Inaccuracy") };

	debug.display(viewmodel, convars::viewmodel_fov->GetFloat());

	if (interfaces::engine->IsInGame() && localplayer)
	{
		debug.display(health, localplayer->health());
		debug.display(moveType, localplayer->moveType());
		debug.display(playerFlags, localplayer->flags());
		debug.display(flashDuration, localplayer->flashDuration());
		debug.display(flashAlpha, localplayer->flashAlpha());
		debug.display(globalTime, interfaces::globalVars->curtime);

		if (const auto weapon{ localplayer->activeWeapon() })
		{
			debug.display(weaponType, L"Boobs");
			debug.display(defIndex, weapon->itemDefIndex());
			debug.display(weaponClassId, weapon->weaponTypeStr());
			debug.display(inaccuracy, weapon->inaccuracy());
		}
		
		int players{};
		for (int i{ 1 }; i < interfaces::engine->GetMaxClients(); i++)
		{
			if (interfaces::entityList->GetClientEntity<Entity>(i))
				players++;
		}

		int ents{};
		for (int i{ 1 }; i < interfaces::entityList->GetMaxEntities(); i++)
		{
			if (interfaces::entityList->GetClientEntity<Entity>(i))
				ents++;
		}

		debug.display(maxPlayers, players);
		debug.display(maxEnts, ents);
	}
	else
	{
		debug.hide(health);
		debug.hide(moveType);
		debug.hide(playerFlags);
		debug.hide(weaponType);
		debug.hide(defIndex);
		debug.hide(weaponClassId);
		debug.hide(maxPlayers);
		debug.hide(maxEnts);
	}

	debug.draw();
}

void spectator_list()
{
	using namespace interfaces;

	static DynamicPanel spectatorList{ L"Spectators", infoFont, screenW - 253, screenH / 2 }; // Default width = 250

	if (!localplayer || !localplayer->isAlive())
		return;

	spectatorList.draw();

	const auto player{ localplayer->isAlive() ? localplayer : localplayer->observerTarget() };

	if (!player)
		return;

	static int offset{ 0 };

	for (int i{ 1 }; i < engine->GetMaxClients(); i++)
	{
		const auto ent{ entityList->GetClientEntity<PlayerEntity>(i) };

		if (!ent || ent->dormant() || ent->isAlive() || ent->observerTarget() != player || ent == localplayer)
			continue;

		player_info_t info;

		if (!engine->GetPlayerInfo(i, &info))
			return;

		wchar_t name[128];

		if (MultiByteToWideChar(CP_UTF8, 0, info.name, -1, name, 128))
		{
			std::wstring nameWstr{ name };
			if (nameWstr.length() >= 10)
				nameWstr.erase(nameWstr.begin() + 10, nameWstr.end());

			std::wstring modeWstr{};
			switch (ent->observerMode())
			{
			case OBSMode::InEye: modeWstr = L"Firstperson"; break;
			case OBSMode::Chase: modeWstr = L"Chase"; break;
			case OBSMode::Deathcam: modeWstr = L"Deathcam"; break;
			case OBSMode::Fixed: modeWstr = L"Fixed"; break;
			case OBSMode::Freezecam: modeWstr = L"Freezecam"; break;
			case OBSMode::None: modeWstr = L"None"; break;
			case OBSMode::Roaming: modeWstr = L"Roaming"; break;
			default: modeWstr = L"Other";
			}

			spectatorList.temp_child(offset, nameWstr, modeWstr);
		}
	}
	
	offset = 0;
}

void rainbow_color(Color& rainbow, int& state)
{
	if (state == 0) // Red
	{
		if (rainbow.g < 127)
			rainbow.g++;
		if (rainbow.g == 127) 
			state = 1;
	}
	else if (state == 1)
	{
		if (rainbow.g < 255)
			rainbow.g++;
		if (rainbow.g == 255)
			state = 2;
	}
	else if (state == 2)
	{
		if (rainbow.r > 0)
			rainbow.r--;
		if (rainbow.r == 0)
			state = 3;
	}
	else if (state == 3)
	{
		if (rainbow.g > 0)
			rainbow.g--;
		if (rainbow.b < 255)
			rainbow.b++;
		if (rainbow.g == 0 && rainbow.b == 255)
			state = 4;
	}
	else if (state == 4)
	{
		if (rainbow.r < 75)
			rainbow.r++;
		if (rainbow.b > 130)
			rainbow.b--;
		if (rainbow.r == 75 && rainbow.b == 130)
			state = 5;
	}
	else if (state == 5)
	{
		if (rainbow.r < 148)
			rainbow.r++;
		if (rainbow.b < 211)
			rainbow.b++;
		if (rainbow.r == 148 && rainbow.b == 211)
			state = 6;
	}
	else if (state == 6)
	{
		if (rainbow.r < 255)
			rainbow.r++;
		if (rainbow.b > 0)
			rainbow.b--;
		if (rainbow.r == 255 && rainbow.b == 0)
			state = 0;
	}
}

void infopanel()
{
	if (!infoFont && !set_font(infoFont, 20))
		return;

	if (!screenW || !screenH)
		interfaces::engine->GetScreenSize(screenW, screenH);
	
	static Color rainbow{ 255, 0, 0, 255 };
	static int rainbowState{ 0 };
	rainbow_color(rainbow, rainbowState);

	print_text(L"Romulus", screenW - 253, 3, rainbow, infoFont); // Alligned with spec list
	spectator_list();

	if (config::drawDebugPanel)
		debugpanel();
}