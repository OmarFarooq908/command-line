#include "ceasar.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>

using namespace std;

void base_n_base10() {
	bool continue_command = true;
	while (continue_command) {
		string raw_num;

		char e[] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
		int b;
		int c;
		int f;
		int k = 0;
		int l = 0;
		int m;
		int n;

		cout << ">> Enter a number: ";
		cin >> raw_num;
		for (int i = 0; i < raw_num.length(); i++) {
			if (int(raw_num[i]) >= 97 && int(raw_num[i]) <= 122) {
				raw_num[i] = char(int(raw_num[i]) - 32);
			}
		}
		if (raw_num == "SYSTEM-C") {
			continue_command = false;
		}
		cout << ">> Enter the base of the number entered: ";
		cin >> n;

		b = raw_num.length();
		c = b - 1;
		vector <int> d(b);

		for (int i = 0; i <= c; i++) {
			for (int j = 0; j < strlen(e); j++) {
				if (raw_num[i] == e[j]) {
					d[i] = int(raw_num[i] - 55);
					k = 1;
					break;
				}
			}
			if (k == 0) {
				d[i] = raw_num[i] - 48;
			}
		}
		m = c;
		for (int i = 0; i <= c; i++) {
			l = l + d[i] * pow(n, m);
			m--;
		}
		cout << ">> " << raw_num << " in base 10 : " << l << endl;
		cout << ">> Do you want to use the app again? (Y/N) >> ";
		char choice;
		cin >> choice;
		if (choice == 'n' || choice == 'N') {
			break;
		}
	}
}

