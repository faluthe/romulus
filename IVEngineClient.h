#pragma once

#include "helper.h"
#include "Matrix.h"

struct player_info_t;

class IVEngineClient
{
public:
	void GetScreenSize(int& width, int& height)
	{
		return call_virtual_method<void(__thiscall*)(void*, int&, int&)>(this, ENGINE_GETSCREENSIZE)(this, width, height);
	}

	bool GetPlayerInfo(int entNum, player_info_t* info)
	{
		return call_virtual_method<bool(__thiscall*)(void*, int, player_info_t*)>(this, ENGINE_PLAYERINFO)(this, entNum, info);
	}
	
	int GetLocalPlayer()
	{
		return call_virtual_method<int(__thiscall*)(void*)>(this, ENGINE_GETLOCALENT)(this);
	}

	int GetMaxClients()
	{
		return call_virtual_method<int(__thiscall*)(void*)>(this, ENGINE_MAXCLIENTS)(this);
	}

	bool IsInGame()
	{
		return call_virtual_method<bool(__thiscall*)(void*)>(this, ENGINE_INGAME)(this);
	}

	ViewMatrix& WorldToScreenMatrix()
	{
		return call_virtual_method<ViewMatrix& (__thiscall*)(void*)>(this, ENGINE_W2SMATRIX)(this);
	}
};