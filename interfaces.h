#pragma once

#include "IBaseClientDll.h"
#include "IClientEntityList.h"
#include "ICvar.h"
#include "IEngineTrace.h"
#include "IInput.h"
#include "IMaterialSystem.h"
#include "INetChannel.h"
#include "IPanel.h"
#include "IStudioRender.h"
#include "ISurface.h"
#include "ISurfaceData.h"
#include "IVEngineClient.h"
#include "IVModelInfo.h"
#include "IVModelRender.h"
#include "PlayerMoveHelper.h"
#include "PlayerGameMovement.h"
#include "PlayerPrediction.h"
#include "structs.h"

namespace interfaces
{
	inline IBaseClientDll* client{};
	inline void* clientMode{};
	inline void* clientState{};
	inline ICvar* cvar{};
	inline IVEngineClient* engine{};
	inline IClientEntityList* entityList{};
	inline IEngineTrace* engineTrace{};
	inline PlayerGameMovement* gameMovement{};
	inline CGlobalVarsBase* globalVars{};
	inline IInput* input{};
	inline IMaterialSystem* matSys{};
	inline IVModelInfo* mdlInfo{};
	inline IVModelRender* mdlRender{};
	inline PlayerMoveHelper* moveHelper{};
	inline INetChannel* netChannel{};
	inline IPanel* panel{};
	inline PlayerPrediction* playerPrediction{};
	inline IStudioRender* studioRender{};
	inline ISurface* surface{};
	inline IPhysicsSurfaceProps* surfaceData{};

	void init();
}