#include <iostream>
#include <vector>
#include "dictionaryfunctions.h" // Header file that contains functions requested for the assignment
using namespace std;

/*
	Program by: Liam Andrews
	Student Number: 1054 8022
	Created on 4/03/2022
*/


// Main function for entire project
int main() {

	// Reads in text file for processing
	vector<Word> words = readTextFile();

	// Run main program loop
	mainMenu(words);

	return 0;
}

// Main menu function loops until valid input used
void mainMenu(vector<Word> words) {

	// Integer used for user input when selecting menu choice
	string menuChoice;

	// Main menu that presents user with a choice from several options
	while (true) {
		menuChoice = "0";
		// User options
		cout << "\nSelect an option from the below menu:" << endl;
		cout << "\n1. Word search" << endl;
		cout << "2. Character search" << endl;
		cout << "3. List words without that fufill our conditions" << endl;
		cout << "4. Terminate program" << endl;

		cout << "\nYour choice: ";
		getline(cin, menuChoice);
		
		// Logic for deciding what should happen after user enters input
		if (menuChoice == "1") {
			wordSearch(words);
		}
		else if (menuChoice == "2") {
			characterSearch(words);
		}
		else if (menuChoice == "3") {
			conditionSearch(words);
		}
		else if (menuChoice == "4") {
			cout << "Closing program" << endl;
			break;
		}
	}
}


// Function is responsible for reading in data from the text file and assigning it to a word struct, then placed in a word vector
// Returns a vector of Word structs
vector<Word> readTextFile() {
	// Text that holds a line of text file
	string myText;
	// Name of text file
	ifstream fileName("dictionary2022_S1.txt");
	// Line counter for file, starts at 1. Used to determine what line to assign top which struct attribute
	int lineCounter = 1;

	// Create a new vector of Word structs 
	vector<Word> words;

	// Create an instance of a Word struct
	Word currentWord;

	// Lets user know that something happening
	cout << "Loading text file into program..." << endl;

	// Keep looping until end of file
	while (!fileName.eof()) {
		getline(fileName, myText);
		//cout << "Line number: " << lineCounter << " " << myText << endl;

		// Logic for assigning lines to struct fields 1 = type, 2 = word, 3 = description, 4 = separator
		if (lineCounter == 1){
			currentWord.type = myText;
		}
		else if (lineCounter == 2){
			currentWord.name = myText;
		}
		else if (lineCounter == 3){
			currentWord.definition = myText;
		}
		// File has reached a separator and will reset line counter to zero, will add current struct to the words vector
		else if (lineCounter == 4){
			// Reset line counter
			lineCounter = 0;

			// Add current word to the vector of words
			words.push_back(currentWord);
		}


		lineCounter++;
	}

	// Closing text file to prevent any errors from occuring later on.
	fileName.close();

	// Clear screen and print success message
	system("CLS");
	cout << "File loaded successfully" << endl;

	// TEST TO PRINT OUT VECTOR
	//cout << "TEST " << words[105159].name << endl;
	

	// Return the vector that now contains all of the word structs
	return words;
}

// This function adds functionality fufills task 1 of the assignment.
void wordSearch(vector<Word> words) {
	system("CLS");
	cout << "This is the word search function" << endl;

	string searchTerm;

	// Determine if a word has been found
	bool foundWord = false;

	cout << "Please enter a search term: ";
	getline(cin, searchTerm);

	// Convert search term all to lower case, helps with searching dictionary.
	string test = lowerCase(searchTerm);


	// CHECK TO SEE IF IT WORKS
	//cout << "lower case version is: " << test << endl;

	// Loop through vector words, print out search terms
	for (int x = 0; x < words.size(); x++) {
		
		// If the search term is equal to a value in the dictionary then print it
		if (words[x].name == test) {
			cout << words[x].name << endl;
			cout << words[x].type << endl;
			cout << endl;
			cout << words[x].definition << endl;

			// Determine if error message is displayed below
			foundWord = true;
		}
	}

	// Show user word is not in dictionary if search returns no value
	if (foundWord == false) {
		cout << "\nNo word found, or incorrect input. Try again" << endl;
	}

	// Creates blank line after search
	cout << endl;
}

// This function adds functionality fufills task 2 of the assignment.
void characterSearch(vector<Word> words) {
	cout << "This is the character search function" << endl;

	// Determine if any words matched search criteria
	bool wordFound = false;
	// User's input for when they perform a search, and how many times they occur
	string charToSearch;
	// Count how many matches we get for our character
	string instanceOfChar;

	// Get user's input for above variables
	cout << "Enter a char to search: ";
	getline(cin, charToSearch);

	// Make sure input is a single character
	if (charToSearch.length() != 1) {
		cout << "Incorrect input" << endl;
		//Return to main function
		return;
	}
	
	// If number then return
	if (!isalpha(charToSearch[0])) {
		cout << "no numbers allowed" << endl;
		return;
	}

	charToSearch = lowerCase(charToSearch);

	cout << "\nHow many instances of this char do you want within a word?" << endl;
	getline(cin, instanceOfChar);

	// Check is only a single value, return to main if single not single digit or char
	if (instanceOfChar.length() != 1) {
		cout << "bad job" << endl;
		return;
	}

	// Check if value is an integer
	if (isInteger(instanceOfChar) == false) {
		cout << "not an integer" << endl;
		return;
	}

	int testCount = stoi(instanceOfChar);

	// Check to see if input is a number
	if (testCount <= 0) {
		cout << "error" << endl;
		return;
	}

	// Loop through vector of Words and perform a search
	for (int i = 0; i < words.size(); i++) {
		
		// Reset value to zero for our amount of matches, used to count how many matches we have
		int currentCount = 0;

		string currentWord = words[i].name;

		// Loop through each character within our current word.
		for (int c = 0; c < currentWord.length(); c++) {
			
			// Check if current words character matches our char we are searching for
			if (currentWord[c] == charToSearch[0]) {
				currentCount += 1;
			}
		}

		//Print out any words that have equal or more of the char we are searching for
		if (currentCount >= testCount) {
			cout << currentWord << endl;

			// CHANGE TO MAKE THIS BETTER
			wordFound = true;
		}
	}

	// If we didn't find any results
	if (wordFound == false) {
		cout << "Couldn't find anything that matched your request.\n" << endl;
	}

}

// This function adds functionality fufills task 3 of the assignment.
void conditionSearch(vector<Word> words) {
	cout << "This function will return words that have a Q without a following U" << endl;

	bool goodWord = false, discardWord = false;
	int count = 0;

	// Loop through vector of words
	for (int i = 0; i < words.size(); i++) {
		
		// Current word in vector
		string currentWord = words[i].name;
		bool badWord = false;
		bool hasQ = false;
		string bad = "qu";


		if (currentWord.find(bad) != string::npos) {
			badWord = true;
		}

		if (currentWord.find("q") != string::npos) {
			hasQ = true;
		}

		if (hasQ == true && badWord == false) {
			cout << currentWord << endl;
			count += 1;
		}
	}
	cout << "word count is: " << count << endl;
}

// Takes in any string and converts every character to lower case, output is same string converted
string lowerCase(string input) {
	// Creating result string that will be returned
	string result = input;

	for (int i = 0; i < input.length(); i++) {
		result[i] = tolower(input[i]);
	}

	return result;
}

bool isInteger(string str) {
	for (int i = 0; i < str.length(); i++) {
		if (isdigit(str[i]) == false) {
			return false;
		}
	}
	// If returning this assume value is an integer
	return true;
}