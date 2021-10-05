#include <stdexcept>
#include <string>
#include <Windows.h>

#include "interfaces.h"
#include "IPanel.h"
#include "ISurface.h"

typedef	void* (*CreateInterfaceFn)(const char* name, int* returnCode);

template<typename I>
I* get_interface(HMODULE hModule, const char* interfaceVersion)
{
	CreateInterfaceFn f{ reinterpret_cast<CreateInterfaceFn>(GetProcAddress(hModule, "CreateInterface")) };
	auto result = reinterpret_cast<I*>(f(interfaceVersion, nullptr));

	if (!result)
		throw std::runtime_error(std::string("Failed to get interface: ") + interfaceVersion);

	return result;
}

namespace interfaces
{
	void init()
	{
		panel = get_interface<IPanel>(GetModuleHandleA("vgui2.dll"), "VGUI_Panel009");
		surface = get_interface<ISurface>(GetModuleHandleA("vguimatsurface.dll"), "VGUI_Surface031");
	}
}