#pragma once

class Hook
{
private:
	const void* pInterface;
public:
	Hook() = default;
	Hook(void* pInterface);
	void hookFunc(unsigned short index, void* hkFunc, void** ogFunc);
};