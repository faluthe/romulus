#pragma once

#include "Vector.h"

class IInput
{
public:
	char pad0[173];
	bool cameraInThirdperson;
	bool cameraMovingWithMouse;
	Vector cameraOffset;
};