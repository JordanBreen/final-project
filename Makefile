PROGRAM=program
CFILES=main.c sqlite_loader.c
OFILES=$(CFILES:.c=.o)
CC=gcc
CFLAGS=-g -Wall

$(PROGRAM):	$(OFILES)
	$(CC) $(CFLAGS) -o $(PROGRAM) $(OFILES) -lm -lncurses -lsqlite3 -lpthread

clean::
	/bin/rm $(PROGRAM) $(OFILES)
