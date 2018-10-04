CC = gcc
CFLAGS = -O3 -Wall
LIBS = -lm
DEPS = bignum.h
OBJ = main.o bignum.o 

all: main clean
	
main: $(OBJ)
	$(CC) -o main $^ $(CFLAGS) $(LIBS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LIBS)

clean:
	rm -f *.o
