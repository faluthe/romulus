#pragma once

#include "helper.h"
#include "Recv.h"

enum class ClassId
{
	BaseNPC = 0
};

class ClientClass;
class IClientNetworkable;

typedef IClientNetworkable* (*CreateClientClassFn)(int entnum, int serialNum);
typedef IClientNetworkable* (*CreateEventFn)();

class ClientClass
{
public:
    CreateClientClassFn      m_pCreateFn;
    CreateEventFn            m_pCreateEventFn;
    char* m_pNetworkName;
    RecvTable* recvTable;
    ClientClass* pNext;
    ClassId                  m_ClassID;
};

class IBaseClientDll
{
public:
	ClientClass* GetAllClasses()
	{
		return call_virtual_method<ClientClass* (__thiscall*)(void*)>(this, BASECLIENT_GETALL)(this);
	}
};