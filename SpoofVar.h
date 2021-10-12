#pragma once

#include "ConVar.h"

class SpoofVar
{
private:
	ConVar* pOgConVar;
	const char* originalName;
	const char* newName;
	int originalValue;
	int newValue;
public:
	SpoofVar(ConVar* pConVar, const char* newName, int newVal);
	~SpoofVar();
	int GetValue();
	void SetValue(int newValue);
};