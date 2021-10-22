#pragma once

#include "helper.h"

struct Ray_t;
struct traceFilter;
struct trace_t;

class IEngineTrace
{
public:
	void TraceRay(Ray_t& ray, unsigned int fMask, traceFilter* pTraceFilter, trace_t* pTrace)
	{
		call_virtual_method<void(__thiscall*)(void*, Ray_t&, unsigned int, traceFilter*, trace_t*)>(this, ENGINETRACE_TRACERAY)(this, ray, fMask, pTraceFilter, pTrace);
	}
};