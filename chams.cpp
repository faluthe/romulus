#include <string>

#include "chams.h"
#include "Color.h"
#include "Entity.h"
#include "hooks.h"
#include "interfaces.h"

IMaterial* material{};

void placeholder_func(const Color& col, float alpha = 255.0f)
{
	material->ColorModulate(col.r / 255.0f, col.g / 255.0f, col.b / 255.0f);
	material->AlphaModulate(alpha / 255.0f);

	interfaces::mdlRender->ForcedMaterialOverride(material);
}

void chams(const ModelRenderInfo_t& pInfo)
{
	if (!pInfo.pModel)
		return;

	const auto mdl{ pInfo.pModel };

	if (!material)
		material = interfaces::matSys->FindMaterial("debug/debugambientcube", "Model textures");

	if (strstr(mdl->name, "models/player") != nullptr)
	{
		Entity* localplayer{ interfaces::entityList->GetClientEntity(interfaces::engine->GetLocalPlayer()) };
		Entity* ent{ interfaces::entityList->GetClientEntity(pInfo.entityIndex) };

		if (!ent || ent->dormant() || ent->health() == 0)
			return;

		// material->SetMaterialVarFlags(1 << 15, false);
		if (localplayer->team() != ent->team())
			placeholder_func(colors::orange);
		else
			placeholder_func(colors::blue);
	}
	else if (strstr(mdl->name, "sleeve") != nullptr)
	{
		placeholder_func(colors::orange, 255.0f / 4.0f);
	}
	else if (strstr(mdl->name, "arms") != nullptr)
	{
		placeholder_func(colors::grey);
	}
	else if (strstr(mdl->name, "models/weapons/v_") != nullptr)
	{
		placeholder_func(colors::white);
	}
}