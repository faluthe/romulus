#pragma once

#include "Color.h"

namespace config
{
	inline unsigned short mode{ 0 };

	inline float viewmodel_fov{ 90.0f };
	inline float viewmodel_offset_x{ 2.5f };
	inline float viewmodel_offset_y{ 0.5f };
	inline float viewmodel_offset_z{ -1.5f };

	inline Color enemyVisible{ colors::orange };
	inline Color enemyHidden{ colors::white };
	inline Color friendlyVisible{ colors::blue };

	inline bool handChams{ false };
	inline bool weaponChams{ false };

	inline bool drawDebugPanel{ true };
}