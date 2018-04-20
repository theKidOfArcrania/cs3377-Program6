CFLAGS=-I/scrach/perkins/include -Wall -pedantic-errors
LDFLAGS=-L/scratch/perkins/lib 
LDLIBS=-lcdk -lcurses

OBJS=prog5.o

prog5: $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)

