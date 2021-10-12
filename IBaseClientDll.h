#pragma once

#include "helper.h"
#include "Recv.h"

enum class ClassId
{
	BaseNPC = 0
};

class ClientClass;

class ClientClass
{
public:
    char pad0[8];
    char* networkName;
    RecvTable* recvTable;
    ClientClass* pNext;
    ClassId classId;
};

class IBaseClientDll
{
public:
	ClientClass* GetAllClasses()
	{
		return call_virtual_method<ClientClass* (__thiscall*)(void*)>(this, BASECLIENT_GETALL)(this);
	}
};