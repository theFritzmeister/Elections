#pragma once
#include<iostream>
#include"Elections.h"

namespace Elections
{
	class Final
	{
		party* prty = nullptr;
		int numOfElects = 0;
		int totalVotes = 0;

	public:
		Final() : prty(nullptr) {}
		~Final() = default;

		int getNumOfElects() { return numOfElects; }
		int getTotalVotes() { return totalVotes; }
		void setParty(party* p) { prty = p; }
		party* getParty() const { return prty; }

		friend ostream& operator<<(ostream& os, const Final& res);
		void operator=(const Final& other);
	};
}


