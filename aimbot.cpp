//#include <vector>
//#include <Windows.h>
//
//#include "config.h"
//#include "CUserCmd.h"
//#include "helper.h"
//#include "interfaces.h"
//#include "ISurfaceData.h"
//#include "localplayer.h"
//#include "sharedrecords.h"
//#include "structs.h"
//
////#define   DISPSURF_FLAG_SURFACE           (1<<0)
////#define   DISPSURF_FLAG_WALKABLE          (1<<1)
////#define   DISPSURF_FLAG_BUILDABLE         (1<<2)
////#define   DISPSURF_FLAG_SURFPROP1         (1<<3)
////#define   DISPSURF_FLAG_SURFPROP2         (1<<4)
////
////#define   CONTENTS_EMPTY                0
////
////#define   CONTENTS_SOLID                0x1       
////#define   CONTENTS_WINDOW               0x2
////#define   CONTENTS_AUX                  0x4
////#define   CONTENTS_GRATE                0x8
////#define   CONTENTS_SLIME                0x10
////#define   CONTENTS_WATER                0x20
////#define   CONTENTS_BLOCKLOS             0x40 
////#define   CONTENTS_OPAQUE               0x80 
////#define   LAST_VISIBLE_CONTENTS         CONTENTS_OPAQUE
////
////#define   ALL_VISIBLE_CONTENTS            (LAST_VISIBLE_CONTENTS | (LAST_VISIBLE_CONTENTS-1))
////
////#define   CONTENTS_TESTFOGVOLUME        0x100
////#define   CONTENTS_UNUSED               0x200     
////#define   CONTENTS_BLOCKLIGHT           0x400
////#define   CONTENTS_TEAM1                0x800 
////#define   CONTENTS_TEAM2                0x1000 
////#define   CONTENTS_IGNORE_NODRAW_OPAQUE 0x2000
////#define   CONTENTS_MOVEABLE             0x4000
////#define   CONTENTS_AREAPORTAL           0x8000
////#define   CONTENTS_PLAYERCLIP           0x10000
////#define   CONTENTS_MONSTERCLIP          0x20000
////#define   CONTENTS_CURRENT_0            0x40000
////#define   CONTENTS_CURRENT_90           0x80000
////#define   CONTENTS_CURRENT_180          0x100000
////#define   CONTENTS_CURRENT_270          0x200000
////#define   CONTENTS_CURRENT_UP           0x400000
////#define   CONTENTS_CURRENT_DOWN         0x800000
////
////#define   CONTENTS_ORIGIN               0x1000000 
////
////#define   CONTENTS_MONSTER              0x2000000 
////#define   CONTENTS_DEBRIS               0x4000000
////#define   CONTENTS_DETAIL               0x8000000 
////#define   CONTENTS_TRANSLUCENT          0x10000000
////#define   CONTENTS_LADDER               0x20000000
////#define   CONTENTS_HITBOX               0x40000000
////
////#define   SURF_LIGHT                    0x0001 
////#define   SURF_SKY2D                    0x0002 
////#define   SURF_SKY                      0x0004 
////#define   SURF_WARP                     0x0008 
////#define   SURF_TRANS                    0x0010
////#define   SURF_NOPORTAL                 0x0020 
////#define   SURF_TRIGGER                  0x0040 
////#define   SURF_NODRAW                   0x0080 
////
////#define   SURF_HINT                     0x0100 
////
////#define   SURF_SKIP                     0x0200   
////#define   SURF_NOLIGHT                  0x0400   
////#define   SURF_BUMPLIGHT                0x0800   
////#define   SURF_NOSHADOWS                0x1000   
////#define   SURF_NODECALS                 0x2000   
////#define   SURF_NOPAINT                  SURF_NODECALS
////#define   SURF_NOCHOP                   0x4000   
////#define   SURF_HITBOX                   0x8000   
////
////// -----------------------------------------------------
////// spatial content masks - used for spatial queries (traceline,etc.)
////// -----------------------------------------------------
////#define   MASK_ALL                      (0xFFFFFFFF)
////#define   MASK_SOLID                    (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
////#define   MASK_PLAYERSOLID              (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
////#define   MASK_NPCSOLID                 (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
////#define   MASK_NPCFLUID                 (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER)
////#define   MASK_WATER                    (CONTENTS_WATER|CONTENTS_MOVEABLE|CONTENTS_SLIME)
////#define   MASK_OPAQUE                   (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_OPAQUE)
////#define   MASK_OPAQUE_AND_NPCS          (MASK_OPAQUE|CONTENTS_MONSTER)
////#define   MASK_BLOCKLOS                 (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_BLOCKLOS)
////#define   MASK_BLOCKLOS_AND_NPCS        (MASK_BLOCKLOS|CONTENTS_MONSTER)
////#define   MASK_VISIBLE                  (MASK_OPAQUE|CONTENTS_IGNORE_NODRAW_OPAQUE)
////#define   MASK_VISIBLE_AND_NPCS         (MASK_OPAQUE_AND_NPCS|CONTENTS_IGNORE_NODRAW_OPAQUE)
////#define   MASK_SHOT                     (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)
////#define   MASK_SHOT_BRUSHONLY           (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_DEBRIS)
////#define   MASK_SHOT_HULL                (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_GRATE)
////#define   MASK_SHOT_PORTAL              (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER)
////#define   MASK_SOLID_BRUSHONLY          (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_GRATE)
////#define   MASK_PLAYERSOLID_BRUSHONLY    (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_PLAYERCLIP|CONTENTS_GRATE)
////#define   MASK_NPCSOLID_BRUSHONLY       (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
////#define   MASK_NPCWORLDSTATIC           (CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
////#define   MASK_NPCWORLDSTATIC_FLUID     (CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP)
////#define   MASK_SPLITAREAPORTAL          (CONTENTS_WATER|CONTENTS_SLIME)
////#define   MASK_CURRENT                  (CONTENTS_CURRENT_0|CONTENTS_CURRENT_90|CONTENTS_CURRENT_180|CONTENTS_CURRENT_270|CONTENTS_CURRENT_UP|CONTENTS_CURRENT_DOWN)
////#define   MASK_DEADSOLID                (CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_GRATE)
////
////struct AimbotConfig
////{
////	float maxInaccuracy{};
////	float fov{};
////	bool slowwalk{};
////};
////
////AimbotConfig testConfig{ 0.07f, 30, true };
////
////void slowwalk(CUserCmd* cmd)
////{
////	const auto weapon = localplayer->activeWeapon();
////	if (!weapon)
////		return;
////	const auto data = weapon->weaponData();
////	if (!data)
////		return;
////
////	const float maxSpeed{ (localplayer->isScoped() ? data->maxSpeedAlt : data->maxSpeed) / 4 };
////
////	if (cmd->forwardmove && cmd->sidemove)
////	{
////		const float maxSpeedRoot{ maxSpeed * static_cast<float>(0.707106781186547524401) };
////		cmd->forwardmove = cmd->forwardmove < 0.0f ? -maxSpeedRoot : maxSpeedRoot;
////		cmd->sidemove = cmd->sidemove < 0.0f ? -maxSpeedRoot : maxSpeedRoot;
////	}
////	else if (cmd->forwardmove)
////		cmd->forwardmove = cmd->forwardmove < 0.0f ? -maxSpeed : maxSpeed;
////	else if (cmd->sidemove)
////		cmd->sidemove = cmd->sidemove < 0.0f ? -maxSpeed : maxSpeed;
////}
////
////constexpr float damageMult(int hitgroup)
////{
////	switch (hitgroup)
////	{
////	case 0: return 4.0f; // Head
////	case 3: return 1.25f; // Stomach
////	case 6: // Rightleg
////	case 7: return 0.75f; // Left leg
////	}
////
////	return 1.0f;
////}
////
////constexpr bool hasArmor(int hitgroup, bool helmet)
////{
////	if (hitgroup == 1)
////		return helmet;
////	else if (hitgroup <= 5)
////		return true;
////	else
////		return false;
////}
////
////bool traceToExit(trace_t* enter_trace, Vector start, Vector dir, trace_t* exit_trace)
////{
////#if defined(_WIN32)
////	Vector end = { 0.f, 0.f, 0.f };
////	float distance = 0.f;
////	signed int distCheck = 25;
////	int firstContents = 0;
////
////	do
////	{
////		distance += 3.5f;
////		end = start + dir * distance;
////
////		if (!firstContents) firstContents = interfaces::engineTrace->getPointContents(end, MASK_SHOT | CONTENTS_GRATE);
////
////		const int pointContents = interfaces::engineTrace->getPointContents(end, MASK_SHOT | CONTENTS_GRATE);
////
////		if (!(pointContents & (MASK_SHOT_HULL | CONTENTS_HITBOX)) || pointContents & CONTENTS_HITBOX && pointContents != firstContents)
////		{
////			const Vector newEnd = end - (dir * 4.f);
////
////			const Ray_t ray(end, newEnd);
////
////			interfaces::engineTrace->TraceRay(ray, MASK_SHOT | CONTENTS_GRATE, nullptr, *exit_trace);
////
////			if (exit_trace->startSolid && exit_trace->surface.flags & SURF_HITBOX)
////			{
////				interfaces::engineTrace->TraceRay({ end, start }, MASK_SHOT_HULL | CONTENTS_HITBOX, exit_trace->entity, *exit_trace);
////
////				if (exit_trace->DidHit() && !exit_trace->startSolid) return true;
////
////				continue;
////			}
////
////			if (exit_trace->DidHit() && !exit_trace->startSolid)
////			{
////				if (enter_trace->surface.flags & SURF_NODRAW || !(exit_trace->surface.flags & SURF_NODRAW)) {
////					if (exit_trace->plane.normal.Dot(dir) <= 1.f)
////						return true;
////
////					continue;
////				}
////
////				if (IsBreakableEntity(enter_trace->entity)
////					&& IsBreakableEntity(exit_trace->entity))
////					return true;
////
////				continue;
////			}
////
////			if (exit_trace->surface.flags & SURF_NODRAW)
////			{
////				if (IsBreakableEntity(enter_trace->entity)
////					&& IsBreakableEntity(exit_trace->entity))
////				{
////					return true;
////				}
////				else if (!(enter_trace->surface.flags & SURF_NODRAW))
////				{
////					continue;
////				}
////			}
////
////			if ((!enter_trace->entity
////				|| enter_trace->entity->entityListIndex() == 0)
////				&& (IsBreakableEntity(enter_trace->entity)))
////			{
////				exit_trace = enter_trace;
////				exit_trace->endpos = start + dir;
////				return true;
////			}
////			continue;
////		}
////		distCheck--;
////	} while (distCheck);
////
////	return false;
////#endif
////	//linux users, no tracetoexit for you :(
////	return false;
////}
////
////float handleBulletPenetration(SurfaceData* enterSurfaceData, const trace_t& enterTrace, const Vector& direction, Vector& result, float penetration, float damage)
////{
////	Vector end;
////	trace_t exitTrace;
////
////	if (!traceToExitAlt(enterTrace, enterTrace.endpos, direction, end, exitTrace))
////		return -1.0f;
////
////	SurfaceData* exitSurfaceData = interfaces::surfaceData->GetSurfaceData(exitTrace.surface.surfaceProps);
////
////	float damageMod = 0.16f;
////	float penetrationMod{ (enterSurfaceData->penetrationmodifier + exitSurfaceData->penetrationmodifier) / 2.0f };
////
////	if (enterSurfaceData->material == 71 || enterSurfaceData->material == 89)
////	{
////		damageMod = 0.05f;
////		penetrationMod = 3.0f;
////	}
////	else if (enterTrace.contents >> 3 & 1 || enterTrace.surface.flags >> 7 & 1)
////		penetrationMod = 1.0f;
////
////	if (enterSurfaceData->material == exitSurfaceData->material)
////	{
////		if (exitSurfaceData->material == 85 || exitSurfaceData->material == 87)
////			penetrationMod = 3.0f;
////		else if (exitSurfaceData->material == 76)
////			penetrationMod = 2.0f;
////	}
////
////	damage -= 11.25f / penetration / penetrationMod + damage * damageMod + (exitTrace.endpos - enterTrace.endpos).LengthSqr() / 24.0f / penetrationMod;
////
////	result = exitTrace.endpos;
////	return damage;
////}
////
////bool hitscan(PlayerEntity* ent, const Vector& destination, const WeaponInfo* weaponData, int minDamage)
////{
////	if (!localplayer || !localplayer->isAlive())
////		return false;
////
////	float damage{ static_cast<float>(weaponData->damage) };
////	
////	Vector eyePos{ localplayer->eyePosition() };
////	Vector direction{ destination - eyePos };
////
////	int surfacesLeft = 4;
////
////	while (damage >= 1.0f && surfacesLeft)
////	{
////		trace_t trace;
////		interfaces::engineTrace->TraceRay(Ray_t{ eyePos, destination }, 0x4600400B, traceFilter{ localplayer }, trace);
////
////		//IsOtherEnemy?
////
////		if (trace.fraction == 1.0f)
////			break;
////
////		if (trace.entity == ent && trace.hitgroup > 0 && trace.hitgroup <= 7)
////		{
////			damage = damageMult(trace.hitgroup) * damage * std::pow(weaponData->rangeModifier, trace.fraction * weaponData->range / 500.0f);
////
////			if (float armorRatio{ weaponData->armorRatio / 2.0f }; hasArmor(trace.hitgroup, trace.entity->hasHelmet()))
////				damage -= (trace.entity->armor() < damage * armorRatio / 2.0f ? trace.entity->armor() * 4.0f : damage) * (1.0f - armorRatio);
////
////			return damage >= minDamage;
////		}
////		const auto surfaceData = interfaces::surfaceData->GetSurfaceData(trace.surface.surfaceProps);
////
////		if (surfaceData->penetrationmodifier < 0.1f)
////			break;
////
////		damage = handleBulletPenetration(surfaceData, trace, direction, eyePos, weaponData->penetration, damage);
////		surfacesLeft--;
////	}
////	return false;
////}
//
//void aimbot(CUserCmd* cmd)
//{
//	if (!localplayer || !localplayer->isAlive())
//		return;
//
//	const auto activeWeapon = localplayer->activeWeapon();
//	if (!activeWeapon)
//		return;
//
//	if (GetAsyncKeyState(VK_XBUTTON2) >> 15)
//	{
//		Vector angle;
//		float bestFov{ 255.0f };
//		PlayerEntity* bestTarget = nullptr;
//		int bestHitbox{ -1 };
//
//		for (int i = 1; i <= interfaces::engine->GetMaxClients(); i++)
//		{
//			const auto ent = interfaces::entityList->GetClientEntity<PlayerEntity>(i);
//
//			if (!ent || !ent->isPlayer() || ent == localplayer || ent->dormant() || ent->team() == localplayer->team() ||
//				!ent->isAlive() || ent->gunGameImmunity())
//				continue;
//
//			bool shouldBaim{ false };
//
//			if (!shouldBaim && hitscan(ent, ent->hitboxPos(0), activeWeapon->weaponData(), 0))
//				bestHitbox = 0;
//			else
//			{
//				for (auto hitbox : { 6, 5, 4, 2 })
//				{
//					if (hitscan(ent, ent->hitboxPos(hitbox), activeWeapon->weaponData(), 0))
//						bestHitbox = hitbox;
//				}
//			}
//
//			if (bestHitbox == -1)
//				continue;
//
//			auto hitboxPos = ent->hitboxPos(bestHitbox) - localplayer->eyePosition();
//			vector_angles(hitboxPos, angle);
//			normalize3(angle);
//			angle.clamp();
//
//			auto fov{ get_fov(cmd->viewAngles, angle) };
//
//			if (fov < bestFov)
//			{
//				bestTarget = ent;
//				bestFov = fov;
//			}
//		}
//
//		if (bestTarget && bestHitbox != -1 && bestFov <= testConfig.fov)
//		{
//			if (testConfig.slowwalk)
//				slowwalk(cmd);
//
//			if (activeWeapon->inaccuracy() <= testConfig.maxInaccuracy)
//			{
//				localplayer->aimAt(bestTarget->hitboxPos(bestHitbox), cmd);
//				cmd->buttons |= CUserCmd::IN_ATTACK;
//			}
//		}
//	}
//}