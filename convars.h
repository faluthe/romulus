#pragma once

#include "SpoofVar.h"

namespace convars
{
	inline SpoofVar* viewmodel_fov;
	inline SpoofVar* viewmodel_offset_x;
	inline SpoofVar* viewmodel_offset_y;
	inline SpoofVar* viewmodel_offset_z;

	void set();
	void restore();
	void spoof();
}