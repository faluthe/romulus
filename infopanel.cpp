#include <stdexcept>
#include <string>

#include "infopanel.h"
#include "interfaces.h"

unsigned long infoFont{};

bool set_font(unsigned long& font, int size)
{
	font = interfaces::surface->TextCreateFont();
	return interfaces::surface->SetFontGlyphSet(font, "Tahoma", size, 550, 0, 0, 0x200);
}

void infopanel()
{
	if (!set_font(infoFont, 20))
		return;

	interfaces::surface->DrawSetTextFont(infoFont);
	interfaces::surface->DrawSetTextColor(255, 255, 255, 255);
	interfaces::surface->DrawSetTextPos(100, 100);
	interfaces::surface->DrawPrintText(L"Hello World", wcslen(L"Hello World"));
}