#include "Republic.h"
#include <iostream>

/*Неупорядоченный статический список
второй вариант*/

const int SIZE = 11;

Republic::Republic() {
	Mass = new City[SIZE];
	Next = -1;
	Counter = 0;
	this->Name = "";
	this->Size = SIZE;
	Mass[0].SetNext(0);
}
Republic::Republic(string Name, int Size) {
	Mass = new City[Size];
	Next = -1;
	Counter = 0;
	this->Name = Name;
	this->Size = Size;
	Mass[0].SetNext(0);
}
Republic::~Republic(){
	delete[]Mass;
	Mass = nullptr;
}

void Republic::SetNext(int next) {
	Next = next;
}
void Republic::SetName(string Name) {
	this->Name = Name;
}

void Republic::AddBefore(string beforeCity, string newCity, int Count) {
	if (IsFull()) {
		cout << "Список полон." << endl;
		system("pause");
		return;
	}
	if (Search(newCity))
	{
		cout << "Город с таким названием уже существует" << endl;
		return;
	}
	if (!Search(beforeCity))
	{
		cout << "Города перед которым необходимо добавить не существует" << endl;
		return;
	}
	int Prev = 0;
	int Current = Mass[0].GetNext();
	while (Current != 0) {
		if (Mass[Current].GetName() == beforeCity) { break; }
		Current = Mass[Current].GetNext();
		Prev = Mass[Prev].GetNext();
	}
	int j;
	for (j = 1; j < Size; j++) {
		if (Mass[j].GetNext() == -1) break;
	}
	Mass[j].SetNext(Current);
	Mass[j].SetName(newCity);
	Mass[j].SetCount(Count);
	Mass[Prev].SetNext(j);
	Counter++;
}
void Republic::AddAfter(string afterCity, string newCity, int Count) {
	if (IsFull()) {
		cout << "Список полон." << endl;
		system("pause");
		return;
	}
	if (Search(newCity))
	{
		cout << "Город с таким названием уже существует" << endl;
		return;
	}
	if (this->Counter > 0 && !Search(afterCity) && afterCity != "")
	{
		cout << "Города после которого необходимо добавить не существует" << endl;
		return;
	}
	int Prev = 0;
	int Current = Mass[0].GetNext();
	int k = 0;
	while (Current != -1) {
		if (Mass[Current].GetName() == afterCity) { break; }
		Current = Mass[Current].GetNext();
		Prev = Mass[Prev].GetNext();
	}
	int j;
	for (j = 1; j < Size; j++) {
		if (Mass[j].GetNext() == -1) break;
	}
	Mass[j].SetNext(Mass[Current].GetNext());
	Mass[j].SetName(newCity);
	Mass[j].SetCount(Count);
	Mass[Current].SetNext(j);
	Counter++;
}

void Republic::Delete(string name) {
	if (Counter == 0) {
		cout << "Список пуст." << endl;
		system("pause");
		return;
	}
	int Prev = 0;
	int Current = Mass[0].GetNext();
	while (Current) {
		if (Mass[Current].GetName() == name) {
			Mass[Prev].SetNext(Mass[Current].GetNext());
			Mass[Current].SetNext(-1);
			cout << "Город " << Mass[Current].GetName() << " удален." << endl;
			Counter--;
			return;
		}
		Prev = Mass[Prev].GetNext();
		Current = Mass[Current].GetNext();
	}
	cout << "Город " << name << " не найден в списке." << endl;
}

void Republic::Show() {
	cout << "Республика - " << Name << ". Свободно мест -  " << Size - Counter - 1 << "." << std::endl;
	int Current = Mass[0].GetNext();
	while (Current) {
		cout << Mass[Current].GetName() << " - " << Mass[Current].GetCount() << "чел" << endl;
		Current = Mass[Current].GetNext();
	}
	cout << endl;
}
bool Republic::Search(string name) {
	if (Mass != nullptr)
	{
		int Current = Mass[0].GetNext();
		while (Current) {
			if (Mass[Current].GetName() == name) {
				return true;
			}
			Current = Mass[Current].GetNext();
		}
	}
	return false;
}
bool Republic::IsEmpty() {
	return Counter == 0;
}
bool Republic::IsFull() {
	return Counter == Size-1;
}