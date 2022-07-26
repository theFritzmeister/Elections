#pragma once
#include <iostream>

using namespace std;

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

namespace Elections
{
	class district;

	class citizen
	{

		string name;
		int ID;
		int yearOfBirth;
		district& dstrct;
		bool isArep;
		bool hasVoted;

	public:
		citizen(const string& name2, int id, int yearOfBirth, int yearOfElections, const district& dstrct);
		citizen(const citizen& ctzn);
		~citizen() {}
		
		//getters
		const string& getName() const { return name; }
		int getID() const { return ID; }
		int getDistrictNum() const;
		bool citizenIsRep()const { return isArep; }
		bool Voted()const { return hasVoted; }
		const district& getDis() { return dstrct; }

		//setters
		void setVote() { hasVoted = true; }
		void setRep() { isArep = true; }

		void operator=(const citizen& other);
		friend ostream& operator<<(ostream& os, const citizen& ctzn);

		//file
		void save(ofstream& file) const;
	};
}

