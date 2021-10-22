#pragma once

#include "CUserCmd.h"
#include "Hook.h"
#include "IPanel.h"

struct ModelRenderInfo_t;

namespace hooks
{
	inline Hook clientMode;
	inline Hook mdlRender;
	inline Hook panel;

	// Originals
	inline bool(__stdcall* oCreateMove)(float, CUserCmd*);
	inline void(__thiscall* oPaintTraverse)(IPanel*, unsigned int, bool, bool);
	inline void(__fastcall* oDrawModelExecute)(void*, void*, void*, const ModelRenderInfo_t&, const ModelRenderInfo_t&, void*);

	void init();
	void restore();
}