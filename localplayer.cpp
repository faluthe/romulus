#include "interfaces.h"
#include "localplayer.h"

namespace localplayerUtils
{
	void get()
	{
		using namespace interfaces;
		localplayer = entityList->GetClientEntity<LocalplayerEntity>(engine->GetLocalPlayer());
	}
}