#pragma once
#include "district.h"
#include "party.h"
#include "Elections.h"
#include "final.h"

namespace Elections
{
	class regularElections : public elections
	{
	private:
		DynamicArray<Final> finalResults; //array of results. any cell is a party

	public:
		regularElections(int day, int month, int year) : elections(day, month, year) {}
		regularElections(const regularElections& e) = delete;
		~regularElections() {}

		//getters;
		const DynamicArray<Final>& getFinalArr() const { return finalResults; }

		//setters;
		bool addDistrict(const string& name, int repsNum, int type);
		virtual void addCitizenToList(const string& newName, int id, int birthYear, int DisNum = 0) override;
		virtual const list<citizen*>& Citizens() const { return citizens; }

		void setWinToDistricts(); //set party win only to uniun districts
		void makeFinalResults(); //Calculats the final results
		void showFinalResult();
		void SortFinalResults();

		//file;
		void save(ofstream& file) const;
		void readDistricts(ifstream& file); //read any district from file
	};
}


