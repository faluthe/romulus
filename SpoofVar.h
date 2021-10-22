#pragma once

#include "ConVar.h"

class SpoofVar
{
private:
	ConVar* pOgConVar;
	const char* originalName;
	const char* newName;
	float originalValue;
	float newValue;
public:
	SpoofVar(ConVar* pConVar, const char* newName, float newVal);
	~SpoofVar();
	float GetFloat();
	void SetValue(float newValue);
};