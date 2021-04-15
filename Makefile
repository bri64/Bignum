CC = gcc
CFLAGS = -Wall -O3
DFLAGS = -Wall -Og -g
LIBS = -lm

EXE=main
SRC=$(wildcard *.c)
DEPS=$(wildcard *.h)
OBJ=$(SRC:.c=.o)
DOBJ=$(SRC:.c=.od)

all: main clean

debug: dmain clean

run: main clean
	./$(EXE)

test: main clean
	valgrind ./$(EXE)

super:
	$(CC) -o $(EXE) $(SRC)

main: $(OBJ)
	$(CC) -o $(EXE) $^ $(CFLAGS) $(LIBS)	

dmain: $(DOBJ)
	$(CC) -o $(EXE)_d $^ $(DFLAGS) $(LIBS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) $(LIBS)

%.od: %.c
	$(CC) -c -o $@ $< $(DFLAGS) $(LIBS)

clean:
	rm -f *.o
	rm -f *.od
