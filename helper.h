#pragma once

#include <string>

#include "Color.h"

// Hook indexes
#define INDEX_CREATE_MOVE 24
#define INDEX_DME 21
#define INDEX_PAINT_T 41

/* 
  Valve SDK indexes 
*/

// ConVar
#define CONVAR_GETVALUE 13
#define CONVAR_SETVALUE 16

// Entity
#define ENTITY_ACTIVE_WEAPON 268
#define ENTITY_WEAPON_TYPE 455

// IClientEntityList
#define ENTLIST_GETENT 3

// ICvar
#define ICVAR_REGISTER 10
#define ICVAR_UNREGISTER 11
#define ICVAR_FINDVAR 15

// IBaseClientDll
#define BASECLIENT_GETALL 8

// IMaterial
#define IMAT_ALPHAMOD 27
#define IMAT_COLORMOD 28
#define IMAT_SETMATFLAG 29

// IMaterialSystem
#define IMATSYS_FINDMAT 84

// IPanel
#define PANEL_GETNAME 36

// ISurface
#define SURFACE_SETCOLOR 15
#define SURFACE_DRAWFILLEDRECT 16
#define SURFACE_DRAWOUTLINEDRECT 18
#define SURFACE_DRAWLINE 19
#define SURFACE_TEXTSETFONT 23
#define SURFACE_TEXTSETCOL 25
#define SURFACE_TEXTSETPOS 26
#define SURFACE_TEXTPRINT 28
#define SURFACE_TEXTCREATEFONT 71
#define SURFACE_SETGLYPH 72
#define SURFACE_GETSIZE 79

// IVEngineClient
#define ENGINE_GETSCREENSIZE 5
#define ENGINE_GETLOCALENT 12
#define ENGINE_MAXCLIENTS 20

// IVModelRender
#define MDLRENDER_FORCEMATOVERIDE 1
#define MDLRENDER_ISFORCEDMAT 2

template<typename ReturnType>
ReturnType call_virtual_method(void* pInterface, unsigned int index)
{
    unsigned int* pVTable{ *reinterpret_cast<unsigned int**>(pInterface) };
    return reinterpret_cast<ReturnType>(pVTable[index]);
}

bool set_font(unsigned long& font, int size, int weight = 550);

void print_text(std::wstring text, int x, int y, const Color& col);

std::wstring weapontype_to_wstring(int type);