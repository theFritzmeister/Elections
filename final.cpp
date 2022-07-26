#include <iostream>
#include "Elections.h"
#include "final.h"

namespace Elections
{
	ostream& operator<<(ostream& os, const Final& res)
	{
		party* p = res.prty;

		if (p == nullptr)
			throw invalid_argument("No party");

		os << p->getPartyName() << endl << "Leader: " << p->getLeader() << "Total representatives: " <<
			res.numOfElects << endl << "Total votes: " << res.totalVotes << endl;

		return os;
	}

	void Final::operator=(const Final& other)
	{
		prty = other.prty;
		numOfElects = other.numOfElects;
		totalVotes = other.totalVotes;
	}

}