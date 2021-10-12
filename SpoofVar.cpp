#include "ConVar.h"
#include "interfaces.h"
#include "SpoofVar.h"

SpoofVar::SpoofVar(ConVar* pConVar, const char* newNameVal, int newVal)
	: pOgConVar{ pConVar }
{
	newValue = newVal;
	newName = newNameVal;
	if (pOgConVar)
	{
		interfaces::cvar->UnregisterConCommand(pOgConVar);
		originalName = pOgConVar->name;
		originalValue = pOgConVar->GetValue();
		
		pOgConVar->name = newName;
		interfaces::cvar->RegisterConCommand(pOgConVar);
		pOgConVar->SetValue(newVal);
	}
}

SpoofVar::~SpoofVar()
{
	if (pOgConVar)
	{
		interfaces::cvar->UnregisterConCommand(pOgConVar);
		pOgConVar->name = originalName;
		pOgConVar->SetValue(originalValue);
		interfaces::cvar->RegisterConCommand(pOgConVar);
	}
}

int SpoofVar::GetValue()
{
	return pOgConVar->GetValue();
}

void SpoofVar::SetValue(int newVal)
{
	pOgConVar->SetValue(newVal);
}