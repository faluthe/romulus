#pragma once

#include <deque>

#include "Vector.h"
#include "Matrix.h"

struct CUserCmd;
class INetChannel;

struct Records
{
	Vector head;
	float simTime;
	Matrix matrix[128];
};

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

extern std::deque<Records> records[65];
extern std::deque<SequenceData> sequences;

bool valid_tick(float simTime);

namespace backtrack
{
	void init();
	void update();
	void run(CUserCmd* cmd);
	void addLatencyToNetChan(INetChannel* netchannel, float latency);
	void updateIncomingSequences();
	inline int lastSequence{ 0 };
	inline int selectedTarget{};
	inline int selectedIndex{};
}