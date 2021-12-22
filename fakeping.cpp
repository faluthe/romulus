#include <deque>

#include "backtrack.h"
#include "INetChannel.h"
#include "interfaces.h"

std::deque<SequenceData> sequences;

void backtrack::addLatencyToNetChan(INetChannel* netchannel, float latency)
{
	for (auto& seq : sequences)
	{
		if (interfaces::globalVars->realtime - seq.Realtime >= latency)
		{
			netchannel->m_nInReliableState = seq.inreliablestate;
			netchannel->m_nInSequenceNr = seq.sequencenr;
			break;
		}
	}
}

void backtrack::updateIncomingSequences()
{
	if (interfaces::clientState)
	{
		// Does this matter?
		interfaces::netChannel = *reinterpret_cast<INetChannel**>(reinterpret_cast<uintptr_t>(interfaces::clientState) + 0x9C);
		if (interfaces::netChannel)
		{
			if (interfaces::netChannel->m_nInSequenceNr > lastSequence)
			{
				lastSequence = interfaces::netChannel->m_nInSequenceNr;

				sequences.push_front(SequenceData{ interfaces::netChannel->m_nInReliableState, interfaces::netChannel->m_nOutReliableState, interfaces::netChannel->m_nInSequenceNr, interfaces::globalVars->realtime });
			}

			if (sequences.size() > 2048)
				sequences.pop_back();
		}
	}
}