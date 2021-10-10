#include <stdexcept>
#include <string.h>

#include "IBaseClientDll.h"
#include "interfaces.h"
#include "netvars.h"

ClientClass* clientClass{};

uintptr_t check_recvTable(RecvTable* table, const char* tableName, const char* netvarName)
{
	for (int i{ 0 }; i < table->nProps; i++)
	{
		RecvProp prop{ table->pProps[i] };

		if (!_stricmp(prop.varName, netvarName))
			return prop.offset;

		if (prop.pDataTable)
		{
			uintptr_t offset{ check_recvTable(prop.pDataTable, tableName, netvarName) };
			
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
	return 0;
}

namespace netvars
{
	void init()
	{
		clientClass = interfaces::client->GetAllClasses();

		flags = get_netvar("DT_CSPlayer", "m_fFlags");
		if (!flags)
			throw std::runtime_error("Flags Netvar is null");

		health = get_netvar("DT_BasePlayer", "m_iHealth");
		if (!health)
			throw std::runtime_error("Health Netvar is null");
	}
}