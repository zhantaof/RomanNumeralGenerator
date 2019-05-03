// RomanNumeralGenerator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>
#include <string>

class NumeralGenerator {

public:
	virtual std::string generate(int number) = 0;

};

class RomanNumeralGenerator : public NumeralGenerator {

private:
	// arrays for the main roman numeral characters and decimal numbers
	int arabicNumbers[13] = {1000, 900, 500, 400, 100, 90, 50, 40, 10,  9,  5,  4,  1};
	std::string romanNumerals[13] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

public:
	// function to convert decimal to roman numeral
	std::string generate(int number) {

		std::string output = "";
		for (int i = 0; i < 13; i++) {
			while (number >= arabicNumbers[i]) {
				// append roman numeral to output string 
				output += romanNumerals[i];
				// subtract arabic number from input integer
				number -= arabicNumbers[i];
			} // while
		} // for

		return output;
	}

	// function to convert roman numeral to decimal
	int generate(std::string roman) {
		// map to store the main roman and arabic pairs
		std::map<char, int> romanArabicMap;
		romanArabicMap['M'] = 1000;
		romanArabicMap['D'] = 500;
		romanArabicMap['C'] = 100;
		romanArabicMap['L'] = 50;
		romanArabicMap['X'] = 10;
		romanArabicMap['V'] = 5;
		romanArabicMap['I'] = 1;

		int currentValue = 0;
		int nextValue = 0;
		int lastValue = 0;
		int output = 0;

		for (int i = 0; i < roman.size() - 1; i++) {

			// get current and next position
			currentValue = roman[i];
			nextValue = roman[i + 1];

			// compare current with next value
			if (romanArabicMap[currentValue] < romanArabicMap[nextValue]) {
				output -= romanArabicMap[currentValue];
			} else {
				output += romanArabicMap[currentValue];
			}
		}
		// get the last remaining roman numeral character
		lastValue = roman[roman.size() - 1];
		output += romanArabicMap[lastValue];

		return output;
	}
};

// function to check if input is numerical
bool isNumerical(std::string input)
{
	for (int i = 0; i < input.length(); i++) {
		if (!isdigit(input[i])) {
			return false;
		}
	}
	return true;
}

int main()
{
	using namespace std;

	// declare variables
	string input;
	int number;
	int option;
	string res1;
	int res2;

	// initialise variables with standard input
	cout << "Please select one of the two options:" << endl;
	cout << "Option 1: Convert a specific number" << endl;
	cout << "Option 2: Convert a randomly generated number" << endl;
	cout << "Option 3: Test all numbers from 1 to 3999" << endl;
	cin >> option;

	if (option == 1) {
		cout << "Please enter a number between 1 and 3999: ";
		while (cin >> input) {
			if (!isNumerical(input)) {
				cerr << "Error! You have entered \"" << input << "\". Please enter a number of between 1 and 3999 " << endl;
				continue;
			}
			number = stoi(input);
			// check if number is between 1 and 3999
			if (number < 1 || number > 3999) {
				cerr << "Error! You have entered \""<< number << "\". Please enter a number of between 1 and 3999" << endl;
				continue;
			}

			// create object/call methods
			RomanNumeralGenerator obj = RomanNumeralGenerator();
			res1 = obj.generate(number);
			res2 = obj.generate(res1);

			// print string to standard output
			if (number == res2) {
				cout << number << " = \"" << res1 << "\"" << endl;
			} else {
				cerr << "Error when converting: " << number << "!" << endl;
				return 1;
			}
			cout << "Please enter a number between 1 and 3999: ";
		} // while
	} else if (option == 2) {
		// generate a random whole number between 1 and 3999
		number = 1 + rand() % 3999;
		// check if number is between 1 and 3999
		if (number < 1 || number > 3999) {
			cerr << "Error! Generated number is \"" << number << "\". Not in the range of 1 and 3999" << endl;
			return 1;
		}

		// create object/call methods
		RomanNumeralGenerator obj = RomanNumeralGenerator();
		res1 = obj.generate(number);
		res2 = obj.generate(res1);

		// print string to standard output
		if (number == res2) {
			cout << number << " = \"" << res1 << "\"" << endl;
		}
		else {
			cerr << "Error when converting: " << number << "!" << endl;
			return 1;
		}
	}
	else if (option == 3) {
		for (int number = 1; number <= 3999; number++) {

			// create object/call methods
			RomanNumeralGenerator obj = RomanNumeralGenerator();
			res1 = obj.generate(number);
			res2 = obj.generate(res1);

			// print string to standard output
			if (number == res2) {
				cout << number << " = \"" << res1 << "\"" << endl;
			}
			else {
				cerr << "Error at " << number << "!" << endl;
				return 1;
			}
		}
		cout << "Test Completed. All conversions are correct!" << endl;
	} else {
		cerr << "Error! Please select one of the two options." << endl;
	}
}
