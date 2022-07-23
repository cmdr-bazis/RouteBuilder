#pragma once
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

class service
{
public:
	void check_double(double& doubleVar) {
		while (!(cin >> doubleVar) or cin.get() != '\n') {
			cin.clear();
			cin.ignore(9999, '\n');
			cout << " try again: ";
		}
	}
	void check_string(string& stringVar) {
		while (!(cin >> stringVar) or cin.get() != '\n') {
			cin.clear();
			cin.ignore(9999, '\n');
			cout << " try again: ";
		}
	}
	void check_char(char& charVar) {
		while (!(cin >> charVar) or cin.get() != '\n') {
			cin.clear();
			cin.ignore(9999, '\n');
			cout << " try again: ";
		}
	}
	void check_int(int& intVar) {
		while (!(cin >> intVar) or cin.get() != '\n') {
			cin.clear();
			cin.ignore(9999, '\n');
			cout << " try again: ";
		}
	}
	void check_float(float& floatVar) {
		while (!(cin >> floatVar) or cin.get() != '\n') {
			cin.clear();
			cin.ignore(9999, '\n');
			cout << " try again: ";
		}
	}
	void check_bool(bool& boolVar) {
		while (!(cin >> boolVar) or cin.get() != '\n') {
			cin.clear();
			cin.ignore(9999, '\n');
			cout << " try again: ";
		}
	}
	bool continuation() {
		cout << endl;
		char a;
		cout << " Continue executing current program? (y/n): ";
		check_char(a);
		while ((a != 'n') or (a != 'y')) {
			if (a == 'n') {
				return 0;
			}
			else if (a == 'y') {
				cout << endl;
				return 1;
			}
			else {
				cout << " Please choose only 'y' or 'n': ";
				check_char(a);
			}
		}
	}
	int GetRandomNumber() {
		int num = 1 + rand() % 9;
		return num;
	}
};

