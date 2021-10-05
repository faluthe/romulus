#pragma once

#include "IPanel.h"
#include "ISurface.h"

namespace interfaces
{
	inline IPanel* panel;
	inline ISurface* surface;

	void init();
}