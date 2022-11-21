# Sample Makefile to compile C programs

CC = gcc
CFLAGS = -Wall -g #replace -g with -O when not debugging

DEPS	= queue.h Makefile
OBJS	= queue.o qdriver.o jobs.o

EXECS	= mysched

all:	$(EXECS)

%.o:	%.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

mysched:	$(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:	
	rm -f *.o $(EXECS)

