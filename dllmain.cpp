#pragma warning(disable : 4100)
#include <stdexcept>
#include <Windows.h>

#include "hooks.h"
#include "interfaces.h"
#include "netvars.h"

DWORD WINAPI init(HMODULE hModule)
{
    while (!GetModuleHandleA("serverbrowser.dll"))
        Sleep(1000);

    try
    {
        interfaces::init();
        netvars::init();
        hooks::init();
    }
    catch (const std::exception& e)
    {
        MessageBoxA(NULL, e.what(), NULL, MB_OK | MB_ICONWARNING);
    }

    while (!(GetAsyncKeyState(VK_END) & 1))
        Sleep(1000);

    hooks::restore();

    FreeLibraryAndExitThread(hModule, 0);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);
        CreateThread(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(init), hModule, NULL, NULL);
    }
    return TRUE;
}