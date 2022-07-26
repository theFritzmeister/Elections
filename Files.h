#pragma once
#include <fstream>

using namespace std;

namespace Elections
{
	class elections;

	class FileManager
	{
	public:
		enum electinosType { NORMAL = 1, SIMPLE };
		static elections* load_elections(const string& fileName);
		static void save_elections(elections* e, const string& fileName);
		static electinosType getType(const elections* e);
	};
}

