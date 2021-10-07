#include <stdexcept>
#include <string>

#include "config.h"
#include "helper.h"
#include "infopanel.h"
#include "interfaces.h"
#include "Panel.h"

unsigned long infoFont{};
int screenW, screenH;

void debugpanel()
{
	static Panel debug{ L"Debug", L"...", screenW - (screenW / 8), screenH / 2, 220};
	static bool e{};
	if (!e)
	{
		debug.add_entry(L"Width", std::to_wstring(screenW));
		debug.add_entry(L"Height", std::to_wstring(screenH));
		debug.add_entry(L"Thomas", L"is awesome");
		e = true;
	}
	debug.draw();

	static Panel thomasPanel{ L"Thomas", L"", 100, 100, 500, 50 };
	static bool e2{};
	if (!e2)
	{
		thomasPanel.add_entry(L"hello", std::to_wstring(50.0f));
		e2 = true;
	}
	thomasPanel.draw();
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