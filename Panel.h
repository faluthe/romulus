#pragma once

#include <string>
#include <vector>

class ChildPanel
{
public:
	std::wstring title;
	std::wstring option;
	bool hidden{ false };
};

class DynamicPanel
{
private:
	int x, y;
	int w, h;
	unsigned int font;
	std::wstring title;
public:
	std::vector<ChildPanel> children;
	DynamicPanel(std::wstring title, unsigned int font, int x, int y, int w = 250, int h = 30)
		: title{ title }, font{ font }, x{ x }, y{ y }, w{ w }, h{ h }
	{
	}
	int add_child(std::wstring childTitle, std::wstring childOption = L"");
	void temp_child(int& offset, std::wstring title, std::wstring option);
	void hide(int index);
	void display(int index, std::wstring displayOption);
	void display(int index, int displayOption);
	void display(int index, float displayOption);
	void draw();
};