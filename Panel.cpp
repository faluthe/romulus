#include <vector>

#include "Color.h"
#include "helper.h"
#include "interfaces.h"
#include "Panel.h"

int DynamicPanel::add_child(std::wstring childTitle, std::wstring childOption)
{
	ChildPanel child{ childTitle, childOption };

	children.push_back(child);

	return children.size() - 1;
}

void DynamicPanel::hide(int index)
{
	children.at(index).hidden = true;
}

void DynamicPanel::display(int index, std::wstring displayOption)
{
	children.at(index).hidden = false;
	children.at(index).option = displayOption;
}

void DynamicPanel::display(int index, int displayOption)
{
	children.at(index).hidden = false;
	children.at(index).option = std::to_wstring(displayOption);
}

void DynamicPanel::draw()
{
	interfaces::surface->DrawSetColor(colors::grey);

	interfaces::surface->DrawFilledRect(x, y, x + w, y + h);
	interfaces::surface->DrawSetColor(colors::black);
	interfaces::surface->DrawOutlinedRect(x - 1, y - 1, (x + w) + 1, (y + h) + 1);

	int wide, tall;
	interfaces::surface->GetTextSize(font, title.c_str(), wide, tall);

	print_text(title, ((x + (x + w)) / 2) - (wide / 2), y + h / 4, colors::white);

	for (size_t i{ 0 }, offset{ static_cast<size_t>(y + h) }; i < children.size(); i++)
	{
		if (!children.at(i).hidden)
		{
			interfaces::surface->DrawSetColor(colors::grey);
			interfaces::surface->DrawFilledRect(x, offset, x + w, offset + h);
			interfaces::surface->DrawSetColor(colors::black);
			interfaces::surface->DrawOutlinedRect(x - 1, offset - 1, (x + w) + 1, (offset + h) + 1);

			interfaces::surface->DrawLine((x + (x + w)) / 2, offset, (x + (x + w)) / 2, offset + h);

			print_text(children.at(i).title, x + 10, offset + 5, colors::white);
			print_text(children.at(i).option, ((x + (x + w)) / 2) + 10, offset + 5, colors::white);
			
			offset += h;
		}
	}
}