#pragma once

#include "CUserCmd.h"
#include "Hook.h"
#include "IPanel.h"

class INetChannel;
struct ModelRenderInfo_t;

enum class client_frame_stage_t {
	FRAME_UNDEFINED = -1,			// (haven't run any frames yet)
	FRAME_START,

	// A network packet is being recieved
	FRAME_NET_UPDATE_START,
	// Data has been received and we're going to start calling PostDataUpdate
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	// Data has been received and we've called PostDataUpdate on all data recipients
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	// We've received all packets, we can now do interpolation, prediction, etc..
	FRAME_NET_UPDATE_END,

	// We're about to start rendering the scene
	FRAME_RENDER_START,
	// We've finished rendering the scene.
	FRAME_RENDER_END
};

namespace hooks
{
	inline Hook client;
	inline Hook clientMode;
	inline Hook mdlRender;
	inline Hook netChannel;
	inline Hook panel;

	// Originals
	inline bool(__stdcall* oCreateMove)(float, CUserCmd*);
	inline void(__thiscall* oPaintTraverse)(IPanel*, unsigned int, bool, bool);
	inline void(__fastcall* oDrawModelExecute)(void*, void*, void*, const ModelRenderInfo_t&, const ModelRenderInfo_t&, void*);
	inline void(__thiscall* oFrameStageNotify)(void*, client_frame_stage_t);
	inline int(__thiscall* oSendDatagram)(INetChannel*, void*);

	void init();
	void restore();
}