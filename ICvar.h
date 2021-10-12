#pragma once

#include "ConVar.h"
#include "helper.h"

class ICvar
{
public:
	void RegisterConCommand(void* pCommandBase)
	{
		return call_virtual_method<void(__thiscall*)(void*, void*, int)>(this, ICVAR_REGISTER)(this, pCommandBase, 1);
	}

	void UnregisterConCommand(void* pCommandBase)
	{
		return call_virtual_method<void(__thiscall*)(void*, void*)>(this, ICVAR_UNREGISTER)(this, pCommandBase);
	}

	ConVar* FindVar(const char* varName)
	{
		return call_virtual_method<ConVar* (__thiscall*)(void*, const char*)>(this, ICVAR_FINDVAR)(this, varName);
	}
};