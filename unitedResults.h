#pragma once
#include "results.h"

using namespace std;

namespace Elections
{
	class unitedResults : public results
	{
		party* winnerPrty;

	public:
		unitedResults() : results(), winnerPrty(nullptr) {}
		unitedResults(const unitedResults& r) = delete;
		virtual ~unitedResults() {}

		const party& getWinnerPrty() const { return *winnerPrty; }
		bool setWinnerPrty();

		virtual void toOs(ostream& os) const;
	};
}

