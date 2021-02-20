# Dictionary with Spellchecker
This is a project that I created for my Advanced Data Structures and Algorithms class (Spring 2019). The program reads in data from a dictionary file containing 122,809 words ("english.txt") and parses the words to remove punctuation marks. After parsing, all of the words are stored in a hash table using a hashing algorithm to provide unique keys. The main program will prompt the user to type in a word and determine if the word is in the dictionary or not. If it is, the user will be told so and the statistics for lookup time with the table information will be provided. If the word is not in the dictionary, then the user will be told so and the program will output words that are within a one-edit distance of the original word. So if you type in "helt", that will not be in the dictionary; results for one-edit distance will eb words like "help", "helm", "hell".



# Sample Output
Make sure the program is compiled first by running the 'make' command; the object file will be 'dict'.
```console
your_bash:~$ ./dict

```
![Alt text](https://github.com/MalikCoderGreen/dictionary_with_spellchecker/blob/main/Picture1.png?raw=true "Dictionary program screenshot")

