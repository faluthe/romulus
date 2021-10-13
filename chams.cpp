#include <string>

#include "chams.h"
#include "Color.h"
#include "Entity.h"
#include "hooks.h"
#include "interfaces.h"

IMaterial* material{};

void setup_material(const Color& col, bool ignoreZ = false, bool wireframe = false, float alpha = 255.0f)
{
	if (!material)
		material = interfaces::matSys->FindMaterial("debug/debugambientcube", "Model textures");

	material->ColorModulate(col.r / 255.0f, col.g / 255.0f, col.b / 255.0f);
	material->AlphaModulate(alpha / 255.0f);
	material->SetMaterialVarFlags(1 << 15, ignoreZ);
	material->SetMaterialVarFlags(1 << 28, wireframe);

	interfaces::mdlRender->ForcedMaterialOverride(material);
}

void chams(void* _this, void* _edx, void* context, const ModelRenderInfo_t& state, const ModelRenderInfo_t& pInfo, void* pCustomBoneToWorld)
{
	if (!pInfo.pModel)
		return;

	const auto mdl{ pInfo.pModel };

	Entity* localplayer{ interfaces::entityList->GetClientEntity(interfaces::engine->GetLocalPlayer()) };

	if (strstr(mdl->name, "models/player") != nullptr)
	{
		Entity* ent{ interfaces::entityList->GetClientEntity(pInfo.entityIndex) };

		if (!localplayer || !ent || ent->dormant() || ent->health() == 0)
			return;

		if (localplayer->team() != ent->team())
		{
			setup_material(colors::darkOrange, true);
			hooks::oDrawModelExecute(_this, _edx, context, state, pInfo, pCustomBoneToWorld);
			setup_material(colors::orange);
		}
		else
			setup_material(colors::blue);
	}
	else if (strstr(mdl->name, "sleeve") != nullptr)
	{
		setup_material(colors::orange, false, true);
	}
	else if (strstr(mdl->name, "arms") != nullptr)
	{
		setup_material(colors::orange, false, false, 255.0f / 2.0f);
	}
	else if (strstr(mdl->name, "models/weapons/v_") != nullptr)
	{
		if (localplayer->isScoped())
			return;

		const auto activeWeapon{ localplayer->activeWeapon() };
		if (activeWeapon && activeWeapon->weaponType() == 0)
		{
			static float alpha{ 255.0f };
			static bool countup{ false };
			if (!countup && alpha > 0.0f)
				alpha -= 0.5f;
			if (alpha <= 0.0f)
				countup = true;
			if (countup && alpha < 255.0f)
				alpha += 0.5f;
			if (alpha >= 255.0f)
				countup = false;
				
			setup_material(colors::black, false, false, alpha);
		}
		else
			setup_material(colors::white);
	}
}