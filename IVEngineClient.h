#pragma once

#include "helper.h"

class IVEngineClient
{
public:
	void GetScreenSize(int& width, int& height)
	{
		return call_virtual_method<void(__thiscall*)(void*, int&, int&)>(this, ENGINE_GETSCREENSIZE)(this, width, height);
	}
};