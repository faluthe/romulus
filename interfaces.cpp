#include <stdexcept>
#include <string>
#include <Windows.h>

#include "interfaces.h"

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
		const auto clientDll{ GetModuleHandleA("client.dll") };
		const auto engineDll{ GetModuleHandleA("engine.dll") };

		client = get_interface<IBaseClientDll>(clientDll, "VClient018");
		clientMode = **(void***)((*(uintptr_t**)client)[0xA] + 0x5);
		clientMode = **reinterpret_cast<void***>((*reinterpret_cast<uintptr_t**>(client))[0xA] + 0x5);
		clientState = **reinterpret_cast<void***>(pattern_scan("engine.dll", "A1 ? ? ? ? 8B 80 ? ? ? ? C3") + 1);
		cvar = get_interface<ICvar>(GetModuleHandleA("vstdlib.dll"), "VEngineCvar007");
		engine = get_interface<IVEngineClient>(engineDll, "VEngineClient014");
		entityList = get_interface<IClientEntityList>(clientDll, "VClientEntityList003");
		engineTrace = get_interface<IEngineTrace>(engineDll, "EngineTraceClient004");
		gameMovement = get_interface<PlayerGameMovement>(clientDll, "GameMovement001");
		globalVars = **reinterpret_cast<CGlobalVarsBase***>((*reinterpret_cast<uintptr_t**>(client))[0xB] + 0xA);
		input = *reinterpret_cast<IInput**>((*reinterpret_cast<uintptr_t**>(client))[0x10] + 0x1);
		matSys = get_interface<IMaterialSystem>(GetModuleHandleA("materialsystem.dll"), "VMaterialSystem080");
		mdlInfo = get_interface<IVModelInfo>(engineDll, "VModelInfoClient004");
		mdlRender = get_interface<IVModelRender>(engineDll, "VEngineModel016");
		moveHelper = **reinterpret_cast<PlayerMoveHelper***>(pattern_scan("client.dll", "8B 0D ? ? ? ? 8B 46 08 68") + 2);
		panel = get_interface<IPanel>(GetModuleHandleA("vgui2.dll"), "VGUI_Panel009");
		playerPrediction = get_interface<PlayerPrediction>(clientDll, "VClientPrediction001");
		studioRender = get_interface<IStudioRender>(GetModuleHandleA("studiorender.dll"), "VStudioRender026");
		surface = get_interface<ISurface>(GetModuleHandleA("vguimatsurface.dll"), "VGUI_Surface031");
		surfaceData = get_interface<IPhysicsSurfaceProps>(GetModuleHandleA("vphysics.dll"), "VPhysicsSurfaceProps001");
	}
}