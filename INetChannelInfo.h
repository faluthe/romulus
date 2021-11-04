#pragma once

#include "helper.h"

class INetChannelInfo
{
public:
	float GetLatency(int flow)
	{
		return call_virtual_method<float(__thiscall*)(void*, int)>(this, NCI_LATENCY)(this, flow);
	}

	char pad0[44];
	int chokedPackets;
};