#include <string>

#include "Entity.h"
#include "IBaseClientDll.h"
#include "interfaces.h"
#include "Matrix.h"
#include "Vector.h"

std::wstring WeaponEntity::weaponTypeStr()
{
	switch (clientClass()->classId)
	{
	case ClassId::AK47: return L"AK-47";
	case ClassId::C4: return L"Bomb";
	case ClassId::Deagle: 
		if (isRevolver())
			return L"Revolver";
		return L"Deagle";
	case ClassId::DecoyGrenade: return L"Decoy";
	case ClassId::FlashbangGrenade: return L"Flashbang";
	case ClassId::HEGrenade: return L"HE Grenade";
	case ClassId::IncendiaryGrenade: return L"Incendiary";
	case ClassId::Knife: return L"Knife";
	case ClassId::MolotovGrenade: return L"Molotov";
	case ClassId::SmokeGrenade: return L"Smoke";
	case ClassId::AUG: return L"AUG";
	case ClassId::AWP: return L"AWP";
	case ClassId::PPBIZON: return L"PP-Bizon";
	case ClassId::ELITE: return L"Dual Berettas";
	case ClassId::FAMAS: return L"FAMAS";
	case ClassId::FIVESEVEN: return L"Five-Seven";
	case ClassId::G3SG1: return L"G3SG1";
	case ClassId::GalilAR: return L"Galil AR";
	case ClassId::Glock: return L"Glock-18";
	case ClassId::P2000:
		if (itemDefinitionIndex() == 61)
			return L"USP-S";
		return L"P2000";
	case ClassId::M249: return L"M249";
	case ClassId::M4A1S: 
		if (itemDefinitionIndex() == 16)
			return L"M4A4";
		return L"M4A1-S";
	case ClassId::MAC10: return L"MAC-10";
	case ClassId::MAG7: return L"MAG-7";
	case ClassId::MP5SD: return L"M55-SD";
	case ClassId::MP7: return L"MP7";
	case ClassId::MP9: return L"MP9";
	case ClassId::Negev: return L"Negev";
	case ClassId::Nova: return L"Nova";
	case ClassId::P250: 
		if (itemDefinitionIndex() == 63)
			return L"CZ75-Auto";
		return L"P250";
	case ClassId::P90: return L"P90";
	case ClassId::Sawedoff: return L"Sawed-Off";
	case ClassId::SCAR20: return L"SCAR-20";
	case ClassId::SG553: return L"SG 553";
	case ClassId::SSG08: return L"SSG 08";
	case ClassId::Tec9: return L"Tec-9";
	case ClassId::UMP45: return L"UMP-45";
	case ClassId::USPS: return L"USP-S";
	case ClassId::XM1014: return L"XM1014";
	default: return L"Error";
	}
}

void Entity::invalidateBoneCache()
{
	static DWORD addr = (DWORD)pattern_scan("client.dll", "80 3D ? ? ? ? ? 74 16 A1 ? ? ? ? 48 C7 81");

	*(int*)(this + 0xA30) = interfaces::globalVars->framecount;
	*(int*)(this + 0xA28) = 0;

	unsigned long boneCounter = **(unsigned long**)(addr + 10);
	*(unsigned long*)((DWORD)this + 0x2924) = 0xFF7FFFFF;
	*(unsigned int*)((DWORD)this + 0x2690) = (boneCounter - 1);
}

Vector Entity::hitboxPos(int id)
{
	Matrix boneMatrix[128];

	if (setupBones(boneMatrix, 128, 0x00000100, 0.0f))
	{
		auto studioModel{ interfaces::mdlInfo->GetStudioModel(model()) };

		if (studioModel)
		{
			const auto hitbox{ studioModel->GetHitboxSet(0)->GetHitbox(id) };

			if (hitbox)
			{
				Vector min, max;

				transform_vector(hitbox->bbmin, boneMatrix[hitbox->bone], min);
				transform_vector(hitbox->bbmax, boneMatrix[hitbox->bone], max);

				return Vector{ (min.x + max.x) * 0.5f, (min.y + max.y) * 0.5f, (min.z + max.z) * 0.5f };
			}
		}
	}
	return Vector{};
}

WeaponEntity* Entity::activeWeapon()
{
	auto activeWeapon{ *reinterpret_cast<uintptr_t*>(this + netvars::activeWeapon) & 0xFFF };
	return reinterpret_cast<WeaponEntity*>(interfaces::entityList->GetClientEntity(activeWeapon));
}

bool Entity::isGrenade()
{
	switch (clientClass()->classId)
	{
	case ClassId::GrenadeProjectile:
	case ClassId::DecoyProjectile:
	case ClassId::MolotovProjectile:
	case ClassId::SmokeProjectile:
		return true;
	default:
		return false;
	}
}

bool Entity::isC4() { return clientClass()->classId == ClassId::C4; }
bool Entity::isPlantedC4() { return clientClass()->classId == ClassId::PlantedC4; }