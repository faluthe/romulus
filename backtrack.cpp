#include <algorithm>
#include <deque>

#include "backtrack.h"
#include "ConVar.h"
#include "CUserCmd.h"
#include "INetChannelInfo.h"
#include "interfaces.h"
#include "localplayer.h"
#include "Vector.h"

struct Convars
{
	ConVar* updaterate;
	ConVar* maxupdaterate;
	ConVar* interp;
	ConVar* interp_ratio;
	ConVar* min_interp_ratio;
	ConVar* max_interp_ratio;
	ConVar* maxunlag;
};

static Convars convars;
std::deque<Records> records[65];

int time2ticks(float time)
{
	return static_cast<int>(0.5f + time / interfaces::globalVars->interval_per_tick);
}

float ticks2time(int ticks)
{
	return interfaces::globalVars->interval_per_tick * static_cast<float>(ticks);
}

float get_lerp()
{
	auto ratio{ std::clamp(convars.interp_ratio->GetFloat(), convars.min_interp_ratio->GetFloat(), convars.max_interp_ratio->GetFloat()) };
	return (std::max)(convars.interp->GetFloat(), (ratio / ((convars.maxupdaterate) ? convars.maxupdaterate->GetFloat() : convars.updaterate->GetFloat())));
}

bool valid_tick(float simTime)
{
	const auto network{ interfaces::engine->GetNetChannelInfo() };
	if (!network)
		return false;

	float latency0{ network->GetLatency(0) };
	float latency1{ network->GetLatency(1) };
	float lerp{ get_lerp() };
	float unlag{ convars.maxunlag->GetFloat() };
	float servertime{ interfaces::globalVars->curtime };

	auto delta = std::clamp(latency0 + latency1 + lerp, 0.0f, unlag) - (servertime - simTime);
	return std::abs(delta) <= 0.4f;
}

namespace backtrack
{
	void init()
	{
		using namespace interfaces;

		records->clear();

		convars.updaterate = cvar->FindVar("cl_updaterate");
		convars.maxupdaterate = cvar->FindVar("sv_maxupdaterate");
		convars.interp = cvar->FindVar("cl_interp");
		convars.interp_ratio = cvar->FindVar("cl_interp_ratio");
		convars.min_interp_ratio = cvar->FindVar("sv_client_min_interp_ratio");
		convars.max_interp_ratio = cvar->FindVar("sv_client_max_interp_ratio");
		convars.maxunlag = cvar->FindVar("sv_maxunlag");
	}

	void update()
	{
		using namespace interfaces;
		if (!localplayer)
		{
			if (!records->empty())
				records->clear();
			return;
		}
		
		const auto network{ engine->GetNetChannelInfo() };
		if (!network)
			return;

		for (int i{ 1 }; i <= engine->GetMaxClients(); i++)
		{
			const auto ent{ entityList->GetClientEntity(i) };
			
			if (!ent || ent == localplayer || ent->dormant() || !ent->isAlive() || ent->team() == localplayer->team())
			{
				records[i].clear();
				continue;
			}

			if (records[i].size() && (records[i].front().simTime == ent->simulationTime()))
				continue;

			Records record{};
			*(Vector*)(ent + 0xA0) = ent->vecOrigin();
			*(int*)(ent + 0xA68) = 0;
			*(int*)(ent + 0xA30) = 0;
			record.head = ent->hitboxPos(0);
			record.simTime = ent->simulationTime();
			
			ent->invalidateBoneCache();

			ent->setupBones(record.matrix, 128, 0x7FF00, globalVars->curtime);
			
			records[i].push_front(record);

			while (records[i].size() > 3 && records[i].size() > static_cast<size_t>(time2ticks(0.4f)))
				records[i].pop_back();

			if (auto invalid = std::find_if(std::cbegin(records[i]), std::cend(records[i]), [](const Records& rec) { return !valid_tick(rec.simTime); }); invalid != std::cend(records[i]))
				records[i].erase(invalid, std::cend(records[i]));
		}
	}

	void run(CUserCmd* cmd)
	{
		if (!localplayer || !localplayer->isAlive())
			return;

		const auto weapon{ localplayer->activeWeapon() };
		if (!weapon)
			return;

		float bestFov{ 255.0f };
		float bestDistance{ FLT_MAX };

		Entity* bestTarget{};
		Vector bestTargetHeadPos{};
		int bestTargetIndex{};
		int bestRecord{};
		Vector lol{};

		for (int i{ 1 }; i < interfaces::engine->GetMaxClients(); i++)
		{
			const auto ent{ interfaces::entityList->GetClientEntity(i) };

			if (!ent || !ent->isAlive() || ent->dormant() || ent->team() == localplayer->team())
				continue;

			auto headPos{ ent->hitboxPos(0) - localplayer->eyePosition() };

			vector_angles(headPos, lol);
			normalize3(lol);
			lol.clamp();

			float curDist{ localplayer->vecOrigin().DistTo(headPos) };
			auto fov{ get_fov(cmd->viewAngles + (localplayer->aimPunch() * 2.0f), lol) };

			if (fov < bestFov)
			{
				bestFov = fov;
				bestTarget = ent;
				bestDistance = curDist;
				bestTargetIndex = i;
				bestTargetHeadPos = headPos;
			}
		}
		Vector angle;
		if (bestTarget)
		{
			if (records[bestTargetIndex].size() <= 3)
				return;

			bestFov = 255.0f;
			bestDistance = 999.0f;
			for (size_t i{ 0 }; i < records[bestTargetIndex].size(); i++)
			{
				auto record{ &records[bestTargetIndex][i] };
				if (!record || !valid_tick(record->simTime))
					continue;
				auto headPos{ record->head - localplayer->eyePosition() };
				vector_angles(headPos, angle);
				angle.clamp();
				float curDist{ localplayer->vecOrigin().DistTo(record->head) };
				auto fov{ get_fov(cmd->viewAngles + (localplayer->aimPunch() * 2.0f), angle) };
				if (fov < bestFov)
				{
					bestFov = fov;
					bestDistance = curDist;
					bestRecord = i;
				}
			}
		}

		selectedTarget = bestTargetIndex;
		selectedIndex = bestRecord;

		if (bestRecord && cmd->buttons & CUserCmd::IN_ATTACK)
			cmd->tickCount = time2ticks(records[bestTargetIndex][bestRecord].simTime + get_lerp());
	}
}