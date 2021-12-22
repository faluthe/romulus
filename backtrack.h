#pragma once

#include <deque>

struct CUserCmd;
class INetChannel;

struct SequenceData
{
	SequenceData(int instate, int outstate, int seqnr, float realtime)
	{
		inreliablestate = instate;
		outreliablestate = outstate;
		sequencenr = seqnr;
		Realtime = realtime;
	}
	int inreliablestate;
	int outreliablestate;
	int sequencenr;
	float Realtime;
};

extern std::deque<SequenceData> sequences;

bool valid_tick(float simTime);
int time2ticks(float time);
float ticks2time(int ticks);

namespace backtrack
{
	void init();
	void run(CUserCmd* cmd);
	void addLatencyToNetChan(INetChannel* netchannel, float latency);
	void updateIncomingSequences();
	inline int lastSequence{ 0 };
	inline int selectedTarget{};
	inline int selectedIndex{};
}