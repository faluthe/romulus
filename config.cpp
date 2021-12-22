#include <string>
#include <Windows.h>

#include "Config.h"
#include "helper.h"
#include "interfaces.h"
#include "Panel.h"

unsigned long configFont{};

void option(DynamicPanel& configPanel, int index, bool& option, int key, std::wstring trueText, std::wstring falseText)
{
	if (GetAsyncKeyState(key) & 1)
		option = !option;

	configPanel.display(index, option ? trueText : falseText);
}

namespace config
{
	void display()
	{
		if (GetAsyncKeyState(VK_INSERT) & 1)
			drawConfigPanel = !drawConfigPanel;

		if (!configFont && !set_font(configFont, 20))
			return;

		if (!screenW || !screenH)
			interfaces::engine->GetScreenSize(screenW, screenH);

		static DynamicPanel configPanel{ L"Configuration", configFont, screenW / 4, 3 };

		static int optionBoxes{ configPanel.add_child(L"Boxes") };
		static int optionChams{ configPanel.add_child(L"Chams") };
		static int optionSilentAim{ configPanel.add_child(L"Silent Aim") };
		static int optionAntiflash{ configPanel.add_child(L"Anti Flash") };

		static int optionDebug{ configPanel.add_child(L"Debug") };

		option(configPanel, optionBoxes, boxes, VK_NUMPAD2, L"ALWAYS", L"Dead Only");
		option(configPanel, optionChams, chamsIgnoreZ, VK_NUMPAD3, L"IGNOREZ", L"Normal");
		option(configPanel, optionSilentAim, silentAim, VK_NUMPAD4, L"ON", L"OFF");
		option(configPanel, optionAntiflash, antiflash, VK_NUMPAD5, L"ON", L"Dead Only");

		option(configPanel, optionDebug, drawDebugPanel, VK_DELETE, L"ON", L"OFF");

		if (drawConfigPanel)
			configPanel.draw();
	}
}