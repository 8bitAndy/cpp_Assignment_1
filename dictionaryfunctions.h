#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Struct provides info such as the name of a word, the type (e.g verb or noun) and it's definition.
struct Word {
	string name;
	string type;
	string definition;
};

// Main menu
void mainMenu(vector<Word> words);

// Function signature for reading data from our text file
vector<Word> readTextFile();

// This function adds functionality fufills task 1 of the assignment.
void wordSearch(vector<Word> words);

// This function adds functionality fufills task 2 of the assignment.
void characterSearch(vector<Word> words);

// This function adds functionality fufills task 3 of the assignment.
void conditionSearch(vector<Word> words);

// Converts uppercase words to lower case. Made to ensure all searches occur regardless of case of search term
string lowerCase(string);

bool isInteger(string str);