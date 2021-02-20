#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <iostream>
#include <string>
class Dictionary{


/*
*
*Name : Maliak Green
*Course: COSC320
*Description: Project - 2 HashTable Dictionary that reads in words from a text file into a hash table and allows users to check if words are in the dictionary. A class decleared type "Dictionary" uses internal methods to check for suggestions on misspelled words.  
*
*
*/

private: 

	struct wordNode{
		std::string key;
		wordNode *prev = nullptr;
		wordNode *next = nullptr;
	};
	
	size_t size = 0;
	wordNode **hash;
	int buckets = 10000;
public: 

	Dictionary();
	size_t hash_f(size_t);
	void checkText(std::string, int&, int&);
	void oneEdit(std::string, int&, int&);
	void oneSuggEdits(std::string);
	size_t bucketSize();
	size_t biggestBucket();
	size_t smallestBucket();
	size_t avgBucketSize();
	double getTime();
	void insert(std::string);
	int getDictSize();
	~Dictionary();



};

#endif
