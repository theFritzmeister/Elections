#pragma once
#include <iostream>
#include "citizen.h"

using namespace std;

using namespace Elections;

class add
{
public:
	void operator()(int& s) { s++; }
};

template <class T, class F>
void addOne(T t, F f)
{
	f(t);
}

inline void printList(const list<citizen*>& lst)
{
	if (lst.empty())
		throw out_of_range("There are no citizens!");

	for (auto i = lst.begin(); i != lst.end(); ++i)
		cout << *(*i) << endl;
}

template <class T>
void Swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}





