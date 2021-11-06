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
		armor = get_netvar("DT_CSPlayer", "m_ArmorValue");
		c4Blow = get_netvar("DT_PlantedC4", "m_flC4Blow");
		entQuality = get_netvar("DT_BaseAttributableItem", "m_iEntityQuality");
		fallbackSeed = get_netvar("DT_BaseAttributableItem", "m_nFallbackSeed");
		fallbackWear = get_netvar("DT_BaseAttributableItem", "m_flFallbackWear");
		flags = get_netvar("DT_CSPlayer", "m_fFlags");
		gunGameImmunity = get_netvar("DT_CSPlayer", "m_bGunGameImmunity");
		health = get_netvar("DT_BasePlayer", "m_iHealth");
		isScoped = get_netvar("DT_CSPlayer", "m_bIsScoped");
		itemDefIndex = get_netvar("DT_BaseCombatWeapon", "m_iItemDefinitionIndex");
		itemId = get_netvar("DT_BaseAttributableItem", "m_iItemIDHigh");
		modelIndex = get_netvar("DT_BaseEntity", "m_nModelIndex");
		moveType = get_netvar("DT_CSPlayer", "m_nRenderMode") + 1;
		myWeapons = get_netvar("DT_CSPlayer", "m_hMyWeapons");
		nextPrimaryAttack = get_netvar("DT_BaseCombatWeapon", "m_flNextPrimaryAttack");
		originalOwnerLow = get_netvar("DT_BaseAttributableItem", "m_OriginalOwnerXuidLow");
		originalOwnerHigh = get_netvar("DT_BaseAttributableItem", "m_OriginalOwnerXuidHigh");
		paintkit = get_netvar("DT_BaseAttributableItem", "m_nFallbackPaintKit");
		simulationTime = get_netvar("DT_CSPlayer", "m_flSimulationTime");
		team = get_netvar("DT_BasePlayer", "m_iTeamNum");
		tickBase = get_netvar("DT_CSPlayer", "m_nTickBase");
		vecOrigin = get_netvar("DT_BasePlayer", "m_vecOrigin");
		viewmodel = get_netvar("DT_BasePlayer", "m_hViewModel[0]");
		viewmodelWeapon = get_netvar("DT_BaseViewModel", "m_hWeapon");
		viewmodelModelIndex = get_netvar("DT_BaseViewModel", "m_nModelIndex");
		worldModel = get_netvar("DT_BaseCombatWeapon", "m_hWeaponWorldModel");
	}
}