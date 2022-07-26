#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "regularElections.h"
#include "simpleElections.h"
#include "menu.h"

using namespace std;
using namespace Elections;

const int MAX_SIZE = 150;

void addDistrictMenu(elections* e)
{
	string name;
	int type, Repnum;
	cout << "Enter name of district:" << endl;

	cin.ignore();
	cin >> name;
	cout << "Enter type of district (1 for united, 2 for splitted), and number of representatives:" << endl;
	cin >> type >> Repnum;

	dynamic_cast<regularElections*>(e)->addDistrict(name, Repnum, type);
	cout << "District added successfully!" << endl;
}

void addCitizenMenu(elections* e)
{
	char name[MAX_SIZE];
	int id, year, district = 0;
	cout << "Enter name:" << endl;
	cin.ignore();
	cin.getline(name, MAX_SIZE);
	cout << "Enter ID, year of birth and district number:" << endl;
	cin >> id >> year >> district;

	if (typeid(*e) == typeid(regularElections))
		e->addCitizenToList(name, id, year, district);

	else e->addCitizenToList(name, id, year);

	cout << "Citizen added successfully!" << endl;
}

void addPartyMenu(elections* e)
{
	char name[MAX_SIZE];
	int id;
	cout << "Enter the party name:" << endl;
	cin.ignore();
	cin.getline(name, MAX_SIZE);
	cout << "Enter the prime minister candidate ID:" << endl;
	cin >> id;
	citizen* prime = e->searchByID(id);

	e->addParty(name, prime);

	cout << "Party added successfully!" << endl;
}

void addRepMenu(elections* e)
{
	int id, districtNum, partyNum;
	cout << "Enter representative's ID, number of party, and number of district:" << endl;
	cin >> id >> partyNum >> districtNum;;

	if (typeid(*e) == typeid(simpleElections))
		districtNum = 0;

	if (e->getDstrctArrSize() < districtNum + 1 || districtNum < 0)
		throw invalid_argument("No such district!");

	if (e->getPrtyArrSize() < partyNum + 1 || partyNum < 0)
		throw invalid_argument("No such party!");

	if (e->getParties()[partyNum]->repsFull(districtNum))
		throw out_of_range("Representatives list is full!");

	e->addRep(id, partyNum, districtNum);
	cout << "Representative added successfully!" << endl;
}

void voteMenu(elections* e)
{
	int id, partyNum;

	cout << "Enter your ID, and the number of party you vote for:" << endl;
	cin >> id >> partyNum;

	citizen* voter = e->searchByID(id);
	if (voter == nullptr)
		throw invalid_argument("There is no such citizen!");

	if (voter->Voted())
		throw invalid_argument("You already voted!");

	if (partyNum >= e->getPrtyArrSize() || partyNum < 0)
		throw invalid_argument("There is no such party");

	e->vote(*voter, partyNum);
	cout << "You have voted successfully!" << endl;
}


void resultsMenu(elections* e)
{
	regularElections* reg = dynamic_cast<regularElections*>(e);
	e->preResults();

	if (typeid(*e) == typeid(regularElections))
		reg->makeFinalResults();


	e->showResults(); //results by district
	if (typeid(*e) == typeid(regularElections))
		reg->showFinalResult();
}

elections* loadMenu()
{
	string name;
	cout << "Enter file's name:" << endl;
	cin >> name;
	elections* e = FileManager::load_elections(name);

	if (e != nullptr)
		cout << "Loaded successfully!" << endl;

	return e;
}

void saveMenu(elections* e)
{
	string name;
	cout << "Save as:" << endl;
	cin >> name;
	FileManager::save_elections(e, name);
	cout << "Saved successfully!" << endl;
}

void chooseFromMenu(int op, elections** e)
{
	switch (op)
	{
	case(1):
		if (typeid(**e) == typeid(simpleElections))
			throw invalid_argument("Can't add district in simple elections!");

		else addDistrictMenu(*e);

		break;
	case(2):
		addCitizenMenu(*e);
		break;

	case(3):
		addPartyMenu(*e);
		break;

	case(4):
		addRepMenu(*e);
		break;

	case(5):
		(*e)->printDistricts();
		break;

	case(6):
		printList((*e)->Citizens());
		break;

	case(7):
		(*e)->printParties();
		break;

	case(8):
		voteMenu(*e);
		break;

	case(9):
		resultsMenu(*e);
		break;

	case(10):
		break;

	case(11):
		saveMenu(*e);
		break;

	case(12):
		delete* e;
		*e = loadMenu();
		break;

	default:
		throw invalid_argument("Wrong input!");
		break;
	}

	system("pause");
	system("CLS");
}

elections* doElections(int type)
{
	elections* e;
	int day, month, year, repsNum;

	if (type != 1 && type != 2)
		throw invalid_argument("Wrong input!");

	system("CLS");

	cout << "Enter elections date: " << endl;

	cin >> day >> month >> year;

	if (type == 1)
	{
		cout << "Enter number of representatives:" << endl;
		cin >> repsNum;
		e = new simpleElections(day, month, year, repsNum);
	}

	else e = new regularElections(day, month, year);

	return e;
}

void chooseFromFirstMenu(int op, elections** e)
{
	bool flag = false;

	if (op < 1 || op > 3)
		throw invalid_argument("Wrong input!");

	if (op == 1)
	{
		system("CLS");
		int type;
		cout << "Enter 1 for simple elections and 2 for regular elections:" << endl;
		cin >> type;

		while (!flag)
		{
			flag = true;

			try 
			{
				*e = doElections(type);
			}

			catch (std::exception & ex)
			{
				cout << ex.what() << endl <<"Something went wrong" << endl;
				flag = false;
			}

			catch (const char* tryAgain)
			{
				cout << tryAgain << endl;
				cin >> type;
				flag = false;
			}
		}
	}

	else if (op == 2)
	{
		try 
		{
			*e = loadMenu();
		}

		catch (const char* fileErrorMsg) 
		{
			cout << fileErrorMsg << endl;
			exit(1);
		}
	}

	else if (op == 3)
		exit(1);
}

int main()
{
	bool flag = false;
	int op = 0;
	elections* e = nullptr;
	Menu::showFirstMenu();

	while (!flag)
	{
		flag = true;
		try 
		{
			cin >> op;
			chooseFromFirstMenu(op, &e);
		}

		catch (std::exception & ex)
		{
			cout << ex.what() << endl;
			flag = false;
		}
	}

	cout << "Elections: " << e->getDate() << endl;

	while (op != 10)
	{
		Menu::showMenu();
		cin >> op;
		system("CLS");

		try
		{
			chooseFromMenu(op, &e);
		}

		catch (std::exception& ex)
		{
			cout << "Error: " << ex.what() << endl;
			system("pause");
			system("CLS");
		}

		catch (bad_alloc& ex) 
		{
			cout << ex.what() << endl;
			exit(1);
		}

		catch (const char* fileErrorMsg) 
		{
			cout << fileErrorMsg << endl;
			exit(1);
		}
	}

	system("pause");

	delete e;
}