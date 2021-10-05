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
};