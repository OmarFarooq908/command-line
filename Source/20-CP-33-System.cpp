#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>
#include <iomanip>

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
		cin.ignore();			//
		getline(cin, directory); // 
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
void scrabble() {
	int n_letters, word_length, array_word_length, final_score = 0;
	int number_of_correct_words = 0;
	int random_num[12];
	char choice;
	bool invalid_letter = false;
	string ascii_n_letters, position, word;
	string note = "";

	/* As the number of letters should be between 3 and 15. So 15-3 is 12.
	 Therefore the size of array declared below will be 12 */
	string ascii_score[12];
	int score[12];
	char letters[12];

	// Name   : Muhammad Omar Farooq
	// Reg No : 20-CP-33

	cout << " ________________________________________________________________\n";
	cout << "|\t\t\t\t\t\t\t         |\n";
	cout << "| In the Name of Allah, the Most  Gracious and the Most Merciful |" << endl;
	cout << "|\tProgrammed by : Muhammad Omar Farooq\t\t         |\n";
	cout << "|\tReg No : 20-CP-33\t\t\t\t         |\n";
	cout << "|\tSubmitted To : Ma'am Afshan Jamil\t\t         |\n";
	cout << "|\tDepartment of Computer Engineering\t\t         |\n";
	cout << "|  University of Engineering and Technology, Taxila\t\t |\n";
	cout << "|________________________________________________________________|\n";

	cout << "\t\t ________________________________\n";
	cout << "\t\t|\t\t\t\t |\n";
	cout << "\t\t|\t Welcome to Scrabble\t |\n";
	cout << "\t\t|________________________________|\n";

	cout << " ________________________________________________________________\n";
	cout << "|\t\t\t\t\t\t\t\t |\n";
	cout << "|\t\t\tRules of the Game\t\t\t |\n";
	cout << "|________________________________________________________________|\n";
	cout << "|\t|\t\t\t\t\t\t\t |\n";
	cout << "|Sr. No |\t\t\tRules\t\t\t\t |\n";
	cout << "|_______|________________________________________________________|\n";
	cout << "|\t|\t\t\t\t\t\t\t |\n";
	cout << "|\t| You will be asked to enter the number of letters, \t |\n|   1.  | lets say n letters, allowed to make the word." <<
		"The number|\n" <<
		"|\t| of letters allowed should not be less than 3 and should|\n|\t| not exceed 15.\t\t\t\t\t |\n";
	cout << "|_______|________________________________________________________|\n";
	cout << "|\t|\t\t\t\t\t\t\t |\n";
	cout << "|\t| You will be asked to enter score for n letters. Score  |\n|   2.  | assigned to each letter should not be" <<
		" negative \t |\n|\t| or zero and should be less than 10."
		"\t\t\t |\n";
	cout << "|_______|________________________________________________________|\n";
	cout << "|\t|\t\t\t\t\t\t\t |\n";
	cout << "|   3.  | User will construct one word out of the n letters. Each|\n|\t| Each valid word recieves one score" <<
		"\t\t\t |\n";
	cout << "|_______|________________________________________________________|\n";
	cout << "|\t|\t\t\t\t\t\t\t |\n";
	cout << "|\t| Score for a word is the sum of the points for letters  |\n|   4.  | in the word plus 50 points if all n" <<
		" letters are used on|\n|\t| the go. Zero score will be displayed if word\t\t |\n|\t| constructed by user has any" <<
		"letter other than allowed\t |\n|\t| list.\t\t\t\t\t\t\t |\n";
	cout << "|_______|________________________________________________________|\n";

	srand(time(0));
	do {
		int total_score = 50;
		while (true) {
			cout << "\n>> Enter the number of letters allowed to make word >> ";
			cin >> ascii_n_letters;
			bool positive = true;
			bool negative = false;
			bool invalid = false;
			int digit_length;
			digit_length = (ascii_n_letters.length() - 1);
			n_letters = 0;
			for (int i = 0; i <= digit_length; i++) {
				if (positive) {
					if (int(ascii_n_letters[0]) == 45) {
						negative = true;
						positive = false;
						continue;
					}
				}
				if (int(ascii_n_letters[i]) < 48 || int(ascii_n_letters[i]) > 57) {
					invalid = true;
					break;
				}
			}
			if (invalid) {
				cout << ">> You entered an invalid number.....\n";
				continue;
			}
			else if (invalid == false && positive) {
				for (int i = 0; i <= digit_length; i++) {
					// Fundamental concept of counting. (Positional Notation)
					n_letters += (int(ascii_n_letters[(digit_length - i)]) - 48) * pow(10, i);
				}
				if (n_letters >= 3 && n_letters <= 15) {
					break;
				}
				else {
					cout << ">> Invalid range. Follow rule number 1.\n";
					continue;
				}
			}
			else if (invalid == false && negative) {
				cout << ">> The entered number should be a positive number.\n";
			}
		}
		for (int i = 0; i < n_letters; i++) {
			random_num[i] = rand() % 90;
			if (random_num[i] < 0) {
				random_num[i] *= (-1);
			}
			if (random_num[i] < 65) {
				i -= 1;
			}
		}
		for (int i = 0; i < n_letters; i++) {
			letters[i] = random_num[i];
		}
		cout << ">> Make a word out of the following letters >> \n";
		for (int i = 0; i < n_letters; i++) {
			cout << setw(50) << (letters[i]) << endl;
		}
		for (int i = 0; i < n_letters; i++) {
			if (i + 1 == 1) {
				position = "st";
			}
			else if (i + 1 == 2) {
				position = "nd";
			}
			else if (i + 1 == 3) {
				position = "rd";
			}
			else {
				position = "th";
			}
			while (true) {
				cout << ">> Enter the score for \"" << letters[i] << "\" >> ";
				cin >> ascii_score[i];
				int score_digit_length;
				score_digit_length = (ascii_score[i].length() - 1);
				score[i] = 0;
				for (int j = 0; j <= score_digit_length; j++) {
					if (int(ascii_score[i][j]) >= 48 && int(ascii_score[i][j]) <= 57) {
						score[i] += (int(ascii_score[i][(score_digit_length - j)]) - 48) * pow(10, j);
					}
				}
				if (score[i] > 0 && score[i] < 10) {
					break;
				}
				else {
					cout << ">> Invalid score. Follow rule number 2." << endl;
				}
			}

		}

		cout << ">> Make a word from the following letters >> ";
		for (int i = 0; i < n_letters; i++) {
			cout << "\"" << letters[i] << "\" ";
		}

		while (true) {
			int number_of_correct_words = 0;
			cout << "\n>> Enter the word >> ";
			cin >> word;
			word_length = word.length();
			array_word_length = word_length - 1;
			// To convert upper case to lower case in order to compare letters without taking
			// upper and lower case into account
			for (int i = 0; i <= array_word_length; i++) {
				if (int(word[i]) >= 97 && int(word[i]) <= 122) {
					word[i] -= 32;
				}
			}
			int j = 0;
			for (int i = 0; i < n_letters; i++) {
				if (int(word[j]) < 65 || (int((word[j]) > 90 && int(word[j]) < 97)) || int(word[j]) > 122) {
					invalid_letter = true;
				}
			}
			if (word_length == n_letters) {
				for (int i = 0; i < word_length; i++) {
					for (j = 0; j < word_length; j++) {
						if (int(word[j]) < 65 || int((word[j]) > 90 && int(word[j]) < 97) || int(word[j]) > 122) {
							invalid_letter = true;
						}
						if (letters[i] == word[j]) {
							number_of_correct_words++;
							break;
						}

						else if (j == word_length - 1) {
							if (letters[i] != word[j]) {
								total_score = 0;
								note = ">> Acording to rule 4 ";
								cout << note << ">> The score is >> " << total_score << endl;
								note = "";
								i = word_length + 1;
								break;
							}
						}
					}
					if (letters[i] == word[j]) {
						continue;
					}
				}
				for (int i = 0; i < word_length; i++) {
					total_score += score[i];
				}
				if (number_of_correct_words == word_length) {
					break;
				}
			}
			total_score = 0;
			if (invalid_letter) {
				note = ">> Acording to rule 4 ";
				total_score = 0;
				cout << note << ">> The score is >>  " << total_score << endl;
				cout << ">> The word contains a character other than English alphabet.....\n";
				cout << ">> Please make a word out of the English alphabets.\n";
				invalid_letter = false;
			}
			cout << ">> Try again....." << endl;
		}
		final_score += total_score;
		cout << note << ">> The score is >>  " << total_score << endl;
		cout << ">> Do you want to play again? (Y/N) >> ";
		cin >> choice;
	} while (choice == 'Y' || choice == 'y');
	cout << ">> Your final score is >> " << final_score << endl;
}
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
	cout << "|\tSubmitted To : Ma'am Ayesha\t\t\t         |\n";
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
