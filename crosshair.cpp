#include "Color.h"
#include "interfaces.h"
#include "localplayer.h"

void external_xhair()
{
	using namespace interfaces;

	if (!localplayer || !localplayer->isAlive())
		return;

	int width, height;
	engine->GetScreenSize(width, height);

	int x = static_cast<int>((width / 2) - (width / 90 * localplayer->aimPunch().y));
	int y = static_cast<int>((height / 2) + (height / 90 * localplayer->aimPunch().x));

	surface->DrawSetColor(colors::red);

	surface->DrawLine(x + 5, y, x - 5, y);
	surface->DrawLine(x, y + 5, x, y - 5);
}