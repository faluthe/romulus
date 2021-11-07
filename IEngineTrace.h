#pragma once

// https://github.com/perilouswithadollarsign/cstrike15_src/blob/master/public/engine/IEngineTrace.h

#include "helper.h"

struct Ray_t
{
    Ray_t(const Vector& src, const Vector& dest) : start(src), delta(dest - src) { isSwept = delta.x || delta.y || delta.z; }
    Vector start{ };
    float pad{ };
    Vector delta{ };
    char pad2[40]{ };
    bool isRay{ true };
    bool isSwept{ };
};

struct traceFilter
{
    traceFilter(const Entity* entity) : skip{ entity } { }
    virtual bool shouldHitEntity(Entity* entity, int) { return entity != skip; }
    virtual int getTraceType() const { return 0; }
    const void* skip;
};

struct trace_t
{
    Vector startpos;
    Vector endpos;
    char pad[20];
    float fraction;
    int contents;
    unsigned short dispFlags;
    bool allSolid;
    bool startSolid;
    char pad1[4];
    struct Surface {
        const char* name;
        short surfaceProps;
        unsigned short flags;
    } surface;
    int hitgroup;
    char pad2[4];
    Entity* entity;
    int hitbox;
};

class IEngineTrace
{
public:
	VIRTUAL_METHOD(void, TraceRay, 5, (const Ray_t& ray, unsigned int fMask, const traceFilter& pTraceFilter, trace_t& pTrace), (this, std::cref(ray), fMask, std::cref(pTraceFilter), std::ref(pTrace)))
};