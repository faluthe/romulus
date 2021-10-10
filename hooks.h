#pragma once

#include "Hook.h"

namespace hooks
{
	inline Hook clientMode;
	inline Hook panel;

	void init();
	void restore();
}