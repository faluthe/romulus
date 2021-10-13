#include <Windows.h>

#include "convars.h"
#include "interfaces.h"
#include "SpoofVar.h"

namespace convars
{
	void set()
	{
		const auto localplayer{ interfaces::entityList->GetClientEntity(interfaces::engine->GetLocalPlayer()) };
		const auto activeWeapon{ localplayer->activeWeapon() };

		interfaces::cvar->FindVar("cl_grenadepreview")->SetValue(1);
		interfaces::cvar->FindVar("mat_postprocess_enable")->SetValue(1);
		interfaces::cvar->FindVar("weapon_debug_spread_show")->SetValue(2);
		interfaces::cvar->FindVar("cl_crosshair_recoil")->SetValue(1);

		auto righthand{ interfaces::cvar->FindVar("cl_righthand") };
		if (activeWeapon && activeWeapon->weaponType() == 0)
			righthand->SetValue(0);
		else
			righthand->SetValue(1);
	}

	void restore()
	{
		interfaces::cvar->FindVar("cl_grenadepreview")->SetValue(0);
		interfaces::cvar->FindVar("mat_postprocess_enable")->SetValue(0);
		interfaces::cvar->FindVar("weapon_debug_spread_show")->SetValue(0);
		interfaces::cvar->FindVar("cl_crosshair_recoil")->SetValue(0);
		interfaces::cvar->FindVar("cl_righthand")->SetValue(1);

		delete viewmodel_fov;
		delete viewmodel_offset_x;
		delete viewmodel_offset_y;
		delete viewmodel_offset_z;
	}

	void spoof()
	{
		viewmodel_fov = new SpoofVar{ interfaces::cvar->FindVar("viewmodel_fov"), "romulus_viewmodel_fov", 90 };
		viewmodel_offset_x = new SpoofVar{ interfaces::cvar->FindVar("viewmodel_offset_x"), "romulus_viewmodel_offset_x", 10 };
		viewmodel_offset_y = new SpoofVar{ interfaces::cvar->FindVar("viewmodel_offset_y"), "romulus_viewmodel_offset_y", 5 };
		viewmodel_offset_z = new SpoofVar{ interfaces::cvar->FindVar("viewmodel_offset_z"), "romulus_viewmodel_offset_z", -5 };
	}
}
