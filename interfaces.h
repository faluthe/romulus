#pragma once

#include "IPanel.h"
#include "ISurface.h"
#include "IVEngineClient.h"

namespace interfaces
{
	inline IVEngineClient* engine;
	inline IPanel* panel;
	inline ISurface* surface;

	void init();
}