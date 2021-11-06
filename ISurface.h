#pragma once

#include "Color.h"
#include "helper.h"

class ISurface
{
public:
	VIRTUAL_METHOD(void, DrawSetColor, 15, (int r, int g, int b, int a), (this, r, g, b, a))
	VIRTUAL_METHOD(void, DrawFilledRect, 16, (int x0, int y0, int x1, int y1), (this, x0, y0, x1, y1))
	VIRTUAL_METHOD(void, DrawOutlinedRect, 18, (int x0, int y0, int x1, int y1), (this, x0, y0, x1, y1))
	VIRTUAL_METHOD(void, DrawLine, 19, (int x0, int y0, int x1, int y1), (this, x0, y0, x1, y1))
	VIRTUAL_METHOD(void, DrawSetTextFont, 23, (unsigned long font), (this, font))
	VIRTUAL_METHOD(void, DrawSetTextColor, 25, (int r, int g, int b, int a), (this, r, g, b, a))
	VIRTUAL_METHOD(void, DrawSetTextPos, 26, (int x, int y), (this, x, y))
	VIRTUAL_METHOD(void, DrawPrintText, 28, (const wchar_t* text, int len), (this, text, len, 0)) // drawType
	VIRTUAL_METHOD(unsigned long, TextCreateFont, 71, (), (this))
	VIRTUAL_METHOD(bool, SetFontGlyphSet, 72, (unsigned long font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags, int nRangeMin = 0, int nRangeMax = 0), (this, font, windowsFontName, tall, weight, blur, scanlines, flags, nRangeMin, nRangeMax))
	VIRTUAL_METHOD(void, GetTextSize, 79, (unsigned font, const wchar_t* text, int& wide, int& tall), (this, font, text, std::ref(wide), std::ref(tall)))
	
	void DrawSetColor(const Color& color)
	{
		return DrawSetColor(static_cast<unsigned short>(color.r), static_cast<unsigned short>(color.g), static_cast<unsigned short>(color.b), static_cast<unsigned short>(color.a));
	}
};