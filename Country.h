#pragma once
#include "Republic.h"
#include <string>
#include <fstream>
#include "tinystr.h"
#include "tinyxml.h"

using namespace std;

class Country
{
private:
	Republic* MMass;
	int Size;
	int Counter;
	string name;
public:

	string GetName() { return name; }
	int GetSize() { return Size; }

	void SetName(string n) {
		name = n;
	}

	Country(string name, int size);
	Country(string name);
	~Country();
	void Add(string Name);
	void AddSub(string RName, string befName, string Name, int Count, bool isAfter);
	void Delete(string RName);
	void DeleteSub(string RName, string Name);
	void Show();
	bool Search(string RName);
	void SearchCity(string CityName);
	bool IsEmpty();
	bool IsFull();
	bool IsRepEmpty(string Name);
	bool IsRepFull(string Name);
	void DownLoad();
};
