#include <string>

#include "Color.h"
#include "Config.h"
#include "Entity.h"
#include "hooks.h"
#include "interfaces.h"
#include "localplayer.h"

IMaterial* material{};

void init_material()
{
	if (!material)
		material = interfaces::matSys->FindMaterial("debug/debugambientcube", "Model textures");
	material->SetMaterialVarFlags(1 << 2, false);
}

void setup_material(const Color& col, bool ignoreZ = false, bool wireframe = false, float alpha = 255.0f)
{
	init_material();

	material->ColorModulate(col.r / 255.0f, col.g / 255.0f, col.b / 255.0f);
	material->AlphaModulate(alpha / 255.0f);
	material->SetMaterialVarFlags(1 << 15, ignoreZ);
	material->SetMaterialVarFlags(1 << 28, wireframe);

	interfaces::mdlRender->ForcedMaterialOverride(material);
}

void no_draw()
{
	init_material();

	material->SetMaterialVarFlags(1 << 2, true);

	interfaces::mdlRender->ForcedMaterialOverride(material);
}

void breathing(const Color& col)
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

	setup_material(col, false, false, alpha);
}

void chams(void* _this, void* _edx, void* context, const ModelRenderInfo_t& state, const ModelRenderInfo_t& pInfo, void* pCustomBoneToWorld)
{
	if (!pInfo.pModel || !localplayer)
		return;

	const auto mdl{ pInfo.pModel };

	const auto activeWeapon{ localplayer->activeWeapon() };

	if (strstr(mdl->name, "models/player") != nullptr)
	{
		const auto ent{ interfaces::entityList->GetClientEntity(pInfo.entityIndex) };

		if (!ent || ent->dormant() || !ent->isAlive())
			return;

		if (localplayer->team() != ent->team())
		{
			setup_material(config::enemyHidden, true);
			hooks::oDrawModelExecute(_this, _edx, context, state, pInfo, pCustomBoneToWorld);
			setup_material(config::enemyVisible);
		}
		else
			setup_material(config::friendlyVisible);
	}
	else if (config::handChams && strstr(mdl->name, "sleeve") != nullptr)
	{
		if (activeWeapon && activeWeapon->isKnife())
			no_draw();
		else
			setup_material(colors::orange, false, true);
	}
	else if (config::handChams && strstr(mdl->name, "arms") != nullptr)
	{
		if (activeWeapon && activeWeapon->isKnife())
			no_draw();
		else
			setup_material(colors::orange, false, false, 255.0f / 2.0f);
	}
	else if (config::weaponChams && strstr(mdl->name, "models/weapons/v_") != nullptr)
	{
		if (localplayer->isScoped())
			return;

		if (activeWeapon && activeWeapon->isKnife())
			breathing(colors::black);
		else
			setup_material(colors::white);
	}
}