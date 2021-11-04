#pragma warning(disable : 26812)
#include <MinHook.h>
#include <stdexcept>

#include "backtrack.h"
#include "config.h"
#include "convars.h"
#include "engineprediction.h"
#include "features.h"
#include "Hook.h"
#include "hooks.h"
#include "interfaces.h"
#include "localplayer.h"

struct CUserCmd;

static bool bSendDatagram{ false };

int __fastcall hkSendDatagram(INetChannel* netchannel, void*, void* datagram)
{
	if (!interfaces::engine->IsInGame())
	{
		backtrack::lastSequence = 0;
		return hooks::oSendDatagram(netchannel, datagram);
	}

	if (datagram)
		return hooks::oSendDatagram(netchannel, datagram);

	int inState{ netchannel->m_nInReliableState };
	int inSequenceNr{ netchannel->m_nInSequenceNr };
	
	backtrack::addLatencyToNetChan(netchannel, 0.2f);
	int og{ hooks::oSendDatagram(netchannel, datagram) };

	netchannel->m_nInReliableState = inState;
	netchannel->m_nInSequenceNr = inSequenceNr;

	return og;
}

bool __stdcall hkCreateMove(float inputSampleTime, CUserCmd* cmd)
{
	auto setAngles{ hooks::oCreateMove(inputSampleTime, cmd) };
	if (!cmd || !cmd->commandNumber)
		return setAngles;

	localplayerUtils::get();

	if (!bSendDatagram)
	{
		interfaces::netChannel = *reinterpret_cast<INetChannel**>(reinterpret_cast<uintptr_t>(interfaces::clientState) + 0x9C);
		hooks::netChannel = Hook{ interfaces::netChannel };
		hooks::netChannel.hookFunc(INDEX_SENDDATAGRAM, &hkSendDatagram, reinterpret_cast<void**>(&hooks::oSendDatagram));
		bSendDatagram = true;
	}
	if (bSendDatagram)
		backtrack::updateIncomingSequences();

	autopistol(cmd);
	bunnyhop(cmd);
	convars::set();

	cmd->buttons |= CUserCmd::IN_BULLRUSH; // No crouch cooldown

	static bool initBacktrack = []() { backtrack::init(); return true; } ();

	backtrack::update();
	
	prediction::run(cmd);
	backtrack::run(cmd);

	return false;
}

void __fastcall hkDrawModelExecute(void* _this, void* _edx, void* context, const ModelRenderInfo_t& state, const ModelRenderInfo_t& pInfo, void* pCustomBoneToWorld)
{
	if (interfaces::studioRender->IsForcedMaterialOverride())
		return hooks::oDrawModelExecute(_this, _edx, context, state, pInfo, pCustomBoneToWorld);

	chams(_this, _edx, context, state, pInfo, pCustomBoneToWorld);

	hooks::oDrawModelExecute(_this, _edx, context, state, pInfo, pCustomBoneToWorld);

	interfaces::mdlRender->ForcedMaterialOverride(nullptr);
}

void __stdcall hkFrameStageNotify(client_frame_stage_t frameStage)
{
	localplayerUtils::get();
	static auto setInterpolationFlags = [](Entity* ent, int flag) {
		const auto varMap{ (uintptr_t)ent + 36 };
		const auto szVarMap{ *(int*)(varMap + 20) };
		for (auto index = 0; index < szVarMap; index++)
			*(uintptr_t*)((*(uintptr_t*)varMap) + index * 12) = flag;
	};
	switch (frameStage)
	{
	case client_frame_stage_t::FRAME_NET_UPDATE_END:
		if (localplayer && localplayer->isAlive())
		{
			for (int i = 1; i <= interfaces::engine->GetMaxClients(); i++)
			{
				const auto ent{ interfaces::entityList->GetClientEntity(i) };
				if (!ent || ent->team() == localplayer->team() || ent->dormant())
					continue;
				setInterpolationFlags(ent, 0);
			}
		}
		break;
	default: break;
	}
	hooks::oFrameStageNotify(interfaces::client, frameStage);
}

void __stdcall hkPaintTraverse(unsigned int panel, bool forceRepaint, bool allowRepaint)
{
	hooks::oPaintTraverse(interfaces::panel, panel, forceRepaint, allowRepaint);
	
	auto panelName{ interfaces::panel->GetName(panel) };
	if (!strcmp(panelName, "MatSystemTopPanel"))
	{
		render_esp();
		external_xhair();
		infopanel();
		config::display();
	}
}

namespace hooks
{
	void init()
	{
		if (MH_Initialize() != MH_OK)
			throw std::runtime_error("Minhook error.");

		client = Hook{ interfaces::client };
		clientMode = Hook{ interfaces::clientMode };
		mdlRender = Hook{ interfaces::mdlRender };
		panel = Hook{ interfaces::panel };

		client.hookFunc(INDEX_FRAMESTAGENOTIFY, &hkFrameStageNotify, reinterpret_cast<void**>(&oFrameStageNotify));
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