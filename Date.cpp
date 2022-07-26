#include <fstream>
#include "Date.h"
#include "Elections.h"

namespace Elections
{
	date::date(int day, int month, int year) : day(day), month(month), year(year)
	{
		if (month < 1 || month > 12 || day < 1 || day > 32)
			throw invalid_argument("Wrong input!");
	}

	void date::save(ofstream& file) const
	{
		file.write(rcastcc(&(this->day)), sizeof(int));
		file.write(rcastcc(&(this->month)), sizeof(int));
		file.write(rcastcc(&(this->year)), sizeof(int));
	}

	ostream& operator<<(ostream& os, const date& date)
	{
		os << date.day << "." << date.month << "." << date.year << " "; return os;
	}
}