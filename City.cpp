#include "City.h"

City::City(int Year, string Name) {
	SetName(Name);
	SetCount(Year);
	Next = -1;
}
City::City() {
	SetName("");
	SetCount(0);
	Next = -1;
}
City::~City() {}

void City::SetName(string Name) {
	this->Name = Name;
}
void City::SetCount(int Year) {
	this->Count = Year;
}
void City::SetNext(int next) {
	this->Next = next;
}