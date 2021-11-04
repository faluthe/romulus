#pragma once

#include <string_view>

#include "helper.h"
#include "IMaterial.h"

enum class OverrideType {
    Normal = 0,
    BuildShadows,
    DepthWrite,
    CustomMaterial, // weapon skins
    SsaoDepthWrite
};

class IStudioRender
{
private:
    char pad0[592];
    IMaterial* materialOverride;
    char pad1[12];
    OverrideType overrideType;
public:
	bool IsForcedMaterialOverride()
	{
        if (!materialOverride)
            return overrideType == OverrideType::DepthWrite || overrideType == OverrideType::SsaoDepthWrite;
        return std::string_view{ materialOverride->name() }.starts_with("dev/glow");
	}
};