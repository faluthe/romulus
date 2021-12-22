#pragma once

#include <string>

#include "Color.h"
#include "Matrix.h"
#include "Vector.h"

// Hook indexes
#define INDEX_CREATE_MOVE 24
#define INDEX_DME 21
#define INDEX_FRAMESTAGENOTIFY 37
#define INDEX_PAINT_T 41
#define INDEX_SENDDATAGRAM 46

/*
  Valve SDK indexes
*/

// ConVar
#define CONVAR_GETFLOAT 12
#define CONVAR_GETVALUE 13
#define CONVAR_SETFLOAT 15
#define CONVAR_SETVALUE 16

// Entity
#define ENTITY_CLIENTCLASS 2
#define ENTITY_MODEL 8
#define ENTITY_ABSORIGIN 10
#define ENTITY_SETUPBONES 13
#define ENTITY_ISPLAYER 158
#define ENTITY_EYEPOS 285
#define ENTITY_OBSMODE 294
#define ENTITY_OBSTARGET 295
#define ENTITY_ACTIVEWEP 331
#define ENTITY_AIMPUNCH 346
#define WEAPONENTITY_WEAPON_TYPE 455

// IBaseClientDll
#define BASECLIENT_GETALL 8

// IClientEntityList
#define ENTLIST_GETENT 3
#define ENTLIST_MAXENTS 8

// ICvar
#define ICVAR_REGISTER 10
#define ICVAR_UNREGISTER 11
#define ICVAR_FINDVAR 15

// IEngineTrace
#define ENGINETRACE_TRACERAY 5

// IMaterial
#define IMAT_NAME 0
#define IMAT_ALPHAMOD 27
#define IMAT_COLORMOD 28
#define IMAT_SETMATFLAG 29

// IMaterialSystem
#define IMATSYS_FINDMAT 84

// INetChannelInfo
#define NCI_LATENCY 9

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
#define ENGINE_PLAYERINFO 8
#define ENGINE_GETLOCALENT 12
#define ENGINE_MAXCLIENTS 20
#define ENGINE_INGAME 26
#define ENGINE_W2SMATRIX 37
#define ENGINE_NETCHANNEL 78

// IVModelInfo
#define MDLINFO_GETSTUDIO 32

// IVModelRender
#define MDLRENDER_FORCEMATOVERIDE 1
#define MDLRENDER_ISFORCEDMAT 2

inline unsigned long infoFont;
inline int screenW, screenH;

template<typename ReturnType, int index, typename ...Arguments>
constexpr ReturnType call_virtual_method(void* pInterface, Arguments... arguments)
{
	return (*reinterpret_cast<ReturnType (__thiscall***)(void*, Arguments...)>(pInterface))[index](pInterface, arguments...);
}

#define VIRTUAL_METHOD(type, functionName, index, functionArgs, realArgs) \
type functionName functionArgs \
{ \
	return call_virtual_method<type, index>realArgs; \
}

bool set_font(unsigned long& font, int size, int weight = 550);

void print_text(std::wstring text, int x, int y, const Color& col, unsigned long font, bool centered = false);

bool world_to_screen(const Vector& in, Vector& out);

void transform_vector(const Vector& in1, Matrix& in2, Vector& out);

void vector_angles(const Vector& forward, Vector& angles);
void angle_vectors(Vector& angles, Vector& forward);

float normalizeVector(Vector& v);

Vector CalcAngle(const Vector& source, const Vector& destination);

constexpr float RAD2DEG(const float x);

constexpr float DEG2RAD(const float x);

Vector VectortoFart(const Vector& v);

template<typename T>
void normalize3(T& vec)
{
	for (auto i = 0; i < 2; i++) {
		while (vec[i] < -180.0f) vec[i] += 360.0f;
		while (vec[i] > 180.0f) vec[i] -= 360.0f;
	}
	vec[2] = 0.f;
}

float get_fov(const Vector& viewAngle, const Vector& aimAngle);

std::uint8_t* pattern_scan(const char* module_name, const char* signature);