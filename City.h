#pragma once
#include <string>
#include <iostream>
using namespace std;

class City
{
private:
	int Count;
	string Name;
	int Next;
public:
	City(int Count, string Name);
	City();	
	~City();	
	void SetCount(int Year); 
	void SetName(string Name);
	void SetNext(int next);

	int GetNext() { return Next; }
	int GetCount() { return Count; }
	string GetName() { return Name; }	
};
