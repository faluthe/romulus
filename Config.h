#pragma once

#include "Color.h"

namespace config
{
	inline bool drawConfigPanel{ true };

	inline unsigned short mode{ 0 };

	inline float viewmodel_fov{ 90.0f };
	inline float viewmodel_offset_x{ 2.5f };
	inline float viewmodel_offset_y{ 0.5f };
	inline float viewmodel_offset_z{ -1.5f };

	inline Color enemyVisible{ 187, 68, 48, 255 };
	inline Color enemyHidden{ colors::white };
	inline Color friendlyVisible{ 244, 159, 10, 255 };
	inline Color backtrack{ 7, 160, 195, 20 };
	inline Color selectedTick{ 98, 76, 171, 127 };

	inline bool handChams{ false };
	inline bool weaponChams{ false };

	inline bool drawDebugPanel{ false };

	inline bool boxes{ false };
	inline bool chamsIgnoreZ{ false };

	void display();
}