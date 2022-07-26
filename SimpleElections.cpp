#include <iostream>
#include "SimpleElections.h"

namespace Elections
{
	simpleElections::simpleElections(int day, int month, int year, int repsNum) : elections(day, month, year)
	{
		if (repsNum < 0)
			throw invalid_argument("Invalid number of representatives");
	
		district* dis = new district(" ", 0, SPLITTED, repsNum);
		districts.insert(districts.end(), dis);
		const list<citizen*>& list = this->Citizens();
		districts[0]->citizensDis = list;
	}

	void simpleElections::addCitizenToList(const string& newName, int ID, int yearOfBirth, int dstrctNum)
	{
		citizen* c1 = searchByID(ID);

		if (c1 != nullptr)
			throw invalid_argument("Citizen already exists! ");

		c1 = new citizen(newName, ID, yearOfBirth, Date.getYear(), *(districts[0]));

		citizens.push_back(c1); //add citizen to list;
		districts[0]->getRes()->updateCitizensNum();
	}
}
