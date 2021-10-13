#pragma once

#include "helper.h"

class IVEngineClient
{
public:
	void GetScreenSize(int& width, int& height)
	{
		return call_virtual_method<void(__thiscall*)(void*, int&, int&)>(this, ENGINE_GETSCREENSIZE)(this, width, height);
	}
	
	int GetLocalPlayer()
	{
		return call_virtual_method<int(__thiscall*)(void*)>(this, ENGINE_GETLOCALENT)(this);
	}

	int GetMaxClients()
	{
		return call_virtual_method<int(__thiscall*)(void*)>(this, ENGINE_MAXCLIENTS)(this);
	}
};