#pragma once
#include <list>
#include <iostream>
#include <fstream>

#include "DynamicArray.h"
#include "citizen.h"
#include "helper.h"

using namespace std;
namespace Elections
{
	class party
	{
		friend class elections;

		struct repsOfDstrct
		{
			int currReps = 0;
			int numberOfReps;
			list<citizen*>* repList;
		};

		string name;
		int Sn;
		const citizen& leader;
		DynamicArray<repsOfDstrct>* reps;

	public:
		party(const string& name, const citizen& leader, int Sn, int numOfDistricts);
		party(const party& p) = delete;
		~party() {}

		//getters;
		const string& getPartyName() const { return name; }
		const int getSn() const { return Sn; }
		const citizen& getLeader() const { return leader; }
		DynamicArray<repsOfDstrct>& getReps() { return *reps; }
		int getRepsSize() const { return (*reps).size(); }

		//setters;
		bool setRepsNum(int dstrctSn, int repsNum); 
		bool setDistrictToParty(int dstrctSn, int repsNum);
		void insertDistrictToPartyRes(int repsNum); 
		bool repsFull(int idx) const;
		void printReps();
		friend ostream& operator<<(ostream& os, const party& p);
		bool operator==(const party& other)const;

		//file;
		void save(ofstream& file) const;
	};
}


