#include "hooks.h"
#include "interfaces.h"
#include "localplayer.h"
#include "structs.h"

struct KnifeInfo
{
	int index{};
	int defIndex{};
	int paintKit{};
};

void skinchanger(client_frame_stage_t stage)
{
	if (stage == client_frame_stage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START)
	{
		if (!localplayer || !localplayer->isAlive())
			return;

		const auto weapon = localplayer->activeWeapon();

		if (!weapon)
			return;

		const auto team = localplayer->team();

		static KnifeInfo knife;

		if (team == Team::CT)
		{
			knife.index = interfaces::mdlInfo->GetModelIndex("models/weapons/v_knife_karam.mdl");
			knife.defIndex = 507;
			knife.paintKit = 568;
		}
		else if (team == Team::T)
		{
			knife.index = interfaces::mdlInfo->GetModelIndex("models/weapons/v_knife_m9_bay.mdl");
			knife.defIndex = 508;
			knife.paintKit = 413;
		}

		auto hWeapons = localplayer->weapons();
		for (int i{ 0 }; hWeapons[i] != 0xFFFFFFFF; i++)
		{
			auto weapons = interfaces::entityList->GetEntityFromHandle<WeaponEntity>(hWeapons[i]);

			if (!weapons)
				return;

			if (weapon->clientClass()->classId == ClassId::Knife)
			{
				const auto viewModel = interfaces::entityList->GetEntityFromHandle<ViewmodelEntity>(localplayer->viewmodel());

				if (!viewModel)
					return;

				const auto viewModelWeapon = interfaces::entityList->GetEntityFromHandle<WeaponEntity>(viewModel->hWeapon());

				if (!viewModel)
					return;

				viewModel->modelIndex() = knife.index;
				
				const auto worldModel = interfaces::entityList->GetEntityFromHandle<ViewmodelEntity>(viewModelWeapon->hWorldModel());
				
				if (!worldModel)
					return;

				worldModel->modelIndex() = knife.index + 1;
			}

			auto weaponClass{ weapons->clientClass()->classId };

			if (weaponClass == ClassId::Knife)
			{
				weapons->itemDefIndex() = knife.defIndex;
				weapons->paintKit() = knife.paintKit;
				weapons->modelIndex() = knife.index;
				weapons->quality() = 3;
				weapons->wear() = 0.001f;
			}

			if (weaponClass == ClassId::AWP)
				weapons->paintKit() = 279;
			if (weaponClass == ClassId::AK47)
				weapons->paintKit() = 921;
			if (weaponClass == ClassId::Glock)
				weapons->paintKit() = 586;
			if (weaponClass == ClassId::M4A1S)
				weapons->paintKit() = 430;
			if (weaponClass == ClassId::P2000)
				weapons->paintKit() = 1040;
			if (weaponClass == ClassId::SSG08)
				weapons->paintKit() = 554;

			weapons->ogOwnerLow() = 0;
			weapons->ogOwnerHigh() = 0;
			weapons->fallbackSeed() = 403;
			weapons->itemId() = -1;
		}
	}
}