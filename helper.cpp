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

std::wstring weapontype_to_wstring(int type)
{
    switch (type)
    {
    case 0:
        return L"Knife(0)";
    case 1:
        return L"Pistol(1)";
    case 2:
        return L"SMG(2)";
    case 3:
        return L"Rifle(3)";
    case 4:
        return L"Shotgun(4)";
    case 5:
        return L"Sniper(5)";
    case 6:
        return L"Machine Gun(6)";
    default:
        return L"Error(" + std::to_wstring(type) + L")";
    }
}