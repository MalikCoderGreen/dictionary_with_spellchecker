dict: main.o Dictionary.o
	g++ -o dict main.o Dictionary.o

main.o: main.cpp Dictionary.h
	g++ -std=c++11 -c -Wall -g main.cpp

Dictionary.o: Dictionary.cpp Dictionary.h
	g++ -std=c++11 -c -Wall -g Dictionary.cpp

clean: 
	rm -f dict*.o
	

rebuild: 
	make clean
	make
