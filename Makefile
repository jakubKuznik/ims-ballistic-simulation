CC = g++

CFLAGS = -g -Wpedantic -Wall -Wextra 
all: simulation 

##########################################################################

simulation: simulation.cpp simulation.hpp 
	gcc $(CFLAGS) -c simulation.cpp -o simulation


clean:
	rm *.o simulation 
