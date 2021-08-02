#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include "ceasar.h"

using namespace std;

int time_check(string current_time, int choice) {
	int current_hours, current_minutes, future_hours, future_minutes, marid;
	if ((current_time.length() == 8) && (current_time[0] == '1' || current_time[0] == '0') &&
		(current_time[1] >= '0' && current_time[1] <= '9') && (current_time[2] == ':') &&
		(current_time[3] >= '0' && current_time[3] <= '5') && (current_time[4] >= '0' &&
			current_time[4] <= '9') && (current_time[5] == ' ') && (current_time[6] == 'A'
				|| current_time[6] == 'a' || current_time[6] == 'P' || current_time[6] == 'p') &&
		(current_time[7] == 'M' || current_time[7] == 'm')) {

		string c_hour, c_minute, meridian;
		c_hour.push_back(current_time[0]);
		c_hour.push_back(current_time[1]);
		c_minute.push_back(current_time[3]);
		c_minute.push_back(current_time[4]);
		meridian.push_back(toupper(current_time[6]));
		meridian.push_back(toupper(current_time[7]));
		current_hours = stoi(c_hour, 0, 10);
		current_minutes = stoi(c_minute, 0, 10);
		if (meridian == "AM") {
			marid = 1;
		}
		else {
			marid = 0;
		}
	}
	else {
		cout << ">> Invalid format.....\n";
		exit(1);
	}
	if (choice == 1) {
		return current_hours;
	}
	else if (choice == 2) {
		return current_minutes;
	}
	else if (choice == 3) {
		return marid;
	}
	else {
		cout << ">> Invalid function call......\n";
		exit(1);
	}
}
int time_calc(int current_hours, int current_minutes, int current_meridian,
	int future_hours, int future_minutes, int future_meridian) {
	int current_total_mins, future_total_mins;
	if (current_meridian == 0) {
		current_hours += 12;
	}
	if (future_meridian == 0) {
		future_hours += 12;
	}
	current_total_mins = (current_hours * 60) + current_minutes;
	future_total_mins = (future_hours * 60) + future_minutes;
	return abs(future_total_mins - current_total_mins);
}
void time_calculator() {
	int current_hours, current_minutes, current_meridian;
	int future_hours, future_minutes, future_meridian;
	int current_total_mins = 0, future_total_mins = 0, time_difference;
	string current_time, future_time;

	// Name   : Muhammad Omar Farooq
	// Reg No : 20-CP-33

	cout << " ________________________________________________________________\n";
	cout << "|\t\t\t\t\t\t\t         |\n";
	cout << "| In the Name of Allah, the Most  Gracious and the Most Merciful |" << endl;
	cout << "|\tProgrammed by : Muhammad Omar Farooq\t\t         |\n";
	cout << "|\tReg No : 20-CP-33\t\t\t\t         |\n";
	cout << "|\tSubmitted To : Sir Sheharyar\t\t\t         |\n";
	cout << "|\tDepartment of Computer Engineering\t\t         |\n";
	cout << "|  University of Engineering and Technology, Taxila\t\t |\n";
	cout << "|________________________________________________________________|\n\n";

	cout << ">> The time entered should have to following format >> \"09:00 PM\"\n";
	while (true) {
		cout << ">> Enter the current time >> ";
		cin.ignore();
		getline(cin, current_time);
		current_hours = time_check(current_time, 1);
		current_minutes = time_check(current_time, 2);
		current_meridian = time_check(current_time, 3);

		cout << ">> Enter the time of future that you want to travel to >> ";
		getline(cin, future_time);
		future_hours = time_check(future_time, 1);
		future_minutes = time_check(future_time, 2);
		future_meridian = time_check(future_time, 3);

		cout << ">> The time difference is >> " << time_calc(current_hours, current_minutes, current_meridian,
			future_hours, future_minutes, future_meridian) << " minutes.\n";
		cout << ">> Do you want to use the app again? (Y/N) >> ";
		char choice;
		cin >> choice;
		if (choice == 'n' || choice == 'N') { break; }
	}
}

