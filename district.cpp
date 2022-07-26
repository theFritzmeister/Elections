#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "district.h"
#include "results.h"
#include "unitedResults.h"

using namespace std;
namespace Elections
{
	district::district(string Name, int Sn, int type, int repNum) : name(Name), Sn(Sn), type(type), repNum(repNum)
	{
		if (Sn < 0 || (type != UNITED && type != SPLITTED) || repNum < 0)
			throw invalid_argument("Wrong input");

		else if (type == UNITED)
			res = new unitedResults();

		else res = new results();
	}

	district::district(const district& dstrct) : name(dstrct.name), Sn(dstrct.Sn), type(dstrct.type), repNum(dstrct.repNum)
	{
		delete res;
		res = dstrct.res;
	}

	district::district(ifstream& file)
	{
		int nameLen;

		file.read(rcastc(&nameLen), sizeof(int));
		name.resize(nameLen);
		file.read((char*)(name.data()), nameLen);
		file.read(rcastc(&Sn), sizeof(int));
		file.read(rcastc(&type), sizeof(int));
		file.read(rcastc(&repNum), sizeof(int)); 

		if (Sn < 0 || (type != UNITED && type != SPLITTED) || repNum < 0)
			throw invalid_argument("Wrong input");
	
		else if (type == UNITED)
			res = new unitedResults();

		else res = new results();
	}

	district::~district()
	{
		delete res;
	}

	ostream& operator<<(ostream& os, const district& dstrct)
	{
		os << "District serial number: " << dstrct.getSn() << ", District name: " << dstrct.getName() <<
			"district type: ";

		if (dstrct.getType() == UNITED)
			os << "UNITED, ";

		else os << "SPLITTED, ";
		os << "Number of representatives in district: " << dstrct.getRepNum() << endl;

		return os;
	}

	void district::operator=(const district& other)
	{
		name = other.name;
		Sn = other.Sn;
		type= other.type; 
		repNum = other.repNum;
		res = other.res; 
		Percentage = other.Percentage;
		citizensDis = other.citizensDis;
	}

	void district::save(ofstream& file)const
	{
		int nameSize = name.length();
		file.write(rcastcc(&nameSize), sizeof(int));
		file.write(rcastcc(name.data()), nameSize);
		file.write(rcastcc(&Sn), sizeof(int));
		file.write(rcastcc(&type), sizeof(int));
		file.write(rcastcc(&repNum), sizeof(int));
	}
}