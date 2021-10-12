#include <stdexcept>
#include <string>
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
	Entity* localplayer{ interfaces::entityList->GetClientEntity(interfaces::engine->GetLocalPlayer()) };

	static Panel debug{ L"Debug", L"", screenW - (screenW / 7), screenH / 2 };
	
	static Panel health{ debug.add_entry(&health, L"Health") };
	static Panel flags{ debug.add_entry(&flags, L"Flags", std::to_wstring(netvars::flags)) };
	static Panel playerFlags{ debug.add_entry(&playerFlags, L"Player Flags") };
	static Panel viewmodel{ debug.add_entry(&viewmodel, L"viewmodel_fov") };
	static Panel moveType{ debug.add_entry(&moveType, L"Move Type") };

	viewmodel.set_option(convars::viewmodel_fov->GetValue());

	if (localplayer)
	{
		health.set_option(localplayer->health());
		playerFlags.set_option(localplayer->flags());
		moveType.set_option(localplayer->moveType());
	}

	debug.draw();
}

void infopanel()
{
	if (!infoFont && !set_font(infoFont, 20))
		return;
	interfaces::surface->DrawSetTextFont(infoFont);

	interfaces::engine->GetScreenSize(screenW, screenH);

	static Panel info{ L"Romulus", L"", screenW - (screenW / 5), 1 };
	info.set_option(config::mode);
	info.draw();

	if (config::mode == 0)
		debugpanel();
}