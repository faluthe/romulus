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
	constexpr Color orange{ 255, 127, 39, 255 };
	constexpr Color blue{ 15, 192, 252, 255 };
	constexpr Color green{ 0, 255, 0, 255 };
	constexpr Color yellow{ 255, 255, 0, 255 };
	constexpr Color red{ 255, 0, 0, 255 };
}