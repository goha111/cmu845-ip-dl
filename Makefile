CC = gcc
FLAGS =-g -O2 -w -rdynamic -I . -ldl
LDLIBS=-lpthread

all: dl cgi

dl: dl.c csapp.o cache.o
	$(CC) $(FLAGS) -o dl dl.c csapp.o cache.o

cgi:
	(cd cgi-bin; make)

csapp.o:
	$(CC) $(FLAGS) -c csapp.c

cache.o:
	$(CC) $(FLAGS) -c cache.c

clean:
	rm -f *.o dl *.so *~
	(cd cgi-bin; make clean)
