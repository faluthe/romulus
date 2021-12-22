#pragma once

#include <deque>

#include "Matrix.h"
#include "Vector.h"

struct Records
{
	Vector head;
	float simTime;
	Matrix matrix[128];
};

extern std::deque<Records> records[65];

namespace sharedrecords
{
	void update();
}