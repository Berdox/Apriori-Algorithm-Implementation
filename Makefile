CC = g++
CFLAGS = -std=c++17 -O2 -Wall

all: Apriori Idea1 GenDatabase
	$(RM) *.o *.d

# Apriori main program
Apriori: main_apriori.o Apriori.o
	$(CC) $(CFLAGS) -o Apriori main_apriori.o Apriori.o

main_apriori.o: ./src/main_apriori.cpp ./include/Apriori.h
	$(CC) $(CFLAGS) -c ./src/main_apriori.cpp

Apriori.o: ./src/Apriori.cpp ./include/Apriori.h
	$(CC) $(CFLAGS) -c ./src/Apriori.cpp

# Idea1 main program
Idea1: main_idea1.o Apriori.o Idea1.o
	$(CC) $(CFLAGS) -o Idea1 main_idea1.o Apriori.o Idea1.o

main_idea1.o: ./src/main_idea1.cpp ./include/Apriori.h ./include/Idea1.h
	$(CC) $(CFLAGS) -c ./src/main_idea1.cpp

Idea1.o: ./src/Idea1.cpp ./include/Idea1.h
	$(CC) $(CFLAGS) -c ./src/Idea1.cpp

# Generator main program
GenDatabase: GenDatabase.o
	$(CC) $(CFLAGS) -o GenDatabase GenDatabase.o

GenDatabase.o: ./src/GenDatabase.cpp
	$(CC) $(CFLAGS) -c ./src/GenDatabase.cpp

# Clean directory
clean:
	$(RM) Apriori GenDatabase Idea1 *.o *.d
