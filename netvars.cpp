#include <stdexcept>
#include <string.h>

#include "interfaces.h"
#include "netvars.h"

class ClientClass;

ClientClass* clientClass{};

uintptr_t check_recvTable(RecvTable* table, const char* tableName, const char* netvarName)
{
	for (int i{ 0 }; i < table->nProps; i++)
	{
		const auto prop{ table->pProps[i] };

		if (!_stricmp(prop.varName, netvarName))
			return prop.offset;

		if (prop.pDataTable)
		{
			const auto offset{ check_recvTable(prop.pDataTable, tableName, netvarName) };
			
			if (offset)
				return offset + prop.offset;
		}
	}
	return 0;
}

uintptr_t get_netvar(const char* tableName, const char* netvarName)
{
	for (auto curNode{ clientClass }; curNode; curNode = curNode->pNext)
	{
		if (!_stricmp(tableName, curNode->recvTable->netTableName))
			return check_recvTable(curNode->recvTable, tableName, netvarName);
	}

	throw std::runtime_error(std::string("Failed to get netvar:") + netvarName);
}

namespace netvars
{
	void init()
	{
		clientClass = interfaces::client->GetAllClasses();
		
		activeWeapon = get_netvar("DT_CSPlayer", "m_hActiveWeapon");
		aimPunch = get_netvar("DT_BasePlayer", "m_aimPunchAngle");
		flags = get_netvar("DT_CSPlayer", "m_fFlags");
		health = get_netvar("DT_BasePlayer", "m_iHealth");
		isScoped = get_netvar("DT_CSPlayer", "m_bIsScoped");
		itemDefIndex = get_netvar("DT_BaseCombatWeapon", "m_iItemDefinitionIndex");
		moveType = get_netvar("DT_CSPlayer", "m_nRenderMode") + 1;
		nextPrimaryAttack = get_netvar("DT_BaseCombatWeapon", "m_flNextPrimaryAttack");
		team = get_netvar("DT_BasePlayer", "m_iTeamNum");
	}
}