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
    using namespace interfaces;
    surface->DrawSetTextColor(col.r, col.g, col.b, col.a);
    surface->DrawSetTextPos(x, y);
    surface->DrawPrintText(text.c_str(), text.size());
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

bool screen_transform(const Vector& in, Vector& out)
{
    static auto& matrix{ interfaces::engine->WorldToScreenMatrix() };

    out.x = matrix[0][0] * in.x + matrix[0][1] * in.y + matrix[0][2] * in.z + matrix[0][3];
    out.y = matrix[1][0] * in.x + matrix[1][1] * in.y + matrix[1][2] * in.z + matrix[1][3];
    out.z = 0.0f;

    float w{ matrix[3][0] * in.x + matrix[3][1] * in.y + matrix[3][2] * in.z + matrix[3][3] };

    if (w < 0.001f)
    {
        out.x *= 100000;
        out.y *= 100000;
        return false;
    }

    out.x /= w;
    out.y /= w;

    return true;
}

bool world_to_screen(const Vector& in, Vector& out)
{
    if (screen_transform(in, out))
    {
        int width, height;
        interfaces::engine->GetScreenSize(width, height);

        out.x = (width / 2.0f) + (out.x * width) / 2.0f;
        out.y = (height / 2.0f) - (out.y * height) / 2.0f;

        return true;
    }
    return false;
}

void transform_vector(const Vector& in1, Matrix& in2, Vector& out)
{
    out[0] = in1.Dot(in2[0]) + in2[0][3];
    out[1] = in1.Dot(in2[1]) + in2[1][3];
    out[2] = in1.Dot(in2[2]) + in2[2][3];
}