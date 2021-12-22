#include "backtrack.h"
#include "interfaces.h"
#include "localplayer.h"
#include "sharedrecords.h"

std::deque<Records> records[65];

void sharedrecords::update()
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

	if (!localplayer->isAlive())
		return;

	for (int i{ 1 }; i <= engine->GetMaxClients(); i++)
	{
		const auto ent{ entityList->GetClientEntity<PlayerEntity>(i) };

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