#pragma once

#include "helper.h"
#include "INetChannelInfo.h"
#include "Matrix.h"

struct player_info_t;

class IVEngineClient
{
public:
	VIRTUAL_METHOD(void, GetScreenSize, 5, (int& width, int& height), (this, std::ref(width), std::ref(height)))
	VIRTUAL_METHOD(bool, GetPlayerInfo, 8, (int entIndex, player_info_t* pInfo), (this, entIndex, pInfo))
	VIRTUAL_METHOD(int, GetLocalPlayer, 12, (), (this))
	VIRTUAL_METHOD(void, GetViewAngles, 18, (Vector& angles), (this, angles))
	VIRTUAL_METHOD(void, SetViewAngles, 19, (const Vector& angle), (this, std::ref(angle)))
	VIRTUAL_METHOD(int, GetMaxClients, 20, (), (this))
	VIRTUAL_METHOD(bool, IsInGame, 26, (), (this))
	VIRTUAL_METHOD(ViewMatrix&, WorldToScreenMatrix, 37, (), (this))
	VIRTUAL_METHOD(INetChannelInfo*, GetNetChannelInfo, 78, (), (this))
};