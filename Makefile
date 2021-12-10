PROGRAM=final-project.exe
CFILES=main.c class.c descriptor.c gui.c id_group.c range.c school.c spell.c spell_level.c subschool.c sqlite_loader.c time_unit.c
OFILES=$(CFILES:.c=.o)
CC=gcc
CFLAGS=-g -Wall

$(PROGRAM):	$(OFILES)
	$(CC) $(CFLAGS) -o $(PROGRAM) $(OFILES) -lm -lform -lmenu -lpanel -lncursesw -lsqlite3 -lpthread

clean::
	/bin/rm $(PROGRAM) $(OFILES) *.*~ *.core
