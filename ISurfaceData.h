#pragma once

#include "helper.h"

struct SurfaceData {
    char pad0[80];
    float maxspeedfactor;
    float jumpfactor;
    float penetrationmodifier;
    float damagemodifier;
    short material;
    bool climbable;
};

class IPhysicsSurfaceProps
{
public:
	VIRTUAL_METHOD(SurfaceData*, GetSurfaceData, 5, (int index), (this, index))
};