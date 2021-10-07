#include <string>

#include "helper.h"
#include "interfaces.h"

bool set_font(unsigned long& font, int size, int weight)
{
    font = interfaces::surface->TextCreateFont();
    return interfaces::surface->SetFontGlyphSet(font, "Tahoma", size, weight, 0, 0, 0x200);
}

void print_text(std::wstring text, int x, int y, const Color& col)
{
    interfaces::surface->DrawSetTextColor(col.r, col.g, col.b, col.a);
    interfaces::surface->DrawSetTextPos(x, y);
    interfaces::surface->DrawPrintText(text.c_str(), text.size());
}