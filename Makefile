CFLAGS=-I/scrach/perkins/include -Wall -pedantic-errors
#LDFLAGS=-L/scratch/perkins/lib  # Screw this... I installed it on my own machine
LDLIBS=-lcdk -lcurses

OBJS=prog6.o binio.o

prog6: $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)

