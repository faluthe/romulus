#include <vector>

#include "Color.h"
#include "helper.h"
#include "interfaces.h"
#include "Panel.h"

Panel Panel::add_entry(Panel* nextPanel, std::wstring panelTitle, std::wstring panelOption)
{
	if (next)
		return next->add_entry(nextPanel, panelTitle, panelOption);

	Panel child{ panelTitle, panelOption, x, y + h, w, h };

	if (previous)
		child.y = previous->y + h;
	
	add_next(nextPanel);

	return child;
}

void Panel::add_next(Panel* nextPanel)
{
	next = nextPanel;
	next->previous = this;
}

void Panel::set_option(int newOption)
{
	option.assign(std::to_wstring(newOption));
}

void Panel::set_option(std::wstring newOption)
{
	option.assign(newOption);
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

	if (next)
		next->draw();
}