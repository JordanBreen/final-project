CC=gcc -lncurses -g -Wall
CFILES= main.c
OFILES=$(CFILES:.c=.o)
main:	$(OFILES)
	$(CC) -o main $(OFILES)
main.o:
.c.o:
	$(CC) -c $<
clean::
	/bin/rm $(OFILES) main
