CC = gcc 
CFLAGS = 
LFLAGS = 

SOURCEDIR = src/
INCDIR = inc/
OBJDIR = obj/

OBJS = connect4.o gameMoves.o board.o point.o
EXECUTABLE = connect4

MFLAGS = -w

default: all objs

all: $(OBJS) Makefile
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJS) $(LFLAGS)


%.c: $(INCDIR)%.h
	
%.o: $(SOURCEDIR)%.c
	$(CC) $(CFLAGS) -c -o $@ $<

objs:
	mv *.o $(OBJDIR)

clean: 
	rm -f $(OBJDIR)*.o $(EXECUTABLE)