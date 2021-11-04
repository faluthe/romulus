#pragma once

struct CUserCmd;

namespace prediction
{
	void start(CUserCmd* cmd);
	void end();
	void run(CUserCmd* cmd);
}