#pragma warning(disable : 26812)
#include <MinHook.h>
#include <stdexcept>

#include "helper.h"
#include "Hook.h"
#include "hooks.h"
#include "interfaces.h"

void(__thiscall* oPaintTraverse)(IPanel*, unsigned int, bool, bool);

void __stdcall hkPaintTraverse(unsigned int panel, bool forceRepaint, bool allowRepaint)
{
	oPaintTraverse(interfaces::panel, panel, forceRepaint, allowRepaint);
	auto panelName{ interfaces::panel->GetName(panel) };
	if (!strcmp(panelName, "MatSystemTopPanel"))
	{
		interfaces::surface->SetColor(255, 255, 255, 255);
		interfaces::surface->DrawFilledRect(100, 100, 100, 100);
	}
}

namespace hooks
{
	void init()
	{
		if (MH_Initialize() != MH_OK)
			throw std::runtime_error("Minhook error.");

		panel = Hook{ interfaces::panel };

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