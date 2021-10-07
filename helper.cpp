#include <string>

#include "helper.h"
#include "interfaces.h"

bool set_font(unsigned long& font, int size, int weight)
{
    font = interfaces::surface->TextCreateFont();
    return interfaces::surface->SetFontGlyphSet(font, "Tahoma", size, weight, 0, 0, 0x200);
}

void print_text(const wchar_t* text, int x, int y, const Color& col)
{
    interfaces::surface->DrawSetTextColor(static_cast<int>(col.r), static_cast<int>(col.g), static_cast<int>(col.b), static_cast<int>(col.a));
    interfaces::surface->DrawSetTextPos(x, y);
    interfaces::surface->DrawPrintText(text, wcslen(text));
}