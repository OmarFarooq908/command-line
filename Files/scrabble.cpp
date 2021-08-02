#include "ceasar.h"
#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <iomanip>
using namespace std;
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
	cout << "|\tSubmitted To : Sir Sheharyar\t\t         |\n";
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

