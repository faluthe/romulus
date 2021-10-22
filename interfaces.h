#pragma once

#include "IBaseClientDll.h"
#include "IClientEntityList.h"
#include "ICvar.h"
#include "IEngineTrace.h"
#include "IMaterialSystem.h"
#include "IPanel.h"
#include "ISurface.h"
#include "IVEngineClient.h"
#include "IVModelInfo.h"
#include "IVModelRender.h"

namespace interfaces
{
	inline IBaseClientDll* client{};
	inline void* clientMode{};
	inline ICvar* cvar{};
	inline IVEngineClient* engine{};
	inline IClientEntityList* entityList{};
	inline IEngineTrace* engineTrace{};
	inline IMaterialSystem* matSys{};
	inline IVModelInfo* mdlInfo{};
	inline IVModelRender* mdlRender{};
	inline IPanel* panel{};
	inline ISurface* surface{};

	void init();
}