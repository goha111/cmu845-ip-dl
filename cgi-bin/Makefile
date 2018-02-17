CC = gcc
CFLAGS = -Wall -O3 -fPIC -shared -I ..

all: adder minus mul

adder: adder.c csapp.o
	$(CC) $(CFLAGS) -o adder.so adder.c csapp.o

minus: minus.c csapp.o
	$(CC) $(CFLAGS) -o minus.so minus.c csapp.o

mul: mul.c csapp.o
	$(CC) $(CFLAGS) -o mul.so mul.c csapp.o

csapp.o:
	$(CC) $(CFLAGS) -c csapp.c

clean:
	rm -f *.so
	rm -f *.o