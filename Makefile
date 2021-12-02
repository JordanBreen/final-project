PROGRAM=final-project.exe
CFILES=main.c gui.c spell.c sqlite_loader.c time_unit.c log2.c
OFILES=$(CFILES:.c=.o)
CC=gcc
CFLAGS=-g -Wall

$(PROGRAM):	$(OFILES)
	$(CC) $(CFLAGS) -o $(PROGRAM) $(OFILES) -lm -lform -lmenu -lpanel -lncursesw -lsqlite3 -lpthread

clean::
	/bin/rm $(PROGRAM) $(OFILES) *.*~ *.core
