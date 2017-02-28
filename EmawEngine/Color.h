#pragma once

#include "Types.h"

struct Color
{
	u32 value;

	Color() {}
	Color(u8 red, u8 green, u8 blue, u8 alpha) : 
		value((red << 24) | (green << 16) | (blue << 8) | alpha) {}
};

struct ColorFloat
{
	f32 red;
	f32 green;
	f32 blue;
	f32 alpha;

	ColorFloat() {}
	ColorFloat(f32 red, f32 green, f32 blue, f32 alpha) :
		red(red), green(green), blue(blue), alpha(alpha) {}
};