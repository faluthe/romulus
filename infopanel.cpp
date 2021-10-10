#include <stdexcept>
#include <string>

#include "config.h"
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

	static Panel debug{ L"Debug", L"", screenW - (screenW / 8), screenH / 2, 220};
	static Panel* health{ debug.add_entry(L"Health") };
	static Panel* flags{ debug.add_entry(L"Flags", std::to_wstring(netvars::flags)) };

	if (localplayer)
	{
		health->set_option(L"Test");
	}

	debug.draw();
}

void infopanel()
{
	if (!infoFont && !set_font(infoFont, 20))
		return;
	interfaces::surface->DrawSetTextFont(infoFont);

	interfaces::engine->GetScreenSize(screenW, screenH);

	print_text(L"Romulus	Mode:", screenW - (screenW / 5), 10, colors::white);
	print_text(std::to_wstring(config::mode).c_str(), screenW - (screenW / 8), 10, colors::white);
	
	if (config::mode == 0)
		debugpanel();
}