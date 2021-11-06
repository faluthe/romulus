#pragma once

#include <cstdarg>

#include "ConVar.h"
#include "helper.h"

class ICvar
{
public:
	virtual void* Connect() = 0;
	virtual void* Disconnect() = 0;
	virtual void* QueryInterface() = 0;
	virtual void* Init() = 0;
	virtual void* Shutdown() = 0;
	virtual void* GetDependencies() = 0;
	virtual void* GetTier() = 0;
	virtual void* Reconnect() = 0;
	virtual void* UnkFunc() = 0; // 8
	virtual void* AllocateDLLIdentifier() = 0;
	virtual void* RegisterConCommand(void* pCommandBase, int unk = 1) = 0;
	virtual void* UnregisterConCommand(void* pCommandBase) = 0;
	virtual void* UnregisterConCommands() = 0;
	virtual void* GetCommandLineValue() = 0;
	virtual void* FindCommandBase() = 0;
	virtual void* FindCommandBase2() = 0;
	virtual ConVar* FindVar(const char* varName) = 0; // 16
	virtual void* FindVar2() = 0;
	virtual void* FindCommand() = 0;
	virtual void* FindCommand2() = 0;
	virtual void* func19() = 0;
	virtual void* func20() = 0;
	virtual void* func21() = 0;
	virtual void* func22() = 0;
	virtual void* func23() = 0;
	virtual void* ConsoleColorPrintf(const uint8_t* color, const char* pFormat, ...) const = 0;
	virtual void* ConsolePrintf(const char* pFormat, ...) const = 0;


	/*void RegisterConCommand(void* pCommandBase)
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

	void ConsolePrintf(const char* format, ...)
	{
		return call_virtual_method<void(__thiscall*)(void*, const char*)>(this, 26)(this, format);
	}*/
};