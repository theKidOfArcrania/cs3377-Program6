CFLAGS=-I/scrach/perkins/include -Wall -pedantic-errors
#LDFLAGS=-L/scratch/perkins/lib  # Screw this... I installed it on my own machine
LDLIBS=-lcdk -lcurses

OBJS=prog5.o

prog5: $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)

