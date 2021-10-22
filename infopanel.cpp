#include <string>

#include "config.h"
#include "convars.h"
#include "Entity.h"
#include "helper.h"
#include "infopanel.h"
#include "interfaces.h"
#include "localplayer.h"
#include "netvars.h"
#include "Panel.h"

int screenW, screenH;

void debugpanel()
{
	static DynamicPanel debug{ L"Debug", infoFont, screenW - (screenW / 5), screenH / 3 };

	static int viewmodel{ debug.add_child(L"viewmodel_fov") };
	static int moveType{ debug.add_child(L"Move type") };
	static int health{ debug.add_child(L"Health") };
	static int playerFlags{ debug.add_child(L"Player's flags") };
	static int weaponType{ debug.add_child(L"Weapon type") };
	static int defIndex{ debug.add_child(L"Weapon index") };
	static int maxPlayers{ debug.add_child(L"Players") };
	static int maxEnts{ debug.add_child(L"Entities") };

	debug.display(viewmodel, convars::viewmodel_fov->GetFloat());

	if (interfaces::engine->IsInGame() && localplayer)
	{
		debug.display(health, localplayer->health());
		debug.display(moveType, localplayer->moveType());
		debug.display(playerFlags, localplayer->flags());
		
		if (const auto weapon{ localplayer->activeWeapon() })
		{
			debug.display(weaponType, weapontype_to_wstring(weapon->weaponType()));
			debug.display(defIndex, weapon->itemDefinitionIndex());
		}
		
		int players{};
		for (int i{ 1 }; i < interfaces::engine->GetMaxClients(); i++)
		{
			if (interfaces::entityList->GetClientEntity(i))
				players++;
		}

		int ents{};
		for (int i{ 1 }; i < interfaces::entityList->GetMaxEntities(); i++)
		{
			if (interfaces::entityList->GetClientEntity(i))
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
		debug.hide(maxPlayers);
		debug.hide(maxEnts);
	}

	debug.draw();
}

void infopanel()
{
	if (!infoFont && !set_font(infoFont, 20))
		return;
	interfaces::surface->DrawSetTextFont(infoFont);

	interfaces::engine->GetScreenSize(screenW, screenH);
	
	int wide, tall;
	interfaces::surface->GetTextSize(infoFont, L"Romulus", wide, tall);

	wide *= 2;

	static DynamicPanel watermark{ L"Romulus", infoFont, screenW - wide - 13 , 3, wide + 10 };

	watermark.draw();

	if (config::drawDebugPanel)
		debugpanel();
}