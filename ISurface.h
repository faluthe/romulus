#pragma once

#include "helper.h"

class ISurface
{
public:
	void SetColor(unsigned short r, unsigned short g, unsigned short b, unsigned short a)
	{
		return call_virtual_method<void(__thiscall*)(void*, unsigned short, unsigned short, unsigned short, unsigned short)>(this, SURFACE_SETCOLOR)(this, r, g, b, a);
	}

	void DrawFilledRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h)
	{
		return call_virtual_method<void(__thiscall*)(void*, unsigned int, unsigned int, unsigned int, unsigned int)>(this, SURFACE_DRAWFILLEDRECT)(this, x, y, w, h);
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
};