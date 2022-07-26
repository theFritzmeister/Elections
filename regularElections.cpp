#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <typeinfo>
#include "regularElections.h"
#include "unitedResults.h"
#include "helper.h"

namespace Elections
{

	bool regularElections::addDistrict(const string& name, int repsNum, int type)
	{
		int size = districts.size();
		district* d = new district(name, size, type, repsNum);

		districts.insert(districts.end(), d);
		
		for (int i = 0; i < parties.size(); ++i)
			parties[i]->setDistrictToParty(size, districts[size]->getRepNum());
	
		return true;
	}

	void regularElections::addCitizenToList(const string& newName, int ID, int yearOfBirth, int dstrctSn)
	{
		if (dstrctSn < 0 || dstrctSn > districts.size())
			throw invalid_argument("No such district");

		citizen* c1 = searchByID(ID);
		if (c1 != nullptr)
			throw invalid_argument("citizen already exists! ");

		district* dis = districts[dstrctSn];
		c1 = new citizen(newName, ID, yearOfBirth, Date.getYear(), *dis);
		
		citizens.push_back(c1);
		districts[dstrctSn]->citizensDis.push_back(c1);
		districts[dstrctSn]->getRes()->updateCitizensNum();
	}

	void regularElections::setWinToDistricts()
	{
		for (auto i = districts.begin(); i != districts.end(); ++i)
		{
			results* disRes = (*i)->getRes();

			if ((*i)->getType() == UNITED)
			{
				unitedResults* disURes = dynamic_cast<unitedResults*>(disRes);
				disURes->setWinnerPrty();
			}
		}
	}

	void regularElections::makeFinalResults()
	{
		if (!finalResults.empty())
			finalResults.clear();

		int numOfParties = parties.size();
		
		for (int i = 0; i < numOfParties; i++)
		{
			Final* f = new Final();
			f->setParty(parties[i]); 

			finalResults.insert(finalResults.end(), *f);

			for (auto _i=districts.begin(); _i != districts.end(); ++_i)
			{
				results* DisRes = (*_i)->getRes();
				int num = DisRes->getDstrctResults()[i].numberOfVotes;
				addOne(finalResults[i].getTotalVotes(), add());
				
				int numOfelects;

				if ((*_i)->getType() == SPLITTED)
					numOfelects = DisRes->getDstrctResults()[i].repsNum;

				else if (*(parties[i]) == dynamic_cast<unitedResults*>(DisRes)->getWinnerPrty());
					numOfelects = (*_i)->getRepNum();

				addOne(finalResults[i].getNumOfElects(), add());
			}
		}

		SortFinalResults();
	}

	void regularElections::SortFinalResults()
	{
		for (int i = 0; i < finalResults.size() - 1; i++)
			for (int j = 0; j < finalResults.size() - i - 1; i++)
				if (finalResults[j].getNumOfElects() < finalResults[j + 1].getNumOfElects())
					Swap(finalResults[j], finalResults[j + 1]);
	}


	void regularElections::showFinalResult()
	{
		cout << endl << "~FINAL RESULTS~   " << endl << endl;

		for (auto i = finalResults.begin(); i != finalResults.end(); ++i)
			cout << (*i) << endl << endl;
	}

	void regularElections::save(ofstream& file) const
	{
		int dstrctSize = districts.size();
		file.write(rcastcc(&dstrctSize), sizeof(int));

		if (dstrctSize > 0)
			for (int i = 0; i < dstrctSize; i++)
				districts[i]->save(file);
	
	}

	void regularElections::readDistricts(ifstream& file)
	{
		int dstrctSize;
		file.read(rcastc(&dstrctSize), sizeof(int));

		for (int i = 0; i < dstrctSize; i++)
		{
			district* d = new district(file);
			districts.insert(districts.end(), d);
		}
			
	}
}

