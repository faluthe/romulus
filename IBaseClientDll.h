#pragma once

#include "helper.h"
#include "Recv.h"

enum class ClassId
{
	GrenadeProjectile = 9,
	DecoyProjectile = 48,
	MolotovProjectile = 114,
	SmokeProjectile = 157,
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