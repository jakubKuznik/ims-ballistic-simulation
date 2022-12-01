CC = g++

CFLAGS = -g -Wpedantic -Wall -Wextra 
all: simulation 

##########################################################################

simulation: simulation.cpp 
	g++ $(CFLAGS) -o simulation simulation.cpp -lsimlib -lm 

clean:
	rm *.o simulation 
