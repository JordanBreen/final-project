CC=gcc -g -Wall
CFILES= main.c sqlite_loader.c
OFILES=$(CFILES:.c=.o)
main:	$(OFILES)
	$(CC) -o main $(OFILES) -lncurses -lsqlite3 -std=c99
main.o:
.c.o:
	$(CC) -c $<
clean::
	/bin/rm $(OFILES) main
