PROGRAM = hero
CC      = gcc
CFLAGS  = -Wall
LDLIBS  = -lglut -lGLU -lGL -lm

$(PROGRAM): hero.o main.o colors.o image.o
	$(CC) -o $(PROGRAM) hero.o main.o colors.o image.o $(CFLAGS) $(LDLIBS)

.PHONY: clean

clean: 
	-rm *.o $(PROGRAM)