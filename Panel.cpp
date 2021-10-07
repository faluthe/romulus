#include <vector>

#include "Color.h"
#include "helper.h"
#include "interfaces.h"
#include "Panel.h"

void Panel::add_entry(std::wstring panelTitle, std::wstring panelOption)
{
	if (children.empty())
		children.push_back(Panel{ panelTitle, panelOption, x, y + h, w, h });
	else
		children.push_back(Panel{ panelTitle, panelOption, x, children.back().y + h, w, h });
}

void Panel::draw()
{
	interfaces::surface->DrawSetColor(colors::grey);

	interfaces::surface->DrawFilledRect(x, y, x + w, y + h);
	interfaces::surface->DrawSetColor(colors::black);
	interfaces::surface->DrawOutlinedRect(x - 1, y - 1, (x + w) + 1, (y + h) + 1);

	interfaces::surface->DrawLine((x + (x + w)) / 2, y, (x + (x + w)) / 2, y + h);

	print_text(title, x + 10, y + 5, colors::white);
	print_text(option, ((x + (x + w)) / 2) + 10, y + 5, colors::white);

	for (size_t i{ 0 }; i < children.size(); i++)
	{
		children.at(i).draw();
	}
}