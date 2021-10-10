#pragma warning(disable : 26812)
#include <MinHook.h>
#include <stdexcept>

#include "bunnyhop.h"
#include "CUserCmd.h"
#include "helper.h"
#include "Hook.h"
#include "hooks.h"
#include "infopanel.h"
#include "interfaces.h"

bool(__stdcall* oCreateMove)(float, CUserCmd*);
void(__thiscall* oPaintTraverse)(IPanel*, unsigned int, bool, bool);

void __stdcall hkPaintTraverse(unsigned int panel, bool forceRepaint, bool allowRepaint)
{
	oPaintTraverse(interfaces::panel, panel, forceRepaint, allowRepaint);
	auto panelName{ interfaces::panel->GetName(panel) };
	if (!strcmp(panelName, "MatSystemTopPanel"))
	{
		infopanel();
	}
}

bool __stdcall hkCreateMove(float inputSampleTime, CUserCmd* cmd)
{
	auto setAngles{ oCreateMove(inputSampleTime, cmd) };
	if (!cmd->commandNumber)
		return setAngles;

	bunnyhop(cmd);

	return false;
}

namespace hooks
{
	void init()
	{
		if (MH_Initialize() != MH_OK)
			throw std::runtime_error("Minhook error.");
		
		clientMode = Hook{ interfaces::clientMode };
		panel = Hook{ interfaces::panel };

		clientMode.hookFunc(INDEX_CREATE_MOVE, &hkCreateMove, (void**)&oCreateMove);
		panel.hookFunc(INDEX_PAINT_T, &hkPaintTraverse, (void**)&oPaintTraverse);

		if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
			throw std::runtime_error("Minhook error.");
	}
	
	void restore()
	{
		if (MH_DisableHook(MH_ALL_HOOKS) != MH_OK)
			throw std::runtime_error("Minhook error.");
		
		if (MH_Uninitialize() != MH_OK)
			throw std::runtime_error("Minhook error.");
	}
}