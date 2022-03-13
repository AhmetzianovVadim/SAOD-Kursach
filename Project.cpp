#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <sstream>
#include "Country.h"
#include <Windows.h>

using namespace std;

Country* C = nullptr; 
int GetInt(string Str);
string GetString(string Str);
void AddRepublic();
void AddCity();
void DeleteRepublic();
void DeleteCity();
void SearchRepublic();
void SearchCity();
void DeleteAll();
void DownLoad();
void UpLoad();

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	while (1) {
		system("cls");
		cout << "Выберите действие : \n"
			<< "1 - Новая страна\n"
			<< "2 - Добавить республику\n"
			<< "3 - Добавить город\n"
			<< "4 - Вывод структуры\n"
			<< "5 - Поиск\n"
			<< "6 - Удалить республику\n"
			<< "7 - Удалить город\n"
			<< "8 - Очистить базу данных\n"
			<< "9 - Загрузить структуру из файла\n"
			<< "10 - Выгрузить структуру в файл\n"
			<< "0 - Выход\n"
			<< endl;
		int Act;
		Act = GetInt("");
		system("cls");
		switch (Act)
		{
		case 1:
			system("cls");
			if (C != nullptr) {
				Act = GetInt("Удалить текущую структур?\n1 - да\n2 - нет");
				if (Act == 1) DeleteAll();
				else break;
			}
			C = new Country(GetString("Введите название страны: "));
			cout << "Страна создана." << endl;
			system("pause");
			break;
		case 2: /*Добавить республику*/
			system("cls");
			AddRepublic();
			system("pause");
			break;
		case 3: /*Добавить город*/
			system("cls");
			AddCity();
			system("pause");
			break;
		case 4: /*Вывод*/
			system("cls");
			if (C == nullptr) {
				cerr << "Страна не создана." << endl;
				system("pause");
				break;
			}
			C->Show();
			system("pause");
			break;
		case 5: /*Поиск*/
			system("cls");
			Act = GetInt("Поиск:\n1 - Республики\n2 - Города по названию\n");
			if (Act == 1) {
				SearchRepublic();
			}
			else if (Act == 2) {
				SearchCity();
			}
			system("pause");
			break;
		case 6: /*Удалить республика*/
			DeleteRepublic();
			system("pause");
			break;
		case 7:	/*Удалить город*/
			DeleteCity();
			system("pause");
			break;
		case 8: /*Очистить БД*/
			system("cls");
			DeleteAll();
			system("pause");
			break;
		case 9: /*Работа с файлом*/
			system("cls");
			UpLoad();
			system("pause");
			break;
		case 10:
			system("cls");
			DownLoad();
			system("pause");
			break;
		case 0: /*Выход*/
			system("cls");
			return 0;
			break;
		default:
			break;
		}
	}
}

void AddRepublic() {
	if (C == nullptr) {
		cerr << "Страна не создана." << endl;
		return;
	}
	system("cls");
	string Name = GetString("Введите название республики: ");
	C->Add(Name);
	//cout << "Республика добавлена." << endl;
}
void AddCity() {
	if (C == nullptr) {
		cerr << "Страна не создана." << endl;
		return;
	}
	if (C->IsEmpty()) {
		cerr << "Список республик пуст" << endl;
		return;
	}
	string rep = GetString("Введите название республики, в которую добавить: ");
	if (!C->Search(rep)) {
		cerr << "В списке нет республики с таким названием." << endl;
		return;
	}
	if (C->IsRepFull(rep)) {
		cerr << "Список городов республики заполнен" << endl;
		return;
	}
	if (C->IsRepEmpty(rep)) {
		string Name = GetString("Введите название первого города:");
		int Count = GetInt("Введите численность города: ");
		C->AddSub(rep, "", Name, Count, true);
		return;
	}
	int act = GetInt("Добавить:\n1 - До\n2 - После\n");
	if (act == 1) {
		string befName = GetString("Введите название города, до которого добавить: ");
		string Name = GetString("Введите название города: ");
		int Count = GetInt("Введите численность города: ");
		C->AddSub(rep, befName, Name,Count, false);
	}
	else if (act == 2) {
		string befName = GetString("Введите название города, после которого добавить: ");
		string Name = GetString("Введите название города: ");
		int Count = GetInt("Введите численность города: ");
		C->AddSub(rep, befName, Name, Count, true);
	}
	
}
void DeleteRepublic() {
	if (C == nullptr) {
		cerr << "Страна не создана." << endl;
		return;
	}
	if (C->IsEmpty()) {
		cerr << "Список республик пуст" << endl;
		return;
	}
	string rep = GetString("Введите название республики: ");
	if (!C->Search(rep)) {
		cerr << "В списке нет республики с таким названием." << endl;
		return;
	}
	C->Delete(rep);
}
void DeleteCity() {
	if (C == nullptr) {
		cerr << "Страна не создана." << endl;
		return;
	}
	if (C->IsEmpty()) {
		cerr << "Список республик пуст" << endl;
		return;
	}
	string rep = GetString("Введите название республики, в котором нужно удалить город: ");
	if (!C->Search(rep)) {
		cerr << "В списке нет республики с таким названием." << endl;
		return;
	}
	if (C->IsRepEmpty(rep)) {
		cerr << "Список городов республики пуст." << endl;
		return;
	}
	string Name = GetString("Введите название города: ");
	C->DeleteSub(rep, Name);
}
void SearchRepublic() {
	if (C == nullptr) {
		cerr << "Страна не создана." << endl;
		return;
	}
	if (C->IsEmpty()) {
		cerr << "Список республик пуст" << endl;
		return;
	}
	string rep = GetString("Введите название республики для поиска: ");
	if (!C->Search(rep)) {
		cerr << "Совпадений не найдено." << endl;
		return;
	}
	else {
		cout << "Республика " << rep << " найдена." << endl;
	}
}
void SearchCity() {
	if (C == nullptr) {
		cerr << "Страна не создана." << endl;
		return;
	}
	if (C->IsEmpty()) {
		cerr << "Список республик пуст" << endl;
		return;
	}
	string Name = GetString("Введите название города: ");
	C->SearchCity(Name);
}
void DeleteAll() {
	delete C;
	C = nullptr;
	cout << "Структура удалена." << endl;
}
void DownLoad() {
	if (C == nullptr) {
		cout << "Страна не создана" << endl;
		return;
	}
	C->DownLoad();
}

void UpLoad() {
		string dir = GetString("Введите путь к xml файлу(d - использовать путь по умолчанию):");
		if (dir == "d") {
			dir = "file.xml";
		}
		TiXmlDocument Doc(dir.c_str());
		if (Doc.LoadFile())
		{
			cout << "Файл успешно открыт." << endl;
		}
		else {
			cout << "Ошибка при открытии файла." << endl;
			return;
		}
		TiXmlHandle hDoc(&Doc);
		TiXmlHandle hRoot(0);
		TiXmlElement* Root = Doc.FirstChildElement("Country");
		hRoot = TiXmlHandle(Root);
		Country* newC = new Country(Root->Attribute("Name"));
		for (TiXmlElement* RepublicElement = hRoot.FirstChildElement("Republic").Element();
			RepublicElement != nullptr;
			RepublicElement = RepublicElement->NextSiblingElement("Republic"))
		{
			string RepublicName, CityName;
			int CityCount;
			if (!RepublicElement->Attribute("Name")) {
				cerr << "Ошибка чтения названия республики.\nНеверно заданы атрибуты." << endl;
				DeleteAll();
				return;
			}
			try {
				RepublicName = RepublicElement->Attribute("Name");
			}
			catch (...) {
				cerr << "Ошибка чтения названия республики.\nНеверно заданы атрибуты." << endl;
				DeleteAll();
				return;
			}
			newC->Add(RepublicName);
			TiXmlElement* XCityElement = RepublicElement->FirstChildElement("City");

			while (XCityElement != nullptr) {
				if (!XCityElement->Attribute("Name") || !XCityElement->Attribute("Count")) {
					cerr << "Ошибка чтения названия и численности города.\nНеверно заданы атрибуты." << endl;
					DeleteAll();
					return;
				}
				try {
					CityName = XCityElement->Attribute("Name");
					string count = XCityElement->Attribute("Count");
					CityCount = atoi(count.c_str());
				}
				catch (...) {
					cerr << "Ошибка чтения названия и численности города.\nНеверно заданы атрибуты." << endl;
					DeleteAll();
					return;
				}
				newC->AddSub(RepublicName, "", CityName, CityCount, true);
				XCityElement = XCityElement->NextSiblingElement("City");
			}
		}
		C = newC;
		cout << "Структура успешно загружена." << endl;
	}


string GetString(string Str) {
	string String;
	while (1) {
		cout << Str << endl;
		getline(cin, String);
		bool BReject = false;
		for (unsigned int i = 0; i < String.length() && !BReject; i++) {
			if (IsCharAlphaNumericA(String[i])) { continue; }
			if (String[i] == ':') { continue; }
			if (String[i] == '\\') { continue; }
			if (String[i] == '-') { continue; }
			if (isspace(String[i])) { continue; }
			if (String[i] == ',' || String[i] == '.') continue;
			BReject = true;
		}
		if (String[0] == NULL) { BReject = true; }
		if (!BReject) break;
		cout << "Ошибка ввода." << endl;
	}
	return String;
}

int GetInt(string Str) {
	string String;
	int Val;
	while (1) {
		cout << Str << endl;
		getline(cin, String);
		if (String == "" || String == " ") continue;
		bool BReject = false;
		for (unsigned int i = 0; i < String.length() && !BReject; i++) {
			if (isdigit(String[i])) continue;
			BReject = true;
		}
		if (!BReject) break;
		cout << "Ошибка ввода." << endl;
	}
	std::stringstream StrStream;
	StrStream << String;
	StrStream >> Val;
	return Val;
}