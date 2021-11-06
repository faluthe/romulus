#pragma once

#include "helper.h"

class IPanel
{
public:
    VIRTUAL_METHOD(const char*, GetName, 36, (unsigned int id), (this, id))
};