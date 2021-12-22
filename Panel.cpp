#include <vector>

#include "Color.h"
#include "interfaces.h"
#include "Panel.h"

int DynamicPanel::add_child(std::wstring childTitle, std::wstring childOption)
{
	ChildPanel child{ childTitle, childOption };

	children.push_back(child);

	return children.size() - 1;
}

void DynamicPanel::temp_child(int& offset, std::wstring childTitle, std::wstring childOption)
{
	using namespace interfaces;

	offset += h;

	surface->DrawSetColor(colors::grey);
	surface->DrawFilledRect(x, y + offset, x + w, y + offset + h);
	surface->DrawSetColor(colors::black);
	surface->DrawOutlinedRect(x - 1, y + offset - 1, (x + w) + 1, y + (offset + h) + 1);

	surface->DrawLine((x + (x + w)) / 2, y + offset, (x + (x + w)) / 2, y + offset + h);

	print_text(childTitle, x + 10, y + offset + 5, colors::white, font);
	print_text(childOption, ((x + (x + w)) / 2) + 10, y + offset + 5, colors::white, font);
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

void DynamicPanel::display(int index, float displayOption)
{
	children.at(index).hidden = false;
	auto wstr{ std::to_wstring(displayOption) };
	wstr.erase(wstr.begin() + wstr.find(L'.') + 4, wstr.end()); // Two points of precision
	children.at(index).option = wstr;
}

void DynamicPanel::draw()
{
	using namespace interfaces;

	surface->DrawSetColor(colors::grey);

	surface->DrawFilledRect(x, y, x + w, y + h);
	surface->DrawSetColor(colors::black);
	surface->DrawOutlinedRect(x - 1, y - 1, (x + w) + 1, (y + h) + 1);

	int wide, tall;
	surface->GetTextSize(font, title.c_str(), wide, tall);

	print_text(title, ((x + (x + w)) / 2) - (wide / 2), y + h / 4, colors::white, font);

	for (size_t i{ 0 }, offset{ static_cast<size_t>(y + h) }; i < children.size(); i++)
	{
		if (!children.at(i).hidden)
		{
			surface->DrawSetColor(colors::grey);
			surface->DrawFilledRect(x, offset, x + w, offset + h);
			surface->DrawSetColor(colors::black);
			surface->DrawOutlinedRect(x - 1, offset - 1, (x + w) + 1, (offset + h) + 1);

			surface->DrawLine((x + (x + w)) / 2, offset, (x + (x + w)) / 2, offset + h);

			print_text(children.at(i).title, x + 10, offset + 5, colors::white, font);
			print_text(children.at(i).option, ((x + (x + w)) / 2) + 10, offset + 5, colors::white, font);
			
			offset += h;
		}
	}
}