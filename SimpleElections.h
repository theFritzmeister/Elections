#pragma once
#include "district.h"
#include "party.h"
#include "final.h"

namespace Elections
{
	class simpleElections : public elections
	{
	public:
		simpleElections(int day, int month, int year, int repsNum);
		simpleElections(const simpleElections& e) = delete;
		~simpleElections() {}

		virtual void addCitizenToList(const string& newName, int ID, int yearOfBirth, int dstrctSn = 0) override;
		virtual const list<citizen*>& Citizens() const { return citizens; }
	};
}

