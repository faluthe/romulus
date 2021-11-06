#pragma once

#include "helper.h"

class ConVar
{
public:
	char pad0[12];
	const char* name;

	VIRTUAL_METHOD(float, GetFloat, 12, (), (this))
	VIRTUAL_METHOD(int, GetInt, 13, (), (this))
	VIRTUAL_METHOD(void, SetString, 14, (const char* string), (this, string))
	VIRTUAL_METHOD(void, SetFloat, 15, (float value), (this, value))
	VIRTUAL_METHOD(void, SetInt, 16, (int value), (this, value))
};