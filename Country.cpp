#define _CRT_SECURE_NO_WARNINGS
#include "Country.h"


/*������ ����� ���������� ������������ ������ - �� ������ ������� ��������� � �����������*/

Country::Country(string name, int size) {
	MMass = new Republic[size];
	this->Size = size;
	Counter = 0;
	MMass[0].SetNext(0);
}

Country::Country(string name) {
	MMass = new Republic[11];
	SetName(name);
	this->Size = 11;
	Counter = 0;
	MMass[0].SetNext(0);
}

Country::~Country() {
	delete[]MMass;
	MMass = nullptr;
}

void Country::Add(string Name) {
	if (IsFull()) {
		cout << "������ �����" << endl;
		return;
	}
	if (Search(Name))
	{
		cout << "���������� � ����� ��������� ��� ����������" << endl;
		return;
	}
	int Current = MMass[0].GetNext();
	int Prev = 0;
	/*���������� ������ ��������, ����� ������� ����� ��������*/
	while (Current != 0) {
		if (MMass[Current].GetName() > Name) {
			break;
		}
		Current = MMass[Current].GetNext();
		Prev = MMass[Prev].GetNext();
	}

	/*���������� ��������� ������ �������*/
	int j;
	for (j = 1; j < Size; j++) {
		if (MMass[j].GetNext() == -1) break;
	}
	MMass[j].SetNext(Current);
	MMass[Prev].SetNext(j);
	MMass[j].SetName(Name);
	Counter++;
}
void Country::AddSub(string RName, string befName, string Name, int Count, bool isAfter) {
	int Current = MMass[0].GetNext();
	while (Current != 0) {
		if (MMass[Current].GetName() == RName) {
			if (isAfter) {
				MMass[Current].AddAfter(befName, Name, Count);
			}
			else {
				MMass[Current].AddBefore(befName, Name, Count);
			}
		}
		Current = MMass[Current].GetNext();
	}
}
void Country::Delete(string RName) {
	if (IsEmpty()) {
		cout << "������ ����" << endl;
		system("pause");
		return;
	}
	int Current = MMass[0].GetNext();
	int Prev = 0;
	while (Current != 0) {
		if (MMass[Current].GetName() == RName) {
			break;
		}
		Current = MMass[Current].GetNext();
		Prev = MMass[Prev].GetNext();
	}
	MMass[Prev].SetNext(MMass[Current].GetNext());
	MMass[Current].SetNext(-1);
	cout << "���������� " << MMass[Current].GetName() << " ������� �� ������" << endl;
	Counter--;
}
void Country::DeleteSub(string RName, string Name) {
	if (IsEmpty()) {
		cout << "������ ����" << endl;
		system("pause");
		return;
	}
	int Current = MMass[0].GetNext();
	while (Current != 0) {
		if (MMass[Current].GetName() == RName) {
			MMass[Current].Delete(Name);
			return;
		}
		Current = MMass[Current].GetNext();
	}
}

void Country::Show() {
	int Current = MMass[0].GetNext();
	cout << "������ " << GetName() << endl;
	while (Current != 0) {
		MMass[Current].Show();
		Current = MMass[Current].GetNext();
	}
}
bool Country::Search(string RName) {
	int Current = MMass[0].GetNext();
	while (Current != 0 && MMass[Current].GetName() != RName) {
		Current = MMass[Current].GetNext();
	}
	if (Current == 0) return false;
	else return true;
}
void Country::SearchCity(string CityName) {
	int Current = MMass[0].GetNext();
	bool HasTram = false;
	while (Current != 0) {
		if (MMass[Current].Search(CityName)) {
			HasTram = true;
			cout << "������� ���������� � ���������� " << MMass[Current].GetName() << endl;
		}
		Current = MMass[Current].GetNext();
	}
	if (!HasTram) cout << "���������� �� �������" << endl;
}
bool Country::IsEmpty() {
	return Counter == 0;
}
bool Country::IsFull() {
	return Counter == Size-1;
}
bool Country::IsRepEmpty(string Name) {
	int Current = MMass[0].GetNext();
	while (Current != 0) {
		if (MMass[Current].GetName() == Name) {
			if (MMass[Current].IsEmpty()) return true;
			else return false;
		}
		Current = MMass[Current].GetNext();
	}
	return true;
}
bool Country::IsRepFull(string Name) {
	int Current = MMass[0].GetNext();
	while (Current != 0) {
		if (MMass[Current].GetName() == Name) {
			if (MMass[Current].IsFull()) return true;
			else return false;
		}
		Current = MMass[Current].GetNext();
	}
	return false;
}

void Country::DownLoad() {
	TiXmlDocument Doc;
	TiXmlElement* XCurrentCountry = new TiXmlElement("Country");
	char* name = new char[GetName().length() + 1];
	strcpy(name, GetName().c_str());
	XCurrentCountry->SetAttribute("Name", name);
	int Current = MMass[0].GetNext();
	bool HasTram = false;
	TiXmlElement* XCurrentRepublic;
	while (Current != 0) {
		XCurrentRepublic = new TiXmlElement("Republic");
		string name = MMass[Current].GetName();
		char* name_ = new char[name.length() + 1];
		strcpy(name_, name.c_str());
		XCurrentRepublic->SetAttribute("Name", name_);
		int CurrentCity = MMass[Current].GetMass(0)->GetNext();
		while (CurrentCity != 0) {
			TiXmlElement* XCurrentCity = new TiXmlElement("City");
			string name = MMass[Current].GetMass(CurrentCity)->GetName();
			int count = MMass[Current].GetMass(CurrentCity)->GetCount();
			char* name_ = new char[name.length() + 1];
			strcpy(name_, name.c_str());
			XCurrentCity->SetAttribute("Name", name_);
			XCurrentCity->SetAttribute("Count", count);
			XCurrentRepublic->LinkEndChild(XCurrentCity);
			CurrentCity = MMass[Current].GetMass(CurrentCity)->GetNext();
			cout << "������ �����" << endl;
		}
		Current = MMass[Current].GetNext();
		XCurrentCountry->LinkEndChild(XCurrentRepublic);
	}
	Doc.LinkEndChild(XCurrentCountry);
	try {
		Doc.SaveFile("file.xml");
	}
	catch (...) {
		cout << "������ ��� ������ � ����" << endl;
	}
	cout << "��������� ��������." << endl;
}