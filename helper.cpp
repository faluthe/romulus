#include <string>
#include <vector>

#include "Entity.h"
#include "helper.h"
#include "interfaces.h"

bool set_font(unsigned long& font, int size, int weight)
{
    font = interfaces::surface->TextCreateFont();
    return interfaces::surface->SetFontGlyphSet(font, "Tahoma", size, weight, 0, 0, 0x200);
}

void print_text(std::wstring text, int x, int y, const Color& col, unsigned long font, bool centered)
{
    using namespace interfaces;
    
    surface->DrawSetTextFont(font);
    surface->DrawSetTextColor(col.r, col.g, col.b, col.a);
    
    if (centered)
    {
        int wide, tall;
        surface->GetTextSize(font, text.c_str(), wide, tall);
        surface->DrawSetTextPos(x - (wide / 2), y - (tall / 2));
    }
    else
        surface->DrawSetTextPos(x, y);
    
    surface->DrawPrintText(text.c_str(), text.size());
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

void vector_angles(const Vector& forward, Vector& angles)
{
    Vector view;
    if (forward[1] == 0.0f && forward[0] == 0.0f)
    {
        view[0] = 0.0f;
        view[1] = 0.0f;
    }
    else
    {
        view[1] = std::atan2(forward[1], forward[0]) * 180.0f / static_cast<float>(3.14159265358979323846);

        if (view[1] < 0.0f)
            view[1] += 360.0f;

        view[2] = std::sqrt(forward[0] * forward[0] + forward[1] * forward[1]);

        view[0] = std::atan2(forward[2], view[2]) * 180.0f / static_cast<float>(3.14159265358979323846);
    }

    angles[0] = -view[0];
    angles[1] = view[1];
    angles[2] = 0.0f;
}

void angle_vectors(Vector& angles, Vector& forward)
{
    float sp, sy, cp, cy;

    sy = sin(DEG2RAD(angles[1]));
    cy = cos(DEG2RAD(angles[1]));

    sp = sin(DEG2RAD(angles[0]));
    cp = cos(DEG2RAD(angles[0]));

    forward.x = cp * cy;
    forward.y = cp * sy;
    forward.z = -sp;
}

float normalizeVector(Vector& v)
{
    float length{ v.Length() };
    if (length != 0.0f)
        v /= length;
    else
        v.x = v.y = 0.0f; v.z = 1.0f;
    return length;
}

void sin_cos(float r, float* s, float* c)
{
    *s = sin(r);
    *c = cos(r);
}

constexpr float RAD2DEG(const float x) 
{
    return (float)(x) * (float)(180.f / static_cast<float>(3.14159265358979323846));
}

constexpr float DEG2RAD(const float x) 
{
    return (float)(x) * (float)(static_cast<float>(3.14159265358979323846) / 180.f);
}

Vector VectortoFart(const Vector& v)
{
    return Vector{ RAD2DEG(std::atan2(-v.z, std::hypot(v.x, v.y))), RAD2DEG(std::atan2(v.y, v.x)), 0.0f };
}

void angle_vectors(const Vector& angles, Vector& forward)
{
    float sp, sy, cp, cy;

    sin_cos(DEG2RAD(angles[0]), &sp, &cp);
    sin_cos(DEG2RAD(angles[1]), &sy, &cy);

    forward.x = cp * cy;
    forward.y = cp * sy;
    forward.z = -sp;
}

float get_fov(const Vector& viewAngle, const Vector& aimAngle)
{
    Vector view, aim;

    angle_vectors(viewAngle, view);
    angle_vectors(aimAngle, aim);

    return RAD2DEG(acos(view.Dot(aim) / view.LengthSqr()));
}

Vector Subtract(const Vector& source, const Vector& destination)
{
    Vector difference;
    difference.x = source.x - destination.x;
    difference.y = source.y - destination.y;
    difference.z = source.z - destination.z;
    return difference;
}

float Magnitude(const Vector& vector)
{
    return sqrtf(vector.x * vector.x + vector.y * vector.y + vector.z + vector.z);
}

float Distance(const Vector& source, const Vector& destination)
{
    Vector difference{ Subtract(source, destination) };
    return Magnitude(difference);
}

Vector CalcAngle(const Vector& source, const Vector& destination)
{
    Vector angle;
    angle.x = -atan2f(destination.x - source.x, destination.y - source.y) / 3.1415927f * 180.0f + 180.0f;
    angle.y = asinf((destination.z, source.z) / Distance(source, destination)) * 180.0f / 3.1415927f;
    angle.z = 0.0f;

    return angle;
}

std::uint8_t* pattern_scan(const char* module_name, const char* signature) // Pasted asf
{
    const auto module_handle = GetModuleHandleA(module_name);

    if (!module_handle)
        return nullptr;

    static auto pattern_to_byte = [](const char* pattern) {
        auto bytes = std::vector<int>{};
        auto start = const_cast<char*>(pattern);
        auto end = const_cast<char*>(pattern) + std::strlen(pattern);

        for (auto current = start; current < end; ++current) {
            if (*current == '?') {
                ++current;

                if (*current == '?')
                    ++current;

                bytes.push_back(-1);
            }
            else {
                bytes.push_back(std::strtoul(current, &current, 16));
            }
        }
        return bytes;
    };

    auto dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(module_handle);
    auto nt_headers =
        reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<std::uint8_t*>(module_handle) + dos_header->e_lfanew);

    auto size_of_image = nt_headers->OptionalHeader.SizeOfImage;
    auto pattern_bytes = pattern_to_byte(signature);
    auto scan_bytes = reinterpret_cast<std::uint8_t*>(module_handle);

    auto s = pattern_bytes.size();
    auto d = pattern_bytes.data();

    for (auto i = 0ul; i < size_of_image - s; ++i) {
        bool found = true;

        for (auto j = 0ul; j < s; ++j) {
            if (scan_bytes[i + j] != d[j] && d[j] != -1) {
                found = false;
                break;
            }
        }
        if (found)
            return &scan_bytes[i];
    }

    return 0;
}