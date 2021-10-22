#include "Entity.h"
#include "IBaseClientDll.h"
#include "interfaces.h"
#include "Matrix.h"
#include "Vector.h"

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