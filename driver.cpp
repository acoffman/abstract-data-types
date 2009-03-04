/******************************
 * Author: Adam Coffman
 *
 * Filename: driver.cpp
 *
 * Description: This is the runnable element of the crossword puzzle solver
 * 	it contains the main method, the user interface and appropriate helper
 * 	functions.
 *
 * Build Instructions: A makefile is included in the project directory
 * 	program can be run as follows:
 * 	make
 * 	./driver
 ******************************/

#include <ctime>
#include <iostream>
#include "SearchableADT.h"
#include "BST.h"
#include "AVL.h"

using namespace std;

//Global Variables (the dictionary) and function prototypes
SearchableADT<string> *dictionary;
double time_this(void (*f)());
void load_dictionary();
void clear_dictionary();
void search_word();
void search_file();
void report_stats();
void search_single_word(string word);

//This function takes a void function pointer 
//and runs it with the timing code wrapped around it
//this saves from having the timing code duplicated in every
//function.
double time_this(void (*f)()){
	clock_t start, finish;
	start = clock();
	f();
	finish = clock();
	return ((double)(finish-start)/CLOCKS_PER_SEC);
}

//Main: includes menus and calls to helper functions.
int main(int agvc, char* argvc[]){

	int choice;
	
	cout << "Crossword Puzzle Helper" << endl << endl;
	cout << "Please select a number: " << endl
			 << "1. Use Binary Search Tree" << endl
			 << "2. Use AVL Tree" << endl
			 << "Please select 1 or 2: ";
	cin >> choice;

	while(choice != 1 && choice != 2){
		cout << "Invalid selection, please choose 1 or 2: ";
		cin >> choice;
	}

	if(choice == 1)
		dictionary = new BST<string>;
	else
		dictionary = new AVL<string>;

	do{
		cout << "Main Menu" << endl
				 << "   1. Load dictionary from file." << endl
			 	 << "   2. Clear current dictionary." << endl
				 << "   3. Check for an entry." << endl
				 << "   4. Check for entries from a file." << endl
			 	 << "   5. Report tree statistics." << endl
				 << "   6. Exit." << endl
				 << "Selection: ";

		cin >> choice;
		while(choice < 1 || choice > 6){
			cout << endl << "Invalid selection, please choose a number 1 through 5: ";
			cin >> choice;
		}

		cout << "\n\n";
	
		if(choice == 1){
		
			double time = time_this(&load_dictionary);
			cout << "Dictionary loaded in: " << time << " seconds." << endl;

		}else if(choice == 2){
		
			double time = time_this(&clear_dictionary);
			cout << "Dictionary cleared in: " << time << " seconds." << endl;
	
		}else if(choice == 3){
		
			double time = time_this(&search_word);
			cout << "Your query was completed in " << time << " seconds." << endl;
	
		}else if(choice == 4){

			double time = time_this(&search_file);
			cout << "Your query was completed in " << time << " seconds." << endl;	
	
		}else if(choice == 5){
		
			double time = time_this(&report_stats);
			cout << "Statistics collected in: " << time << " seconds." << endl;
	
		}else return 0;
  
		cout << "\n\n";

	}while(true);	
	return 0;
}

//Prompts the user for and then loads a dictionary file
//Won't crash if the file is invalid
void load_dictionary(){
	int result;
	do{
			string filename;
			cout << "Please enter a filename to load: ";
			cin >> filename;
			result = dictionary->loadFromFile(filename);
		}while(result == -1);	
}

//Clears the dictionary
void clear_dictionary(){
	dictionary->clear();
}

//Takes a word input from the command prompt and searches the dictionary for it
void search_word(){
	string word; 
	cout << "Please enter the word you would like to search for: ";
	cin >> word;
	search_single_word(word);
}

//Takes a file from the command prompt, reads it in and searches each
//word in the file
void search_file(){
	string word;
	ifstream fin;
	string filename;
	cout << "Please enter the filename to search: " ;
	cin >> filename;
	fin.open(filename.c_str());
	if(fin.fail()){
		cout << "Unable to open file." << endl;
		return;
	}
	while(!fin.eof()){
		fin >> word;
		search_single_word(word);
	}
}

//Takes a string word argument and searches for the word (including blanks)
//in the SearchableADT.
void search_single_word(string word){
	int qPlace = -1;
	for(int i = 0; i< word.length(); i++)
		if(word[i] == '?')
			qPlace = i;
	if(qPlace > -1){
		string suggestions ="";
		for(char i = 'a'; i <= 'z'; i++){
			word[qPlace] = i;
			if(dictionary->isThere(word))
				suggestions = suggestions + word + " ";
		}

		word[qPlace] = '?';
		if(suggestions == "")
			cout << "Found no suggestions for "<< word << " in the loaded dictionary." << endl;
		else
			cout << "Suggestions: " << suggestions << endl;
	}else{
		if(dictionary->isThere(word))
			cout << word <<" is in the dictionary and appears to be spelled correctly. " << endl;
		else cout << word <<" is not in the dictionary and may be mispelled." << endl; 	
	}
}

//Reports statistics about the SearchableADT currently in use
void report_stats(){
		cout << "The dictionary has: " << dictionary->numEntries() << " entries." << endl;
		cout << "The tree is " << dictionary->treeHeight() << " layers deep." << endl;
}
