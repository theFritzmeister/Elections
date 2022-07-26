#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "party.h"

using namespace std;

namespace Elections
{
	party::party(const string& name, const citizen& leader, int Sn, int numOfDistricts) : Sn(Sn), leader(leader), name(name)
	{
		if (numOfDistricts < 0)
			throw invalid_argument("Wrong input!");

		reps = new DynamicArray<repsOfDstrct>(numOfDistricts);

		for (int i = 0; i < numOfDistricts; ++i)
			insertDistrictToPartyRes(0);
	}


	void party::insertDistrictToPartyRes(int repsNum)
	{
		repsOfDstrct* rtd = new repsOfDstrct;
		rtd->numberOfReps = repsNum;
		rtd->repList = new list<citizen*>();
		(*reps).insert((*reps).end(), *rtd);
	}


	bool party::setDistrictToParty(int dstrctSn, int repsNum)
	{
		if ((*reps).size() <= dstrctSn)
			insertDistrictToPartyRes(repsNum);
	
		return true;
	}


	bool party::repsFull(int idx) const
	{
		if ((*reps)[idx].numberOfReps == (*reps)[idx].currReps)
			return true;

		else return false;
	}

	ostream& operator<<(ostream& os, const party& p)
	{
		os << "PARTY " << p.Sn + 1 << endl << "Party's serial number: " << p.Sn << ", Party's name: " << p.name << endl
			<< "Party's prime minister candidate: " << p.leader << endl;
		return os;
	}

	bool party::operator==(const party& other)const
	{
		if ((name == other.name) && (Sn == other.Sn))
			return true;
		else
			return false;
	}

	void party::printReps()
	{
		cout << "REPRESENTATIVES LIST:" << endl;
		for (int i = 0; i < (*reps).size(); ++i)
		{
			cout << "District number: " << i << endl;
			cout << "Representatives: " << endl;
			list<citizen*>& lst = *((*reps)[i].repList);
			if (lst.empty())
				throw invalid_argument("There are no citizens.");
			else
				printList(lst);
			cout << endl;
		}
		cout << endl;
	}

	void party::save(ofstream& file) const
	{
		int nameSize = name.length();
		file.write(rcastcc(&nameSize), sizeof(int));//number of bytes for name
		file.write(rcastcc(name.data()), nameSize);
		file.write(rcastcc(&Sn), sizeof(int)); //party serial number 

		int primeID = leader.getID();
		file.write(rcastcc(&primeID), sizeof(int));

		int repsSize = reps->size();
		file.write(rcastcc(&repsSize), sizeof(int)); //districts number (to array)
		for (int i = 0; i < repsSize; ++i)
		{
			file.write(rcastcc(&((*reps)[i].numberOfReps)), sizeof(int));
			for (auto itr = (*reps)[i].repList->begin(); itr != (*reps)[i].repList->end(); ++itr)
			{
				int repID = (*(*itr)).getID();
				file.write(rcastcc(&repID), sizeof(int));
			}
		}
	}
}