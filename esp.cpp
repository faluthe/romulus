#include <string>
#include <vector>

#include "backtrack.h"
#include "Color.h"
#include "Config.h"
#include "Entity.h"
#include "helper.h"
#include "interfaces.h"
#include "localplayer.h"
#include "structs.h"
#include "Vector.h"

unsigned long espFont;

RECT get_bbox(Entity* ent)
{
	RECT box{};
	Vector top, bottom;

	world_to_screen(ent->hitboxPos(0) + Vector{ 0, 0, 8 }, top); // 0 = head
	world_to_screen(ent->absOrigin() - Vector{ 0, 0, 8 }, bottom);

	int mid{ static_cast<int>(bottom.y - top.y) };
	int width{ static_cast<int>(mid / 4.0f) };

	box.bottom = static_cast<long>(top.y + mid);
	box.top = static_cast<long>(top.y);
	box.left = static_cast<long>(bottom.x - width);
	box.right = static_cast<long>(bottom.x - width + width * 2);

	return box;
}

void player_esp()
{
	using namespace interfaces;

	for (int i{ 1 }; i < engine->GetMaxClients(); i++)
	{
		const auto ent{ entityList->GetClientEntity<PlayerEntity>(i) };

		if (!ent || !ent->isAlive() || ent->dormant() || ent->team() == localplayer->team() || (localplayer->observerTarget() == ent && localplayer->observerMode() == OBSMode::InEye))
			continue;

		RECT box{ get_bbox(ent) };

		// Box
		surface->DrawSetColor(255, 255, 255, 255);
		surface->DrawOutlinedRect(box.left, box.top, box.right, box.bottom);
		surface->DrawSetColor(0, 0, 0, 255);
		surface->DrawOutlinedRect(box.left - 1, box.top - 1, box.right + 1, box.bottom + 1);
		surface->DrawOutlinedRect(box.left + 1, box.top + 1, box.right - 1, box.bottom - 1);

		// Name
		player_info_t info;
		
		if (!engine->GetPlayerInfo(i, &info))
			return;

		wchar_t name[128];

		if (MultiByteToWideChar(CP_UTF8, 0, info.name, -1, name, 128))
			print_text(name, box.left, box.top - 15, colors::white, espFont);

		// Health
		const Color* health;
		if (ent->health() > 75)
			health = &colors::green;
		else if (ent->health() > 25)
			health = &colors::yellow;
		else
			health = &colors::red;

		print_text(L"Health: " + std::to_wstring(ent->health()), box.right + 10, box.bottom, *health, espFont);

		// Armor
		print_text(L"Armor: " + std::to_wstring(ent->armor()), box.right + 10, box.bottom + 15, colors::blue, espFont);

		// Active Weapon
		if (const auto weapon{ ent->activeWeapon() })
			print_text(weapon->weaponTypeStr(), box.right + 10, box.bottom + 30, colors::white, espFont);

		// Bomb carrier
		if (ent->isBombCarrier())
			print_text(L"Bomb", box.right + 10, box.bottom + 45, colors::yellow, espFont);
	}
}

void grenade_esp()
{
	using namespace interfaces;

	for (int i{ 1 }; i < entityList->GetMaxEntities(); i++)
	{
		const auto ent{ entityList->GetClientEntity<Entity>(i) };

		if (!ent || !ent->isGrenade())
			continue;
		
		RECT box{ get_bbox(ent) };

		int x{ (box.right + box.left) / 2 };
		int y{ (box.bottom + box.top) / 2 };

		switch (ent->clientClass()->classId)
		{
		case ClassId::GrenadeProjectile:
			if (auto studioModel{ interfaces::mdlInfo->GetStudioModel(ent->model()) })
			{
				std::string name{ studioModel->szName };
				if (name.find("fraggrenade") != std::string::npos)
					print_text(L"Grenade", x, y, colors::red, espFont);
				else if (name.find("flashbang") != std::string::npos)
					print_text(L"Flashbang", x, y, colors::yellow, espFont);
			}
			break;
		case ClassId::DecoyProjectile:
			print_text(L"Decoy", x, y, colors::blue, espFont);
			break;
		case ClassId::MolotovProjectile:
			print_text(L"Fire", x, y, colors::orange, espFont);
			break;
		case ClassId::SmokeProjectile:
			print_text(L"Smoke", x, y, colors::white, espFont);
			break;
		default:
			break;
		}
	}
}

void bomb_esp()
{
	using namespace interfaces;

	for (int i{ 1 }; i < entityList->GetMaxEntities(); i++)
	{
		const auto ent{ entityList->GetClientEntity<Entity>(i) };

		if (!ent || ent->dormant() || !(ent->isC4() || ent->isPlantedC4()))
			continue;

		if (ent->isC4())
		{
			if (ent->vecOrigin() == Vector{ 0, 0, 0 })
				continue;

			RECT box{ get_bbox(ent) };

			int x{ (box.right + box.left) / 2 };
			int y{ (box.bottom + box.top) / 2 };

			print_text(L"Dropped Bomb", x, y, colors::white, espFont);
		}
		else if (ent->isPlantedC4() && !ent->isDefused())
		{
			RECT box{ get_bbox(ent) };

			int x{ (box.right + box.left) / 2 };
			int y{ (box.bottom + box.top) / 2 };

			auto timeToDet{ *reinterpret_cast<float*>((uintptr_t)ent + netvars::c4Blow) };
			auto timer{ timeToDet - globalVars->curtime };
			auto timerStr{ std::to_wstring(timer) };
			timerStr.erase(timerStr.begin() + timerStr.find(L'.') + 2, timerStr.end()); // One point of precision
			if (timer >= 0.0f)
			{
				print_text(L"Planted Bomb", x, y, colors::white, espFont);
				print_text(timerStr, x, y + 15, colors::white, espFont);
				if (timer >= 10.0f)
					print_text(L"Can Defuse", x, y + 30, colors::green, espFont);
				else if (timer >= 5.0f)
					print_text(L"Can Defuse With Kit", x, y + 30, colors::yellow, espFont);
				else
					print_text(L"Cannot Defuse", x, y + 30, colors::red, espFont);
			}
		}
	}
}

void backtrack_ticks()
{
	using namespace interfaces;

	for (int i = 1; i < engine->GetMaxClients(); i++)
	{
		const auto ent = entityList->GetClientEntity<PlayerEntity>(i);

		if (!ent || !ent->isAlive() || ent->dormant() || ent->team() == localplayer->team() || !ent->isVisible())
			continue;

		auto entRecords = records[ent->entityListIndex()];

		for (size_t k = 0; k < entRecords.size(); k++)
		{
			if (!valid_tick(entRecords[k].simTime) || entRecords[k].matrix == nullptr)
				continue;
			
			Vector pos;
			world_to_screen(entRecords[k].head, pos);
			surface->DrawSetColor(colors::white);
			surface->DrawFilledRect(pos.x, pos.y, pos.x + 1, pos.y + 1);
		}
	}
}

void render_esp()
{
	if (!localplayer)
		return;

	if (!espFont && !set_font(espFont, 13, 500))
		return;

	if (config::boxes || localplayer->health() == 0)
		player_esp();

	grenade_esp();
	bomb_esp();
	backtrack_ticks();
}