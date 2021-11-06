#pragma once

#include "helper.h"

class INetChannelInfo
{
public:
	VIRTUAL_METHOD(float, GetLatency, 9, (int flow), (this, flow))

	char pad0[44];
	int chokedPackets;
};