#include <iostream>
#include "results.h"
#include "unitedResults.h"

using namespace std;
namespace Elections
{
	bool results::setParty(party* p)
	{
		partyResult* r = new partyResult;
		r->party = p;
		r->repsList = new list<citizen*>();

		dstrctResults.insert(dstrctResults.end(), *r);

		return true;
	}

	void results::addVoter(int partySn)
	{
		if (partySn >= dstrctResults.size())
			throw invalid_argument("No such party");

		dstrctResults[partySn].numberOfVotes++;
		numOfVoters++;
	}

	bool results::setPercentage()
	{
		for (auto i = dstrctResults.begin(); i != dstrctResults.end(); ++i)
			(*i).votersPercentage = (static_cast<float>((*i).numberOfVotes / static_cast<float>(numOfVoters)) * 100);

		return true;
	}


	float results::getPercentage() const
	{
		float res = (static_cast<float>(numOfVoters) / static_cast<float>(numOfCitizens)) * 100;

		return res;
	}


	int results::getRepsNum(int partySn)
	{
		return (dstrctResults[partySn].repsNum);
	}


	void results::setNumReps(int repsNum)
	{
		for (auto i = dstrctResults.begin(); i != dstrctResults.end() ; ++i)
		{
			float TempNumOfReps = (((*i).votersPercentage) * repsNum) / 100;
			int numOfReps = static_cast<int>(TempNumOfReps);
		
			(*i).repsNum = numOfReps;
		}
	}


	void results::addRepToList(int partySn, citizen* rep)
	{
		dstrctResults[partySn].repsList->push_back(rep);
	}


	ostream& operator<<(ostream& os, const results& res)
	{
		os << "Percentage of voters: " << res.getPercentage() << "%" << endl << endl;
		res.toOs(os);

		for (int i = 0; i < res.getDstrctResults().size(); ++i)
		{
			os << "Party serial number : " << i << endl << endl
				<< "Number of voters: " << res.dstrctResults[i].numberOfVotes << endl
				<< "Percentage of voters: " << res.dstrctResults[i].votersPercentage << "%" << endl
				<< "Representatives list:" << endl;

			printList(*(res.dstrctResults[i].repsList));
		}

		return os;
	}

	void results::Sort(int size)
	{
		for (int i = 0; i < size - 1; i++)
			for (int j = 0; j < size - i - 1; i++)
				if (dstrctResults[i].repsNum < dstrctResults[i + 1].repsNum)
					Swap(dstrctResults[i], dstrctResults[i + 1]);
	}

	void results::toOs(ostream& os) const
	{
		os << "Candidates by electors: " << endl;

		for (int i = 0; i < dstrctResults.size(); ++i)
			os << "Candidate: " << dstrctResults[i].party->getLeader() << endl
				<< "Number of Representatives: " << dstrctResults[i].repsNum << endl << endl;

	}

	void results::save(ofstream& file) const
	{
		file.write(rcastcc(&numOfVoters), sizeof(int));
		int size = dstrctResults.size();
		file.write(rcastcc(&size), sizeof(int));

		for (int i = 0; i < size; ++i)
			file.write(rcastcc(&(dstrctResults[i].numberOfVotes)), sizeof(int));
	}

	void results::load(ifstream& file)
	{
		int partiesSize, Sn;
		file.read(rcastc(&numOfVoters), sizeof(int));
		file.read(rcastc(&partiesSize), sizeof(int));

		for (int i = 0; i < partiesSize; i++)
			file.read(rcastc(&(dstrctResults[i].numberOfVotes)), sizeof(int));

	}
}