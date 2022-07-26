#pragma once
#include <iostream>
#include "party.h"
#include "helper.h"

using namespace std;
namespace Elections
{
	class party;

	class results
	{
	protected:
		int numOfCitizens;
		int numOfVoters;

		struct partyResult
		{
			party* party = nullptr;
			int numberOfVotes = 0;
			int repsNum;
			float votersPercentage;
	
			list<citizen*>* repsList = nullptr;
		};

		DynamicArray<partyResult> dstrctResults;

	public:
		results() : numOfCitizens(0), numOfVoters(0) {}
		results(const results& r) = delete;
		virtual ~results() {}

		//getters;
		int getRepsNum(int partySn);
		float getPercentage() const;
		const DynamicArray<partyResult>& getDstrctResults() const { return dstrctResults; }

		//setters;
		bool updateCitizensNum() { numOfCitizens++; return true; }
		bool updateVotersNum() { numOfVoters++; return true; }
		bool setParty(party* p);
		void addVoter(int partySn);
		bool setPercentage();
		void setNumReps(int repsNum);
		void addRepToList(int partySn, citizen* rep);

		friend ostream& operator<<(ostream& os, const results& res);
		virtual void toOs(ostream& os) const;
		void Sort(int size); //sorting the results of district;

		//file;
		void save(ofstream& out_file) const;
		void load(ifstream& out_file);
	};
}


