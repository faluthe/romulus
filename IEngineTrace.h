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

struct cplane_t
{
    Vector normal;
    float dist;
    uint8_t type;
    uint8_t signbits;
    uint8_t pad[2];
};

struct trace_t {
    Vector startpos;
    Vector endpos;
    cplane_t plane;
    float fraction;
    int contents;
    unsigned short dispFlags;
    bool allSolid;
    bool startSolid;
    std::byte pad1[4];
    struct Surface {
        const char* name;
        short surfaceProps;
        unsigned short flags;
    } surface;
    int hitgroup;
    std::byte pad2[4];
    PlayerEntity* entity;
    int hitbox;
    bool DidHit()
    {
        return fraction < 1 || allSolid || startSolid;
    }
};

class IEngineTrace
{
public:
    VIRTUAL_METHOD(int, getPointContents, 0, (const Vector& absPosition, int contentsMask), (this, std::cref(absPosition), contentsMask, nullptr))
    VIRTUAL_METHOD(void, ClipRayToEntity, 3, (const Ray_t& ray, unsigned int fMask, Entity* ent, trace_t& pTrace), (this, std::cref(ray), fMask, ent, std::cref(pTrace)))
	VIRTUAL_METHOD(void, TraceRay, 5, (const Ray_t& ray, unsigned int fMask, const traceFilter& pTraceFilter, trace_t& pTrace), (this, std::cref(ray), fMask, std::cref(pTraceFilter), std::ref(pTrace)))
};