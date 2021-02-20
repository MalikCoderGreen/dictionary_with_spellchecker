#include <iostream>
#include "Dictionary.h"
#include <string>
#include <sstream>
#include <vector>


/*
*
*Name : Maliak Green
*Course: COSC320
*Description: Project - 2 HashTable Dictionary that reads in words from a text file into a hash table and allows users to check if words are in the dictionary. A class decleared type "Dictionary" uses internal methods to check for suggestions on misspelled words.  
*
*
*/

int main(){

	std::cout << "SpellChecker Program \n";
	std::cout << "--------------------------------------\n\n";
	auto start0 = std::chrono::system_clock::now();
	Dictionary myDict;
	
	
	auto end0 = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds0 = end0 - start0;
	std::string text;

	size_t words = myDict.getDictSize();
	size_t b = myDict.bucketSize();
	size_t biggestB = myDict.biggestBucket();
	size_t smallestB = myDict.smallestBucket();
	size_t avgB = myDict.avgBucketSize();
	std::cout << "Total Words: " << words << std::endl;

	std::cout << "Biggest bucket size = " << biggestB << std::endl;
	std::cout << "Smallest bucket size = " << smallestB << std::endl;
	std::cout << "Total Number of buckets = " << 50000 << std::endl;
	std::cout << "Number of used buckets = " << b << std::endl;
	std::cout << "Average number of nodes in each bucket = " << avgB << std::endl;
	std::cout << "Total time taken = " << elapsed_seconds0.count() << std::endl;

	std::cout << "Please enter in some text: " << std::endl;
	std::cout << "******************************************* " << std::endl;
	std::getline(std::cin, text);
	std::vector <std::string> tokens;
	std::vector <std::string> tokens2;


	int miss = 0, sugg = 0;

	std::stringstream s;
	std::string tmp;
	s << text;

	auto start = std::chrono::system_clock::now();
	while(s >> tmp && s){
		
	
		for(int i = 0; i < tmp.length(); i++){
			if(tmp[i] == '.'){

				tmp.resize(tmp.length() - 1);
			}

		}

		myDict.checkText(tmp, miss, sugg);
	}

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;

	std::cout << "Summary\n";
	std::cout << "******************************************* " << std::endl;
	std::cout << "Number of misspelled words = " << miss << std::endl;  
	std::cout << "Number of suggestions = " << sugg << std::endl;
	std::cout << "Time required to find suggestions = " << elapsed_seconds.count() << std::endl;


	return 0;
}
