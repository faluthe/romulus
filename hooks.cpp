#pragma warning(disable : 26812)
#include <MinHook.h>
#include <stdexcept>

#include "autopistol.h"
#include "bunnyhop.h"
#include "chams.h"
#include "convars.h"
#include "esp.h"
#include "Hook.h"
#include "hooks.h"
#include "infopanel.h"
#include "interfaces.h"
#include "localplayer.h"

struct CUserCmd;

bool __stdcall hkCreateMove(float inputSampleTime, CUserCmd* cmd)
{
	auto setAngles{ hooks::oCreateMove(inputSampleTime, cmd) };
	if (!cmd->commandNumber)
		return setAngles;

	localplayerUtils::get();

	autopistol(cmd);
	bunnyhop(cmd);
	convars::set();

	return false;
}

void __fastcall hkDrawModelExecute(void* _this, void* _edx, void* context, const ModelRenderInfo_t& state, const ModelRenderInfo_t& pInfo, void* pCustomBoneToWorld)
{
	if (interfaces::mdlRender->IsForcedMaterialOverride())
		return hooks::oDrawModelExecute(_this, _edx, context, state, pInfo, pCustomBoneToWorld);

	chams(_this, _edx, context, state, pInfo, pCustomBoneToWorld);

	hooks::oDrawModelExecute(_this, _edx, context, state, pInfo, pCustomBoneToWorld);

	interfaces::mdlRender->ForcedMaterialOverride(nullptr);
}

void __stdcall hkPaintTraverse(unsigned int panel, bool forceRepaint, bool allowRepaint)
{
	hooks::oPaintTraverse(interfaces::panel, panel, forceRepaint, allowRepaint);
	
	auto panelName{ interfaces::panel->GetName(panel) };
	if (!strcmp(panelName, "MatSystemTopPanel"))
	{
		render_esp();
		infopanel();
	}
}

namespace hooks
{
	void init()
	{
		if (MH_Initialize() != MH_OK)
			throw std::runtime_error("Minhook error.");

		clientMode = Hook{ interfaces::clientMode };
		mdlRender = Hook{ interfaces::mdlRender };
		panel = Hook{ interfaces::panel };

		clientMode.hookFunc(INDEX_CREATE_MOVE, &hkCreateMove, reinterpret_cast<void**>(&oCreateMove));
		mdlRender.hookFunc(INDEX_DME, &hkDrawModelExecute, reinterpret_cast<void**>(&oDrawModelExecute));
		panel.hookFunc(INDEX_PAINT_T, &hkPaintTraverse, reinterpret_cast<void**>(&oPaintTraverse));

		if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
			throw std::runtime_error("Minhook error.");

		convars::spoof();
	}
	
	void restore()
	{
		if (MH_DisableHook(MH_ALL_HOOKS) != MH_OK)
			throw std::runtime_error("Minhook error.");
		
		if (MH_Uninitialize() != MH_OK)
			throw std::runtime_error("Minhook error.");

		convars::restore();
	}
}