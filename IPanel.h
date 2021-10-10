#pragma once

#include "helper.h"

class IPanel
{
public:
    const char* GetName(unsigned int panelId)
    {
        return call_virtual_method<const char* (__thiscall*)(void*, unsigned int)>(this, PANEL_GETNAME)(this, panelId);
    }
};