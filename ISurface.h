#pragma once

#include "Color.h"
#include "helper.h"

class ISurface
{
public:
	void DrawSetColor(unsigned short r, unsigned short g, unsigned short b, unsigned short a)
	{
		return call_virtual_method<void(__thiscall*)(void*, unsigned short, unsigned short, unsigned short, unsigned short)>(this, SURFACE_SETCOLOR)(this, r, g, b, a);
	}

	void DrawSetColor(const Color& color)
	{
		return DrawSetColor(static_cast<unsigned short>(color.r), static_cast<unsigned short>(color.g), static_cast<unsigned short>(color.b), static_cast<unsigned short>(color.a));
	}

	void DrawFilledRect(int x0, int y0, int x1, int y1)
	{
		return call_virtual_method<void(__thiscall*)(void*, int, int, int, int)>(this, SURFACE_DRAWFILLEDRECT)(this, x0, y0, x1, y1);
	}

	void DrawOutlinedRect(int x0, int y0, int x1, int y1)
	{
		return call_virtual_method<void(__thiscall*)(void*, int, int, int, int)>(this, SURFACE_DRAWOUTLINEDRECT)(this, x0, y0, x1, y1);
	}

	void DrawLine(int x0, int y0, int x1, int y1)
	{
		return call_virtual_method<void(__thiscall*)(void*, int, int, int, int)>(this, SURFACE_DRAWLINE)(this, x0, y0, x1, y1);
	}

	void DrawSetTextFont(unsigned long font)
	{
		return call_virtual_method<void(__thiscall*)(void*, unsigned long)>(this, SURFACE_TEXTSETFONT)(this, font);
	}

	void DrawSetTextColor(int r, int g, int b, int a)
	{
		return call_virtual_method<void(__thiscall*)(void*, int, int, int, int)>(this, SURFACE_TEXTSETCOL)(this, r, g, b, a);
	}

	void DrawSetTextPos(int x, int y)
	{
		return call_virtual_method<void(__thiscall*)(void*, int, int)>(this, SURFACE_TEXTSETPOS)(this, x, y);
	}

	void DrawPrintText(const wchar_t* text, int len)
	{
		return call_virtual_method<void(__thiscall*)(void*, const wchar_t*, unsigned int, unsigned int)>(this, SURFACE_TEXTPRINT)(this, text, len, 0); // drawType third argument, default=0
	}

	unsigned long TextCreateFont()
	{
		return call_virtual_method<unsigned long(__thiscall*)(void*)>(this, SURFACE_TEXTCREATEFONT)(this);
	}

	bool SetFontGlyphSet(unsigned long font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags, int nRangeMin = 0, int nRangeMax = 0)
	{
		return call_virtual_method<bool(__thiscall*)(void*, unsigned long, const char*, int, int, int, int, int, int, int)>(this, SURFACE_SETGLYPH)(this, font, windowsFontName, tall, weight, blur, scanlines, flags, nRangeMin, nRangeMax);
	}

	void GetTextSize(unsigned int font, const wchar_t* text, int& wide, int& tall)
	{
		return call_virtual_method<void(__thiscall*)(void*, unsigned int, const wchar_t*, int&, int&)>(this, SURFACE_GETSIZE)(this, font, text, wide, tall);
	}
};