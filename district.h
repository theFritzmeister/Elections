#pragma once
#include <list>
#include <fstream>

#include "citizen.h"
#include "results.h"

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>
#define UNITED 1
#define SPLITTED 2

namespace Elections
{
	class district
	{
		string name;
		int Sn;		//serial number;
		int type;	 //united or splitted;
		int repNum;		//number of representatives;
		int Percentage = 0;		//voting percentage;
		results* res;	//district's results;

	public:
		list<citizen*> citizensDis;		//list of the citizens that are allowed to vote;
		district(string Name, int Sn, int type, int repNum);
		district(const district& dstrct);
		district(ifstream& file);
		~district();
		
		//getters;
		const string& getName() const { return name; }
		const int getSn() const { return Sn; }
		const int getType() const { return type; }
		const int getRepNum() const { return repNum; }
		results* getRes() { return res; }
		results* getRes() const { return res; }

		//setters;
		void setPercentage() { Percentage = res->getPercentage(); }

		friend ostream& operator<<(ostream& os, const district& dstrct);
		void operator=(const district& other);

		//file;
		void save(ofstream& file)const;
	};
}


