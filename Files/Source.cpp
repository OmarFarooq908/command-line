#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>
#include <iomanip>
#include <cstring>
#include "ceasar.h" //Self made
using namespace std;

bool logged_in = false;
int directory_list_index = 0;

void string_lower(string& command) {
	for (int i = 0; i < command.length(); i++) {
		if ((int(command[i]) >= 65) && ((int(command[i])) <= 90)) {
			command[i] = char((int(command[i])) + 32);
		}
	}
}

void help() {
	cout << "1.  help --------- displays a list of instructions\n";
	cout << "2.  user-l ------- login to account\n";
	cout << "3.  user-p ------- forgot password\n";
	cout << "4.  user-o ------- logout\n";
	cout << "5.  user-d ------- delete user account\n";
	cout << "6.  user-c ------- create user account\n";
	cout << "7.  dir-mk ------- make a folder in the current directory\n";
	cout << "8.  dir-d -------- delete current directory\n";
	cout << "9.  dir-b -------- go to parent directory\n";
	cout << "10. dir-r -------- go to root directory\n";
	cout << "11. dir-g -------- go to a directory\n";
	cout << "12. dir-l -------- list folders in current directories\n";
	cout << "13. app-run ------ run an app - requires login\n";
	cout << "14. app-d -------- delete an app - requires login\n";
	cout << "15. app-l -------- display the list of installed apps - requires login\n";
	cout << "16. system-s ----- system shutdown\n";
	cout << "17. system-c ----- go back to command line mode from input state" << 
		" (works in the middle of command)\n";
}
void file_find(vector <string> directory_list, string& current_directory, string filename) {
	int counter = 0;
	for (int i = 0; i < directory_list.size(); i++) {
		int a = 0;
		counter = 0;

		for (int j = directory_list[i].size() - 1; j > directory_list[i].size() - filename.length() - 1; j--) {
			if ((filename.length() - a - 1 >= 0) &&
				(directory_list[i][j] == filename[filename.length() - a - 1])) {
				a++;
				counter++;
			}

		}
		if (counter == filename.length()) {
			current_directory = directory_list[i];
			directory_list_index = i;
			break;
		}
	}

}
void user_c(string valid_command, string& current_directory, vector <string>& directory_list,
	vector <string>& usernames, vector <string>& passwords) {
	bool continue_command = true;
	while (continue_command) {
		if (valid_command == "user-c") {
			string t_user, t_pass;
			cout << current_directory << "/ >> Enter a user name >> ";
			cin.ignore();			//
			getline(cin, t_user);  //
			//cin >> t_user;		
			if (t_user == "system-c") {
				continue_command = false;
			}
			usernames.push_back(t_user);
			cout << current_directory << "/ >> Enter a password >> ";
			getline(cin, t_pass);//
			//cin >> t_pass;
			if (t_pass == "system-c") {
				continue_command = false;
			}
			passwords.push_back(t_pass);
			directory_list.push_back("/dev/root/users/" + usernames[usernames.size() - 1]);
			directory_list.push_back("/dev/root/users/" + usernames[usernames.size() - 1] + "/apps");
			cout << current_directory << "/ >> User created successfully.\n";
			break;
		}
	}
}
void user_l(string valid_command, string& current_directory, vector <string> directory_list,
	string& current_user, vector <string>& usernames, vector<string>& passwords) {
	if (logged_in) {
		cout << current_directory << "/ >> You are already logged in.\n";
	}
	else {
		string in_username, in_password;
		bool user_found = false;
		bool pass_found = false;
		bool continue_command = true;
		while (continue_command) {
			cout << current_directory << "/ >> Enter username >> ";
			cin.ignore();
			getline(cin, in_username); //
			//cin >> in_username;
			string temp_user = in_username;
			string_lower(temp_user);
			if (temp_user == "system-c") {
				continue_command = false;
			}
			int counter = 0;
			for (int i = 0; i < usernames.size(); i++) {
				if (in_username == usernames[i]) {
					user_found = true;
					break;
				}
				else { counter++; }
			}
			if (user_found) { break; }
			else { cout << current_directory << "/ >> Invalid User. User not found.\n"; }

		}

		while (continue_command) {
			cout << current_directory << "/ >> Enter password >> ";
			getline(cin, in_password); // 
			//cin >> in_password;
			string temp_pass = in_password;
			string_lower(temp_pass);
			if (temp_pass == "system-c") {
				continue_command = false;
			}
			int counter = 0;
			for (int i = 0; i < passwords.size(); i++) {
				if (in_password == passwords[i]) {
					pass_found = true;
					break;
				}
			}
			if (pass_found) { break; }
			else { cout << current_directory << "/ >> Invalid Password.\n"; }
		}
		if (continue_command) {
			file_find(directory_list, current_directory, in_username);
			current_user = in_username;
			logged_in = true;
			cout << current_directory << "/ >> Logged in successfully.\n";
		}
	}
}
void user_p(string& current_directory, vector<string>& usernames, vector<string>& passwords) {
	string a_username;
	int index = 0;
	bool continue_command = true;
	while (continue_command) {
		cout << current_directory << "/ >> Enter username >> ";
		cin.ignore();				//
		getline(cin, a_username); //
		//cin >> a_username;
		string temp_user = a_username;
		string_lower(temp_user);
		if (temp_user == "system-c") {
			continue_command = false;
		}
		if (find(usernames.begin(), usernames.end(), a_username) != usernames.end()) {
			index = find(usernames.begin(), usernames.end(), a_username) - usernames.begin();
			break;
		}
		else {
			cout << current_directory << "/ >> Username not found.\n";
		}
	}
	if (continue_command) {
		cout << current_directory << "/ >> Enter new password >> ";
		getline(cin, passwords[index]); //
		//cin >> passwords[index];
	}
}
void user_o(string& current_directory, vector <string> directory_list, string& current_user) {
	current_directory = directory_list[0];
	current_user = "";
	logged_in = false;
	cout << current_directory << "/ >> Logged out successfully.\n";
}
void user_d(string valid_command, string& current_directory, vector <string> directory_list,
	string& current_user, vector <string>& usernames, vector<string>& passwords) {
	string b_user, b_pass;
	bool user_found = false;
	bool pass_found = false;
	bool continue_command = true;
	while (continue_command) {
		cout << current_directory << "/ >> Enter username to delete the account >> ";
		cin.ignore();
		getline(cin, b_user); //
		//cin >> b_user;
		if (b_user == "system-c") {
			continue_command = false;
		}
		int counter = 0;
		for (int i = 0; i < usernames.size(); i++) {
			if (b_user == usernames[i]) {
				user_found = true;
				break;
			}
			else { counter++; }
		}
		if (user_found) {
			usernames.erase(remove(usernames.begin(), usernames.end(), b_user), usernames.end());
			break;
		}
		else { cout << current_directory << "/ >> Invalid User. User not found.\n"; }

	}

	while (continue_command) {
		cout << current_directory << "/ >> Enter password to delete the account >> ";
		getline(cin, b_pass); //
		//cin >> b_pass;
		if (b_pass == "system-c") {
			continue_command = false;
		}
		int counter = 0;
		for (int i = 0; i < passwords.size(); i++) {
			if (b_pass == passwords[i]) {
				pass_found = true;
				break;
			}
		}
		if (pass_found) {
			passwords.erase(remove(passwords.begin(), passwords.end(), b_pass), passwords.end());
			break;
		}
		else { cout << current_directory << "/ >> Invalid Password.\n"; }
	}
	directory_list.erase(remove(directory_list.begin(), directory_list.end(), directory_list[2] + b_user),
		directory_list.end());
	if (logged_in && continue_command) {
		current_directory = directory_list[0];
		logged_in = false;
	}
	cout << current_directory << "/ >> User account deleted successfully.\n";
}
void dir_mk(string& current_directory, vector <string>& directory_list) {
	string file;
	bool continue_command = true;
	cout << current_directory << "/ >> Enter a file name >> ";
	cin.ignore();		//
	getline(cin, file); // 
	//cin >> file;
	if (file == "system-c") {
		continue_command = false;
	}
	if (continue_command) {
		directory_list.push_back(current_directory + "/" + file);
		cout << current_directory << "/ >> Directory created successfully.\n";
	}
}
void dir_d(string& current_directory, vector <string>& directory_list) {
	directory_list.erase(remove(directory_list.begin(), directory_list.end(), current_directory),
		directory_list.end());
	current_directory = directory_list[0];
	cout << current_directory << "/ >> File deleted successfully.\n";
}
void dir_b(string& current_directory, vector <string> directory_list) {
	string temp = current_directory;
	string parent_directory;
	for (int i = temp.length() - 1; temp[i] != '/'; i--) {
		temp.erase(i);
	}
	temp.pop_back();
	current_directory = temp;
}
void dir_r(string& current_directory, vector <string> directory_list) {
	current_directory = directory_list[1];
}
void dir_g(string& current_directory, vector <string> directory_list) {
	string directory;
	bool continue_command = true;
	while (continue_command) {
		bool found = false;
		cout << current_directory << "/ >> The directory name format should be \"/dev/root/users\" >> ";
		cin >> directory;
		//cin >> directory;
		if (directory == "system-c") {
			continue_command = false;
		}
		for (int i = 0; i < directory_list.size(); i++) {
			if (directory == directory_list[i]) {
				current_directory = directory_list[i];
				found = true;
				break;
			}
		}
		if (found) { break; }
		else {
			cout << current_directory << "/ >> Directory not found.\n";
		}
	}
}
void dir_l(string& current_directory, vector <string> directory_list) {
	vector <string> files;
	vector <int> vec_file_slashes;
	string temp = current_directory;
	int current_slashes = 0;
	int file_slashes = 0;
	for (int i = 0; i < directory_list.size(); i++) {
		current_slashes = 0;
		for (int j = 0; j < temp[j] != '\0'; j++) {
			if (temp[j] == '/') {
				current_slashes++;
			}
			if ((temp.length() < directory_list[i].length()) && (temp[j] == directory_list[i][j])) {
				files.resize(i + 1);
				files[i] = directory_list[i];
			}
		}
	}
	for (int i = 0; i < files.size(); i++) {
		for (int j = 0; j < files[i].length(); j++) {
			if (files[i][j] == '/') {
				vec_file_slashes.resize(i + 1, 0);
				vec_file_slashes[i]++;
			}
		}
	}
	for (int i = 0; i < files.size(); i++) {
		if (vec_file_slashes[i] == current_slashes + 1) {
			cout << "---------> " << files[i] << endl;
		}
	}
}
void playstore(string current_directory, vector <string> &installed_apps) {
	string app_install;
	vector <string> app_list{ "base-n-base10", "ceaser-cipher-encryption", "scrabble", "time-calculator" };
	cout << current_directory << "/ >> Following is the list of apps available >> \n";
	cout << "\t\tBase-N-Base10\n\t\tCeaser-Cipher-Encryption\n\t\tScrabble\n\t\tTime-Calculator\n";
	while (true) {
		cout << current_directory << "/ >> Enter the app name to install the app >> ";
		cin >> app_install;
		string_lower(app_install);
		bool app_found = false;
		for (int i = 0; i < app_list.size(); i++) {
			if (app_install == app_list[i]) {
				installed_apps.resize(installed_apps.size() + 1);
				installed_apps[installed_apps.size() - 1] = app_install;
				cout << current_directory << "/ >> App installed successfully.\n";
				app_found = true;
				break;
			}
		}
		if (app_found) { break; }
		else {
			cout << current_directory << "/ >> This app is not available in the playstore.\n";
		}
	}
}
void app_run(string current_directory, vector <string> &installed_apps) {
	string app_name;
	bool app_found = false;
	bool continue_command = true;
	if (logged_in) {
		while ((app_found == false) && continue_command) {
			cout << current_directory << "/ >> Enter the app name to run it >> ";
			cin >> app_name;
			string_lower(app_name);
			if (app_name == "system-c") {
				continue_command = false;
			}
			for (int i = 0; i < installed_apps.size(); i++) {
				if (installed_apps[i] == app_name) {
					app_found = true;
				}
			}
			if (app_found == false) {
				cout << current_directory << "/ >> App is not installed.\n";
			}
		}
		if (app_found && continue_command) {
			cout << current_directory << "/ >> Running " << app_name << endl;
			if (app_name == installed_apps[0]) {
				playstore(current_directory, installed_apps);
			}
			else if (app_name == "base-n-base10") {
				base_n_base10();
			}
			else if (app_name == "ceaser-cipher-encryption") {
				ceaser_cipher_encryption();
			}
			else if (app_name == "scrabble") {
				scrabble();
			}
			else if (app_name == "time-calculator") {
				time_calculator();
			}
		}
		else {
			if (continue_command) {
				cout << current_directory << "/ >> This app is not installed.\n";
			}
		}
	}
	else {
		cout << current_directory << "/ >> To run an app, you need to login.\n";
	}
}
void app_d(string current_directory, vector <string> &installed_apps) {
	string delete_app;
	bool app_found = false;
	if (logged_in) {
		while (app_found == false) {
			cout << current_directory << "/ >> Enter the app name to delete the app >> ";
			cin >> delete_app;
			string_lower(delete_app);
			if (delete_app == "system-c") {
				break;
			}
			for (int i = 0; i < installed_apps.size(); i++) {
				if (delete_app == installed_apps[i]) {
					installed_apps.erase(installed_apps.begin() + i);
					cout << current_directory << "/ >> App deleted successfully.\n";
					app_found = true;
				}
			}
		}
	}
	else {
		cout << current_directory << "/ >> To delete an app, you need to login.\n";
	}
}
void app_l(string current_directory, vector <string> installed_apps) {
	bool apps_installed = false;
	if (logged_in) {
		for (int i = 0; i < installed_apps.size(); i++) {
			if (installed_apps[i] != "") {
				apps_installed = true;
				break;
			}
		}
		cout << current_directory << "/ >> ";
		if (apps_installed) {
			cout << "You have the following apps installed.\n";
			for (int i = 0; i < installed_apps.size(); i++) {
				cout << "-----------> " << installed_apps[i] << endl;
			}
		}
		else {
			cout << "There are no installed apps.\n";
		}
	}
	else {
		cout << current_directory << "/ >> To see the list of installed apps, you need to login.\n";
	}
}
void system_s(string current_directory) {
	cout << current_directory << "/ >> System shutting down..........\n";
	exit(0);
}
string command_search(string raw_command, vector <string> command_list, int len) {

	int i;
	for (i = 0; i < len; i++) {
		if ((raw_command == command_list[i]) && (raw_command.length() == command_list[i].length())) {
			return command_list[i];
		}
	}
	if (i == len) {
		return "Invalid command";
	}
	else {
		return "System crashed";
		exit(1);
	}
}
void branching(string valid_command, string& current_user, string& current_directory,
	vector <string> &installed_apps, vector <string>& directory_list, vector <string>& usernames,
	vector<string>& passwords) {
	if (valid_command == "help") {
		help();
	}
	else if (valid_command == "user-c") {
		user_c(valid_command, current_directory, directory_list, usernames, passwords);
	}
	else if (valid_command == "user-l") {
		user_l(valid_command, current_directory, directory_list, current_user, usernames, passwords);
	}
	else if (valid_command == "user-p") {
		user_p(current_directory, usernames, passwords);
	}
	else if (valid_command == "user-o") {
		user_o(current_directory, directory_list, current_user);
	}
	else if (valid_command == "user-d") {
		user_d(valid_command, current_directory, directory_list, current_user, usernames, passwords);
	}
	else if (valid_command == "dir-mk") {
		dir_mk(current_directory, directory_list);
	}
	else if (valid_command == "dir-d") {
		dir_d(current_directory, directory_list);
	}
	else if (valid_command == "dir-b") {
		dir_b(current_directory, directory_list);
	}
	else if (valid_command == "dir-r") {
		dir_r(current_directory, directory_list);
	}
	else if (valid_command == "dir-g") {
		dir_g(current_directory, directory_list);
	}
	else if (valid_command == "dir-l") {
		dir_l(current_directory, directory_list);
	}
	else if (valid_command == "app-run") {
		app_run(current_directory, installed_apps);
	}
	else if (valid_command == "app-d") {
		app_d(current_directory, installed_apps);
	}
	else if (valid_command == "app-l") {
		app_l(current_directory, installed_apps);
	}
	else if (valid_command == "system-s") {
		system_s(current_directory);
	}
	else if (valid_command == "system-c") {
		cout << current_directory << "/ >> You are already in command line mode.\n";
	}
}

int main() {
	string raw_command, valid_command;
	string invalid_command = "Invalid command";
	string current_directory = "/dev";
	string current_user = "";
	int len;
	int k = 2;
	int user_pass_length = 1;
	vector <string> installed_apps{ "playstore" };
	vector <string> directory_list{ "/dev", "/dev/root", "/dev/root/users","/dev/root/apps" };
	vector <string> usernames{ "root" };
	vector <string> passwords{ "root" };
	vector <string> command_list{ "help", "user-l", "user-p", "user-o", "user-d", "user-c", "dir-mk",
							  "dir-d", "dir-b", "dir-r", "dir-g", "dir-l", "app-run", "app-d",
							  "app-m", "app-l", "system-c", "system-s" };

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

	cout << ">> Welcome to system command line.\n";
	cout << ">> For more information , type \"help\"\n";
	cout << ">> Users: \n\t1. root\n";
	len = command_list.size();
	while (true) {
		cout << current_directory << "/ >> ";
		cin >> raw_command;
		string_lower(raw_command);
		valid_command = command_search(raw_command, command_list, len);
		if (valid_command == invalid_command) {
			cout << valid_command << endl;
			continue;
		}
		else {
			branching(valid_command, current_user, current_directory, installed_apps,
				directory_list, usernames, passwords);
		}
	}
	branching(valid_command, current_user, current_directory, installed_apps, 
		directory_list, usernames, passwords);
	return 0;
}
