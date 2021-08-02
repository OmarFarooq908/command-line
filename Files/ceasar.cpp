#include "ceasar.h"
#include <iostream>
#include <cstring>
using namespace std;

void ceaser_cipher_encryption() {
	string a;
	int d, e, f, g;

	cout << " _______________________________________________________________" << endl;
	cout << "|                                                               |" << endl;
	cout << "| In the Name of Allah, the Most Gracious and the Most Merciful |" << endl;
	cout << "|_______________________________________________________________|" << endl;
	cout << "\n _______________________________________________________________" << endl;
	cout << "|                                                               |" << endl;
	cout << "|                Name    : Muhammad Omar Farooq                 |" << endl;
	cout << "|                Roll No :       20-CP-33                       |" << endl;
	cout << "|_______________________________________________________________|" << endl;
	cout << "\n________________________________________________________________" << endl;
	cout << "|                                                               |" << endl;
	cout << "|               Department of Computer Engineering              |" << endl;
	cout << "|          University of Engineering and Technology, Taxila     |" << endl;
	cout << "|_______________________________________________________________|" << endl;
	while (true) {
		cout << "\n >> Message >> ";
		cin.ignore();
		getline(cin, a);
		cout << ">> Shift >> ";
		cin >> d;
		f = a.length();
		g = f - 1;
		cout << ">> The message after the shift is >> ";
		for (int i = 0; i <= g; i++) {

			e = int(a[i]) + d;
			if (e > 90 && e < 97) {
				e = e - 26;
			}
			if (e > 122) {
				e = e - 26;
			}
			if (e == 35) {
				e -= 3;
			}
			cout << char(e);
		}
		cout << "\n";
		cout << ">> Do you want to use the app again? (Y/N) >> ";
		char choice;
		cin >> choice;
		if (choice == 'N' || choice == 'n') {
			break;
		}
	}
}

