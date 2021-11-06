#include "CUserCmd.h"
#include "engineprediction.h"
#include "helper.h"
#include "interfaces.h"
#include "localplayer.h"
#include "structs.h"

int* predictionRandomSeed;
float oldCurTime;
float oldFrameTime;
player_move_data data;

static int localplayerFlags;
static int* predictionRandomSeed2;
player_move_data* moveData;

namespace prediction
{
	void start(CUserCmd* cmd)
	{
		using namespace interfaces;

		if (!localplayer)
			return;

		if (!predictionRandomSeed)
			predictionRandomSeed = *reinterpret_cast<int**>(pattern_scan("client.dll", "8B 0D ? ? ? ? BA ? ? ? ? E8 ? ? ? ? 83 C4 04") + 2);

		*predictionRandomSeed = cmd->randomseed & 0x7FFFFFFF;

		oldCurTime = globalVars->curtime;
		oldFrameTime = globalVars->frametime;

		globalVars->curtime = localplayer->tickBase() * globalVars->interval_per_tick;
		globalVars->frametime = globalVars->interval_per_tick;

		gameMovement->StartTracking(localplayer);

		memset(&data, 0, sizeof(data));
		moveHelper->SetHost(localplayer);
		playerPrediction->SetupMove(localplayer, cmd, moveHelper, &data);
		gameMovement->ProcessMovement(localplayer, &data);
		playerPrediction->FinishMove(localplayer, cmd, &data);
	}

	void end()
	{
		using namespace interfaces;

		if (!localplayer)
			return;

		gameMovement->FinishTracking(localplayer);
		moveHelper->SetHost(nullptr);

		*predictionRandomSeed = -1;

		globalVars->curtime = oldCurTime;
		globalVars->frametime = oldFrameTime;
	}
	
	void run(CUserCmd* cmd)
	{
		if (!localplayer)
			return;

		localplayerFlags = localplayer->flags();

		if (!predictionRandomSeed2)
			predictionRandomSeed2 = *reinterpret_cast<int**>(pattern_scan("client.dll", "8B 0D ? ? ? ? BA ? ? ? ? E8 ? ? ? ? 83 C4 04") + 2);

		if (!moveData)
			moveData = **reinterpret_cast<player_move_data***>(pattern_scan("client.dll", "A1 ? ? ? ? F3 0F 59 CD") + 1);

		const auto oldCurrentTime{ interfaces::globalVars->curtime };
		const auto oldFrTime{ interfaces::globalVars->frametime };

		interfaces::globalVars->curtime = localplayer->tickBase() * interfaces::globalVars->interval_per_tick;
		interfaces::globalVars->frametime = interfaces::globalVars->interval_per_tick;

		interfaces::moveHelper->SetHost(localplayer);
		interfaces::playerPrediction->SetupMove(localplayer, cmd, interfaces::moveHelper, moveData);
		interfaces::gameMovement->ProcessMovement(localplayer, moveData);
		interfaces::playerPrediction->FinishMove(localplayer, cmd, moveData);
		interfaces::moveHelper->SetHost(nullptr);

		*predictionRandomSeed2 = -1;

		interfaces::globalVars->curtime = oldCurrentTime;
		interfaces::globalVars->frametime = oldFrTime;
	}
}