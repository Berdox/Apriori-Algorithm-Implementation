CC = g++
CFLAGS = -O2 -Wall

all: apriori gen

# Apriori main program
apriori: main.o apriori.o
	$(CC) $(CFLAGS) -o apriori main.o apriori.o

main.o: ./src/main.cpp ./include/Apriori.h
	$(CC) $(CFLAGS) -c ./src/main.cpp

apriori.o: ./src/Apriori.cpp ./include/Apriori.h
	$(CC) $(CFLAGS) -c ./src/Apriori.cpp

# Generator main program
gen: gen.o
	$(CC) $(CFLAGS) -o gen gen.o

gen.o: ./src/gen.cpp
	$(CC) $(CFLAGS) -c ./src/gen.cpp

# Clean directory
clean:
	$(RM) apriori gen *.o *.d
