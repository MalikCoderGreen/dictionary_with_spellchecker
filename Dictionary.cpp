#include "Dictionary.h"
#include <string>
#include <fstream>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <stdlib.h>


/*
*
*Name : Maliak Green
*Course: COSC320
*Description: Project - 2 HashTable Dictionary that reads in words from a text file into a hash table and allows users to check if words are in the dictionary. A class decleared type "Dictionary" uses internal methods to check for suggestions on misspelled words.  
*
*
*/

Dictionary::Dictionary(){

	std::ifstream input("english.txt", std::ios::in);
	std::string word;
	while(std::getline(input, word))
		size++;



	hash = new wordNode*[buckets];

	for(size_t i = 0; i < buckets; i++){
		hash[i] = nullptr;

	}



	input.clear();
	input.seekg(0);
	size_t i = 0;


	while(std::getline(input, word)){
		insert(word);				
		i++;	
	}
}

/*
Function to record lookup time for statistical output.
*/
double Dictionary::getTime(){

	auto start = std::chrono::system_clock::now();

	Dictionary time;

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start; 

	return elapsed_seconds.count();
}


/*
Create unique hash key for dictionary words.
*/
size_t Dictionary::hash_f(size_t u){

	size_t w = 30;
	size_t p = 13;
	size_t a = 187;
	size_t W = 1 << w;

	return (a * u % W) >> (w - p);

}



int Dictionary::getDictSize(){
	return size;
}

/*
Insert words from dictionary object into the hash table.
*/
void Dictionary::insert(std::string word){

	size_t numWord[word.length()];
	size_t hashed = 0;
	for(size_t i = 0; i < word.length(); i++){
		size_t tmp = size_t(word[i]);
		numWord[i] = tmp;
	}

	for(size_t i = 0; i < word.length(); i++){


		numWord[i] = numWord[i] << (7 * i);
		hashed += numWord[i];
	}



	size_t index = hash_f(hashed);

	wordNode *x = new wordNode;

	x->next = hash[index];
	x->key = word;

	hash[index] = x;
	if(x->next){
		x->next->prev = x;
	} 
}

/*
Below are functions that record various bucket sizes within the hash table: 
biggestBucket()
smallestBucket()
avgBucketSize()
bucketSize()
*/
//BUCKET GETTER FUNCTIONS.
//************************************************************************
size_t Dictionary::biggestBucket(){

	size_t maxBucket = 0;

	size_t currentBucket = 0;
	for(int i = 0; i < buckets; i++){
		if(hash[i]){
			wordNode *cursor = hash[i];
			while(cursor){
				currentBucket++;
				cursor = cursor->next;
			}

			if(maxBucket < currentBucket)
				maxBucket = currentBucket;

			currentBucket = 0;
		}
	}

	return maxBucket;
}



size_t Dictionary::smallestBucket(){

	size_t smallestBucket = 0;
	size_t currentBucket = 0;
	for(int i = 0; i < buckets; i++){
		if(hash[i]){

			wordNode *cursor = hash[i];
			while(cursor){
				currentBucket++;
				cursor = cursor->next;
			}

			if(i == 0)
				smallestBucket = currentBucket;

			if(smallestBucket > currentBucket && i > 0)
				smallestBucket = currentBucket;

			currentBucket = 0;
		}
	}

	return smallestBucket;

}


size_t Dictionary::avgBucketSize(){

	size_t avgNodes = 0;
	size_t totalNodes = 0;
	for(size_t i = 0; i < buckets; i++){
		if(hash[i]){
			wordNode *cursor = hash[i];
			while(cursor){
				totalNodes++;
				cursor = cursor->next;
			}

		}
	}

	avgNodes = totalNodes / bucketSize();

	return avgNodes;
}
size_t Dictionary::bucketSize(){
	size_t bSize = 0;

	for(size_t i = 0; i < buckets; i++){

		if(hash[i]){
			bSize++;
		}	
		/*
		   while(cursor->next){
		   cursor = cursor->next;
		   }*/

	}

	return bSize;

}
//************************************************************************

/*
Function to check if the given word by the user is in the hash table. 
If it isn't, oneEdit() will be called to show words that are one edit distance away.
*/
void Dictionary::checkText(std::string text, int &misspelled, int &suggestions){

	bool isIn = false;
	for(size_t i = 0; i < buckets; i++){
		if(hash[i]){

			wordNode *cursor = hash[i];
			while(cursor){

				if(cursor->key == text)
					isIn = true;

				cursor = cursor->next;
			}	

		}
	}


	if(!isIn)
		oneEdit(text, misspelled, suggestions);

	else
		std::cout << text << " is in the dictionary!\n\n";
}

/*
Function to show words that are one edit distance away from the given word. 
*/
void Dictionary::oneEdit(std::string text, int &misspelled, int &suggestions){
	
	misspelled++;
	std::cout <<"\033[31m" << text << "\033[0m" << " is misspelled! Below are the words within one edit distance. ";
	std::cout << "************************************************";
	std::cout << "\n\nOne Edit Suggestions for " <<"\033[31m" << text <<"\033[0m" << ":\n\n ";
	for(size_t i = 0; i < buckets; i++){
		if(hash[i]){
			wordNode *cursor = hash[i];
			while(cursor){

				// i) replacing one character.	
				if(cursor->key.length() == text.length()){
					int offByOne = 0;
					for(int i = 0; i < text.length(); i++){
						if(cursor->key[i] == text[i])
							offByOne++;
					}

					if(offByOne == text.length() - 1){
						suggestions++;
						std::cout << "\n " << cursor->key << "\n";

						oneSuggEdits(cursor->key);
					}
			}
				cursor = cursor->next;

				
			}

		}

	}
	if(suggestions == 0)
		std::cout << "Sorry there where no matches for the word " << "\033[31m" << text << "\033[0m" << std::endl;

	std::cout << "\n";
}


void Dictionary::oneSuggEdits(std::string text){
	std::cout << "Here are the words within two edit distances of the original word \n";
	std::cout << "**************************************************\n";
	std::cout << "Suggestions for " << text << "\n\n";
	for(size_t i = 0; i < buckets; i++){
		if(hash[i]){
			wordNode *cursor = hash[i];
			while(cursor){




				// i) replacing one character.	
				if(cursor->key.length() == text.length()){
					int offByOne = 0;
					for(int i = 0; i < text.length(); i++){
						if(cursor->key[i] == text[i])
							offByOne++;
					}

					if(offByOne == text.length() - 1){
						std::cout << "\n " << cursor->key << " ";
					}
				}
				cursor = cursor->next;

				
			}
	}
	
	}
	std::cout << "\n\n";
}

Dictionary::~Dictionary(){

	for(size_t i = 0; i < buckets; i++){

	wordNode *cursor = hash[i];
		while(cursor){
			wordNode *next = cursor->next;
			delete cursor;
			cursor = next;
		}
	}

	delete [] hash;

}
