#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "citizen.h"
#include "district.h"

namespace Elections
{
	citizen::citizen(const string& newName, int id, int yearOfBirth, int yearOfElections, const district& dstrct) : name(newName), ID(id), yearOfBirth(yearOfBirth),
		dstrct(const_cast<district&>(dstrct)), hasVoted(false), isArep(false)
	{
		if ((yearOfElections - yearOfBirth < 18))
			throw  invalid_argument("Citizen is a minor!");

		if ((id / 100000000) == 0 || (id / 100000000) > 9)
			throw  invalid_argument("Citizens ID must have 9 digits!");
	}

	citizen::citizen(const citizen& ctzn) : name(ctzn.name), ID(ctzn.ID), yearOfBirth(ctzn.yearOfBirth),
		dstrct(const_cast<district&>(dstrct)), hasVoted(ctzn.hasVoted) {}

	int citizen::getDistrictNum() const
	{
		return (dstrct.getSn());
	}

	ostream& operator<<(ostream& os, const citizen& ctzn)
	{
		os << ctzn.getName() << ", ID: " << ctzn.ID << ", year of birth: " << ctzn.yearOfBirth << ", district number: "
			<< ctzn.getDistrictNum();
		return os;
	}

	void citizen::operator=(const citizen& other)
	{
		ID = other.ID;
		name = other.name;
		yearOfBirth = other.yearOfBirth;
		dstrct = other.dstrct;
		isArep = other.isArep;
		hasVoted = other.hasVoted;
	}

	void citizen::save(ofstream& file) const
	{
		int nameSize = name.length();
		file.write(rcastcc(&nameSize), sizeof(int));
		file.write(rcastcc(name.data()), nameSize);	
		file.write(rcastcc(&yearOfBirth), sizeof(int));
		file.write(rcastcc(&ID), sizeof(int));

		int districtNum = dstrct.getSn();
		file.write(rcastcc(&districtNum), sizeof(int));

		int isVote = static_cast<int>(hasVoted);
		int is_Rep = static_cast<int>(isArep);
		file.write(rcastcc(&isVote), sizeof(int));
		file.write(rcastcc(&is_Rep), sizeof(int));
	}
}