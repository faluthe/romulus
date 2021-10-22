#include "ConVar.h"
#include "interfaces.h"
#include "SpoofVar.h"

SpoofVar::SpoofVar(ConVar* pConVar, const char* newNameVal, float newVal)
	: pOgConVar{ pConVar }
{
	newValue = newVal;
	newName = newNameVal;
	if (pOgConVar)
	{
		interfaces::cvar->UnregisterConCommand(pOgConVar);
		originalName = pOgConVar->name;
		originalValue = pOgConVar->GetFloat();
		
		pOgConVar->name = newName;
		interfaces::cvar->RegisterConCommand(pOgConVar);
		pOgConVar->SetFloat(newVal);
	}
}

SpoofVar::~SpoofVar()
{
	if (pOgConVar)
	{
		interfaces::cvar->UnregisterConCommand(pOgConVar);
		pOgConVar->name = originalName;
		pOgConVar->SetFloat(originalValue);
		interfaces::cvar->RegisterConCommand(pOgConVar);
	}
}

float SpoofVar::GetFloat()
{
	return pOgConVar->GetFloat();
}

void SpoofVar::SetValue(float newVal)
{
	pOgConVar->SetFloat(newVal);
}