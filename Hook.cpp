#pragma warning(disable : 26812)
#include <MinHook.h>
#include <stdexcept>
#include <string>

#include "Hook.h"

Hook::Hook(void* pInterface) :
	pInterface{ pInterface }
{
}

void Hook::hookFunc(unsigned short index, void* hkFunc, void** ogFunc)
{
	const auto addr{ (unsigned int)((*(int**)(pInterface))[index]) };

	if (MH_CreateHook((void*)addr, hkFunc, ogFunc) != MH_OK)
		throw std::runtime_error(std::string("Hook failed at: " + addr));
}