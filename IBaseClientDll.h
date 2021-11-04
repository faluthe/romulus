#pragma once

#include "helper.h"
#include "Recv.h"

enum class ClassId
{
	AK47 = 1,
	GrenadeProjectile = 9,
	C4 = 34,
	Deagle = 46,
	DecoyGrenade = 47,
	DecoyProjectile = 48,
	FlashbangGrenade = 77,
	HEGrenade = 96,
	IncendiaryGrenade = 99,
	Knife = 107,
	MolotovGrenade = 113,
	MolotovProjectile = 114,
	PlantedC4 = 129,
	SmokeGrenade = 156,
	SmokeProjectile = 157,
	AUG = 232,
	AWP = 233,
	PPBIZON = 235,
	ELITE = 239,
	FAMAS = 240,
	FIVESEVEN = 241,
	G3SG1 = 242,
	GalilAR = 244,
	Glock = 245,
	P2000 = 246,
	M249 = 247,
	M4A1S = 249,
	MAC10 = 250,
	MAG7 = 251,
	MP5SD = 252,
	MP7 = 253,
	MP9 = 254,
	Negev = 255,
	Nova = 256,
	P250 = 258,
	P90 = 259,
	Sawedoff = 260,
	SCAR20 = 261,
	SG553 = 265,
	SSG08 = 267,
	Tec9 = 269,
	UMP45 = 271,
	USPS = 272,
	XM1014 = 273,
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