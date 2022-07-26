#pragma once
#include <iostream>
#include <list>
#include <typeinfo>
#include <string>

#include "DynamicArray.h"
#include "district.h"
#include "party.h"
#include "Files.h"
#include "Date.h"

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

using namespace std;

namespace Elections
{
	class elections
	{
	protected:
		date Date;
		DynamicArray<district*> districts;
		DynamicArray<party*> parties;
		list<citizen*> citizens;
		
	public:
		elections(int day, int month, int year) : Date(day, month, year) {}
		elections(const elections& e) = delete;
		virtual ~elections() {}

		//getters;
		int getDstrctArrSize() const { return districts.size(); }
		int getPrtyArrSize() const { return parties.size(); }
		const DynamicArray<district*>& getDistricts() const { return districts; }
		const DynamicArray<party*>& getParties() const { return parties; }
		virtual const list<citizen*>& Citizens() { return citizens; }
		const date& getDate() const { return Date; }

		void addParty(const string& name, citizen* leader);
		void addRep(int ID, int partyNum, int dstrctSn = 0);
		virtual void addCitizenToList(const string& newName, int id, int birthYear, int DisNum = 0) = 0; //abstract
		citizen* searchByID(int ID);

		void printParties();
		void printDistricts();

		bool vote(citizen&, int partySn);

		void preResults(); //Calculats the results to any district
		void setPre(); //set percentages to any party in all the districts
		void setRepsToParties();
		void showResults(); //districts results

		//file;
		void readCitizen(ifstream& file);
		void readparty(ifstream& file);
		void readElections(ifstream& file);
	};
}



