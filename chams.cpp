#include <string>

#include "backtrack.h"
#include "Color.h"
#include "Config.h"
#include "Entity.h"
#include "hooks.h"
#include "interfaces.h"
#include "localplayer.h"
#include "sharedrecords.h"

IMaterial* material{};

void init_material()
{
	if (!material)
		material = interfaces::matSys->FindMaterial("debug/debugambientcube", "Model textures");
	material->SetMaterialVarFlags(1 << 2, false);
}

void setup_material(const Color& col, bool ignoreZ = false, bool wireframe = false)
{
	init_material();

	material->ColorModulate(col.r / 255.0f, col.g / 255.0f, col.b / 255.0f);
	material->AlphaModulate(col.a / 255.0f);
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

void breathing(Color& col)
{
	static int alpha{ 255 };
	static bool countup{ false };
	if (!countup && alpha > 0)
		alpha -= 1;
	if (alpha <= 0)
		countup = true;
	if (countup && alpha < 255)
		alpha += 1;
	if (alpha >= 255)
		countup = false;

	col.a = alpha;

	setup_material(col);
}

void chams(void* _this, void* _edx, void* context, const ModelRenderInfo_t& state, const ModelRenderInfo_t& pInfo, void* pCustomBoneToWorld)
{
	if (!pInfo.pModel || !localplayer)
		return;

	const auto mdl{ pInfo.pModel };

	const auto activeWeapon{ localplayer->activeWeapon() };

	if (strstr(mdl->name, "models/player") != nullptr)
	{
		const auto ent{ interfaces::entityList->GetClientEntity<PlayerEntity>(pInfo.entityIndex) };

		if (!ent || ent->dormant() || !ent->isAlive() || ent == localplayer)
			return;

		if (localplayer->team() != ent->team())
		{
			if (config::chamsIgnoreZ || localplayer->health() == 0)
			{
				setup_material(config::enemyHidden, true);
				hooks::oDrawModelExecute(_this, _edx, context, state, pInfo, pCustomBoneToWorld);
			}
			
			auto entIndex = ent->entityListIndex();

			if (records[entIndex].size() > 0)
			{
				for (int i{ 0 }; i < static_cast<int>(records[entIndex].size()); i++)
				{
					if (!valid_tick(records[entIndex][i].simTime) || records[entIndex][i].matrix == nullptr)
						continue;
					if (entIndex != backtrack::selectedTarget || i != backtrack::selectedIndex)
						continue;
					setup_material(config::backtrack);
					hooks::oDrawModelExecute(_this, _edx, context, state, pInfo, records[entIndex][i].matrix);
				}
			}
			setup_material(config::enemyVisible);
		}
		else
			setup_material(config::friendlyVisible);
	}
	else if (config::handChams && (strstr(mdl->name, "sleeve") != nullptr))
	{
		if (activeWeapon && activeWeapon->isKnife())
			no_draw();
		else
			setup_material(colors::orange, false, true);
	}
	else if (config::handChams && (strstr(mdl->name, "arms") != nullptr))
	{
		if (activeWeapon && activeWeapon->isKnife())
			no_draw();
		else
			setup_material(colors::orange);
	}
	else if (config::weaponChams && (strstr(mdl->name, "models/weapons/v_") != nullptr))
	{
		if (localplayer->isScoped())
			return;

		if (activeWeapon && activeWeapon->isKnife())
		{
			static Color knifeColor{ colors::black };
			breathing(knifeColor);
		}
		else
			setup_material(colors::white);
	}
}