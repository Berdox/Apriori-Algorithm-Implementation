CC = g++
CFLAGS = -O2 -Wall

all: apriori idea1 gen

# Apriori main program
apriori: main_apriori.o apriori.o
	$(CC) $(CFLAGS) -o apriori main_apriori.o apriori.o

main_apriori.o: ./src/main_apriori.cpp ./include/Apriori.h
	$(CC) $(CFLAGS) -c ./src/main_apriori.cpp

apriori.o: ./src/Apriori.cpp ./include/Apriori.h
	$(CC) $(CFLAGS) -c ./src/Apriori.cpp

# Idea1 main program
idea1: main_idea1.o apriori.o idea1.o
	$(CC) $(CFLAGS) -o idea1 main_idea1.o apriori.o idea1.o

main_idea1.o: ./src/main_idea1.cpp ./include/Apriori.h ./include/Idea1.h
	$(CC) $(CFLAGS) -c ./src/main_idea1.cpp

idea1.o: ./src/Idea1.cpp ./include/Idea1.h
	$(CC) $(CFLAGS) -c ./src/Idea1.cpp

# Generator main program
gen: gen.o
	$(CC) $(CFLAGS) -o gen gen.o

gen.o: ./src/gen.cpp
	$(CC) $(CFLAGS) -c ./src/gen.cpp

# Clean directory
clean:
	$(RM) apriori gen idea1 *.o *.d
