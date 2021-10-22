#include <string>

#include "Color.h"
#include "Entity.h"
#include "helper.h"
#include "infopanel.h" // For infofont
#include "interfaces.h"
#include "localplayer.h"
#include "structs.h"
#include "Vector.h"

RECT get_bbox(Entity* ent)
{
	RECT box{};
	Vector top, bottom;

	world_to_screen(ent->hitboxPos(0) + Vector{ 0, 0, 8 }, top);
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
		const auto ent{ entityList->GetClientEntity(i) };

		if (!ent || !ent->isAlive() || ent->dormant() || ent->team() == localplayer->team())
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
			print_text(name, box.right + 10, box.top, colors::white);

		// Health
		const Color* health;
		if (ent->health() > 75)
			health = &colors::green;
		else if (ent->health() > 25)
			health = &colors::yellow;
		else
			health = &colors::red;

		print_text(std::to_wstring(ent->health()), box.right + 10, box.top + 15, *health);
	}
}

void grenade_esp()
{
	using namespace interfaces;

	for (int i{ 1 }; i < entityList->GetMaxEntities(); i++)
	{
		const auto ent{ entityList->GetClientEntity(i) };

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
					print_text(L"Grenade", x, y, colors::red);
				else if (name.find("flashbang") != std::string::npos)
				{
					print_text(L"Flashbang", x, y, colors::yellow);
					surface->DrawSetColor(colors::yellow);
					surface->DrawLine(x, y + 20, x + 70, y + 20);
					surface->DrawSetColor(colors::black);
					surface->DrawOutlinedRect(x - 1, y + 19, x + 71, y + 22);
				}
			}
			break;
		case ClassId::DecoyProjectile:
			print_text(L"Decoy", x, y, colors::blue);
			surface->DrawSetColor(colors::blue);
			surface->DrawLine(x, y + 20, x + 70, y + 20);
			surface->DrawSetColor(colors::black);
			surface->DrawOutlinedRect(x - 1, y + 19, x + 71, y + 22);
			print_text(std::to_wstring(i), x, y + 40, colors::white);
			break;
		case ClassId::MolotovProjectile:
			print_text(L"Fire", x, y, colors::orange);
			break;
		case ClassId::SmokeProjectile:
			print_text(L"Smoke", x, y, colors::white);
			break;
		default:
			break;
		}
	}
}

void render_esp()
{
	if (!localplayer)
		return;

	player_esp();
	grenade_esp();
}