#pragma once

#include <string>
#include <vector>

class Panel
{
private:
	int x, y;
	int w, h;
	std::wstring title;
	std::wstring option;
	Panel* previous{};
	Panel* next{};
	void add_next(Panel* nextPanel);
public:
	Panel(std::wstring title, std::wstring option, int x, int y, int w = 250, int h = 30)
		: x{ x }, y{ y }, w{ w }, h{ h }, title{ title }, option{ option }
	{
	}
	Panel add_entry(Panel* nextPanel, std::wstring panelTitle, std::wstring panelOption = L"");
	void set_option(int option);
	void set_option(std::wstring newOption);
	void draw();
};