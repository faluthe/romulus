#pragma once

#include "helper.h"

class IMaterial
{
public:
	VIRTUAL_METHOD(const char*, GetName, 0, (), (this))
	VIRTUAL_METHOD(const char*, TextureGroupName, 1, (), (this))
	VIRTUAL_METHOD(void, AlphaModulate, 27, (float alpha), (this, alpha))
	VIRTUAL_METHOD(void, ColorModulate, 28, (float red, float green, float blue), (this, red, green, blue))
	VIRTUAL_METHOD(void, SetMaterialVarFlags, 29, (int flag, bool on), (this, flag, on))
	VIRTUAL_METHOD(bool, IsPrecached, 70, (), (this))
};