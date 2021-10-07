#pragma once

#include "Color.h"

// Hook indexes
#define INDEX_PAINT_T 41

/* 
  Valve SDK indexes 
*/

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

// IVEngineClient
#define ENGINE_GETSCREENSIZE 5

template<typename ReturnType>
ReturnType call_virtual_method(void* pInterface, unsigned int index)
{
    unsigned int* pVTable{ *reinterpret_cast<unsigned int**>(pInterface) };
    return reinterpret_cast<ReturnType>(pVTable[index]);
}

bool set_font(unsigned long& font, int size, int weight = 550);

void print_text(const wchar_t* text, int x, int y, const Color& col);