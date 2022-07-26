#include "unitedResults.h"

namespace Elections
{
	bool unitedResults::setWinnerPrty()
	{
		int max = dstrctResults[0].repsNum;

		party* winner = dstrctResults[0].party;

		for (auto i = dstrctResults.begin(); i != dstrctResults.end(); ++i)
		{
			if (max < (*i).repsNum)
			{
				max = (*i).repsNum;
				winner = (*i).party;
			}
		}

		winnerPrty = winner;

		return true;
	}

	void unitedResults::toOs(ostream& os) const
	{
		os << "The winner Candidate in the district is: " << getWinnerPrty().getLeader() << endl;
	}
}