#pragma once
#include <iostream>

using namespace std;

namespace Elections
{
	const char* menu[] = 
	{ "Add district", "Add citizen", "Add party", "Add candidate", 
		"Display districts", "Display citizens", "Display parties", 
		"Vote", "Display results", "EXIT", "Save elections", "Load elections" };

	const char* firstMenu[] = { "Create a new elections round", "Load an existing elections round", "EXIT" };

	class Menu
	{
	public:
		enum eMenu {
			addDistrict = 1, addCitizen, addParty, addLeader, displayDistricts,
			displayCitizens, displayParties, Vote, displayResults, Exit, Save, Load};

		enum eFirstMenu {New = 1, load, EXIT};

	public:
		static void showMenu();
		static void showFirstMenu();
	};

	void Menu::showMenu()
	{
		system("CLS");

		cout << "Choose an option:" << endl;
		cout << eMenu::addDistrict << ". " << menu[eMenu::addDistrict - 1] << endl
			<< eMenu::addCitizen << ". " << menu[eMenu::addCitizen - 1] << endl
			<< eMenu::addParty << ". " << menu[eMenu::addParty - 1] << endl
			<< eMenu::addLeader << ". " << menu[eMenu::addLeader - 1] << endl
			<< eMenu::displayDistricts << ". " << menu[eMenu::displayDistricts - 1] << endl
			<< eMenu::displayCitizens << ". " << menu[eMenu::displayCitizens - 1] << endl
			<< eMenu::displayParties << ". " << menu[eMenu::displayParties - 1] << endl
			<< eMenu::Vote << ". " << menu[eMenu::Vote - 1] << endl
			<< eMenu::displayResults << ". " << menu[eMenu::displayResults - 1] << endl
			<< eMenu::Exit << ". " << menu[eMenu::Exit - 1] << endl
			<< eMenu::Save << ". " << menu[eMenu::Save - 1] << endl
			<< eMenu::Load << ". " << menu[eMenu::Load - 1] << endl;
	}

	void Menu::showFirstMenu()
	{
		cout << "Please choose one of the following:" << endl;
		cout << eFirstMenu::New << ". " << firstMenu[eFirstMenu::New - 1] << endl
			<< eFirstMenu::load << ". " << firstMenu[eFirstMenu::load - 1] << endl
			<< eFirstMenu::EXIT << ". " << firstMenu[eFirstMenu::EXIT - 1] << endl;
	}
}

