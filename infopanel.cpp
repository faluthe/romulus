#include <stdexcept>
#include <string>

#include "config.h"
#include "helper.h"
#include "infopanel.h"
#include "interfaces.h"

unsigned long infoFont{};
int screenW, screenH;

void debugpanel()
{
	interfaces::surface->DrawSetColor(colors::grey);
	int x0{ screenW - (screenW / 8) };
	int y0{ screenH / 2 };
	int x1{ screenW - 20 };
	int y1{ y0 + 30 };
	interfaces::surface->DrawFilledRect(x0, y0, x1, y1);
	interfaces::surface->DrawSetColor(colors::black);
	interfaces::surface->DrawOutlinedRect(x0 - 1, y0 - 1, x1 + 1, y1 + 1);
	interfaces::surface->DrawLine((x0 + x1) / 2, y0, (x0 + x1) / 2, y1);
	print_text(L"Debug", x0 + 10, y0 + 5, colors::white);
	y0 = y1;
	y1 += 30;
	interfaces::surface->DrawSetColor(colors::grey);
	interfaces::surface->DrawFilledRect(x0, y0, x1, y1);
	interfaces::surface->DrawSetColor(colors::black);
	interfaces::surface->DrawOutlinedRect(x0 - 1, y0 - 1, x1 + 1, y1 + 1);
	interfaces::surface->DrawLine((x0 + x1) / 2, y0, (x0 + x1) / 2, y1);
	print_text(L"Option", x0 + 10, y0 + 5, colors::white);
	print_text(L"...", ((x0 + x1) / 2) + 10, y0 + 5, colors::white);
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