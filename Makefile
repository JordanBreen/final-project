PROGRAM=final-project.exe
CFILES=main.c sqlite_loader.c icon.c gui.c
OFILES=$(CFILES:.c=.o)
CC=gcc
CFLAGS=-g -Wall

$(PROGRAM):	$(OFILES)
	$(CC) $(CFLAGS) -o $(PROGRAM) $(OFILES) -lm -lform -lmenu -lpanel -lncursesw -lsqlite3 -lpthread

clean::
	/bin/rm $(PROGRAM) $(OFILES) *.*~ *.core
