/***********************************************************************
// OOP244 Workshop 3: Member functions and privacy
// File ReportUtils.h

	�� Name: Youjin An
	�� Part: DIY
	�� Date: 2019/09/28

***********************************************************************/

#include <iostream>
using namespace std;

#include "ReportUtils.h"

namespace sdds {

	// reads an integer from console the integer referenced by "val"
   // argument.
   // if the user enters an invalid integer or values outside of the 
   // boundries set by "min" or "max" , this function flushes the 
   //keyboard, prints the "errorMessage and reads again
   // untill user enters an acceptable integer
	void read(int& val, int min, int max, const char* ErrorMess) {
		bool ok;
		char newline;
		do {
			cin >> val;
			newline = cin.get();
			if (cin.fail() || newline != '\n') {
				ok = false;
				cin.clear();
				cin.ignore(1000, '\n');
			}
			else {
				ok = val <= max && val >= min;
			}
		} while (!ok && cout << ErrorMess);
	}

	// reads a C style string from console up to "len" characters into the
	// the string pointed by the "str" pointer
	// if the user enters more than "len" characters, this function
	// flushes the keyboard, prints the "errorMessage and reads again
	// untill user enters an acceptable string
	void read(char* str, int len, const char* errorMessage) {
		bool ok;
		do {
			ok = true;
			cin.getline(str, len + 1, '\n');
			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				ok = false;
			}
		} while (!ok && cout << errorMessage);
	}

	ostream& line(int len, char ch) {
		for (int i = 0; i < len; i++, cout << ch);
		return cout;
	}

	ostream& number(int num) {
		cout << num;
		for (int i = 0; i < 9; i++) {
			cout << " - " << num;
		}
		return cout;
	}
}

