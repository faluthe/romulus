#pragma once

struct Color
{
	const int r, g, b, a;
};

namespace colors
{
	constexpr Color black{ 0, 0, 0, 255 };
	constexpr Color grey{ 60, 60, 60, 255 };
	constexpr Color white{ 255, 255, 255, 255 };
}