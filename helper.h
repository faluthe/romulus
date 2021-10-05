#pragma once

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

template<typename ReturnType>
ReturnType call_virtual_method(void* pInterface, unsigned int index)
{
    unsigned int* pVTable{ *reinterpret_cast<unsigned int**>(pInterface) };
    return reinterpret_cast<ReturnType>(pVTable[index]);
}