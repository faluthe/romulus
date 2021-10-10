#pragma once

#include "IBaseClientDll.h"
#include "IClientEntityList.h"
#include "IPanel.h"
#include "ISurface.h"
#include "IVEngineClient.h"

namespace interfaces
{
	inline IBaseClientDll* client{};
	inline void* clientMode{};
	inline IVEngineClient* engine{};
	inline IClientEntityList* entityList{};
	inline IPanel* panel{};
	inline ISurface* surface{};

	void init();
}