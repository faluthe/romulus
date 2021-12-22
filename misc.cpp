#include "config.h"
#include "interfaces.h"
#include "helper.h"
#include "localplayer.h"

void antiflash()
{
	if (localplayer && config::antiflash)
		localplayer->flashAlpha() = 50.0f;
	if (localplayer && !config::antiflash)
		localplayer->flashAlpha() = 255.0f;
}

void restore_flash()
{
	if (localplayer)
		localplayer->flashAlpha() = 255.0f;
}

void thirdperson()
{
	static bool inThirdperson = false;
	if (!localplayer || !localplayer->isAlive())
	{
		inThirdperson = false;
		interfaces::input->cameraInThirdperson = false;
		return;
	}

	if (GetAsyncKeyState(VK_MENU) & 1)
		inThirdperson = !inThirdperson;

	interfaces::input->cameraInThirdperson = inThirdperson;
	
	if (inThirdperson)
		interfaces::input->cameraOffset.z = 150.0f;
}