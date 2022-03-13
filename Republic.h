#pragma once
#include "City.h"

class Republic
{
private:
	string Name;
	City* Mass;
	int Size;
	int Counter;
	int Next;
public:
	Republic();
	Republic(string name, int maxSize);
	~Republic();
	void SetNext(int next);
	void SetName(string Name);
	void AddBefore(string beforeRep, string newRep, int Count);
	void AddAfter(string afterRep, string newRep, int Count);
	void Delete(string name);
	void Show();
	

	bool Search(string name);
	bool IsEmpty();
	bool IsFull();

	string GetName() { return Name; }
	City* GetMass(int i) { return &Mass[i]; }
	int GetMaxSize() { return Size; }
	int GetCounter() { return Counter; }
	int GetNext() { return Next; }
};
