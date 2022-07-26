#include "Files.h"
#include "Elections.h"
#include "regularElections.h"
#include "simpleElections.h"

namespace Elections
{
	elections* FileManager::load_elections(const string& fileName)
	{
		elections* e = nullptr;
		ifstream file;
		file.open(fileName, ios::binary);

		if (!file)
			throw "ERROR";

		int type, day, month, year;
		file.read(rcastc(&day), sizeof(int));
		file.read(rcastc(&month), sizeof(int));
		file.read(rcastc(&year), sizeof(int));
		file.read(rcastc(&type), sizeof(int));

		if (type == SIMPLE)
		{
			int repsNum;
			file.read(rcastc(&repsNum), sizeof(int));
			e = new simpleElections(day, month, year, repsNum);
		}

		else e = new regularElections(day, month, year);

		if (!file.eof())
			e->readElections(file);

		file.close();

		return e;
	}

	void FileManager::save_elections(elections* e, const string& fileName)
	{
		ofstream file(fileName, ios::binary | ios::trunc);

		if (!file)
			throw "ERROR";
	
		int num;
		e->getDate().save(file);
		int type = static_cast<int>(FileManager::getType(e));
		file.write(rcastcc(&type), sizeof(int));

		if (type == SIMPLE)
		{
			num = e->getDistricts()[0]->getRepNum();
			file.write(rcastcc(&num), sizeof(int));
		}

		else dynamic_cast<regularElections*>(e)->save(file);

		num = e->Citizens().size();

		if (num > 0)
		{
			file.write(rcastcc(&num), sizeof(int));
			for (auto i = e->Citizens().begin(); i != e->Citizens().end(); ++i)
				(*(*i)).save(file);
		}

		int numOfPrtys = e->getPrtyArrSize();
		file.write(rcastcc(&numOfPrtys), sizeof(int));

		if (numOfPrtys > 0)
			for (int i = 0; i < numOfPrtys; i++)
				e->getParties()[i]->save(file);

		int numOfDstrcts = e->getDstrctArrSize();
		file.write(rcastcc(&numOfDstrcts), sizeof(int));

		if (numOfDstrcts > 0)
			for (int i = 0; i < numOfDstrcts; i++)
				e->getDistricts()[i]->getRes()->save(file);

		file.close();
	}

	FileManager::electinosType FileManager::getType(const elections* e)
	{
		if (typeid(*e) == typeid(regularElections))
			return electinosType::NORMAL;

		else return electinosType::SIMPLE;
	}
}