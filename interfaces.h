#pragma once

#include "IBaseClientDll.h"
#include "IClientEntityList.h"
#include "ICvar.h"
#include "IMaterialSystem.h"
#include "IPanel.h"
#include "ISurface.h"
#include "IVEngineClient.h"
#include "IVModelRender.h"

namespace interfaces
{
	inline IBaseClientDll* client{};
	inline void* clientMode{};
	inline ICvar* cvar{};
	inline IVEngineClient* engine{};
	inline IClientEntityList* entityList{};
	inline IMaterialSystem* matSys{};
	inline IVModelRender* mdlRender{};
	inline IPanel* panel{};
	inline ISurface* surface{};

	void init();
}