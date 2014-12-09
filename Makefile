COMPILER = gcc
CCFLAGS = -Wall -g

all: index

module1: index

wordstat.o: wordstat.c wordstat.h
	$(COMPILER) $(CCFLAGS) -c wordstat.c wordstat.h

main.o: main.c
	$(COMPILER) $(CCFLAGS) -c main.c

index: main.o
	$(COMPILER) $(CCFLAGS) -o index main.o


clean:
	rm -f *.o
	rm -f index
	rm -f *.h.gch
