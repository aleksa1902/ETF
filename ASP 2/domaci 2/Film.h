#include<iostream>
#include<string>

#pragma once
using namespace std;
class Film
{
private:
	string lang;
	string name;
	//string date;
	int day;
	int month;
	int year;
	int revenue;
	int runtime;
	bool prisutan;
public:
	Film(string lan, string nam, int d, int m, int y, int rev, int run) {//
		lang = lan;
		day = d;
		month = m;
		year = y;
		//date = dat;
		name = nam;
		revenue = rev;
		runtime = run;
		prisutan = true;
	}

	void ispisFilma() {
		if (prisutan) cout << "Film: " << day << "/" << month << "/" << year << " Naziv: " << name << " zarada " << revenue << " trajanje " << runtime << " , " << endl;
	}

	int getDay() const { return day; }
	int getMonth() const { return month; }
	int getYear() const { return year; }
	string getLang() const { return lang; }
	string getName() const { return name; }
	int getRevenue() const { return revenue; }
	int getRuntime() const { return runtime; }

	void setDay(int d) { this->day = d; }
	void setMonth(int m) { this->month = m; }
	void setYear(int y) { this->year = y; }
	void setLang(string la) { this->lang = la; }
	void setName(string na) { this->name = na; }
	void setRevenue(int rev) { this->revenue = rev; }
	void setRuntime(int run) { this->runtime = run; }

	bool brisanje() {
		if (this->prisutan) this->prisutan = false;
		return true;
	}

	~Film() {

	}
};

