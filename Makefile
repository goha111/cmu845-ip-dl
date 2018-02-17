CC = gcc
FLAGS =-g -O3 -w -rdynamic -I . -ldl
LDLIBS=-pthread

all: dl cgi

dl: dl.c csapp.o cache.o
	$(CC) $(LDLIBS) $(FLAGS) -o dl dl.c csapp.o cache.o -ldl

cgi:
	(cd cgi-bin; make)

csapp.o:
	$(CC) $(FLAGS) -c csapp.c

cache.o:
	$(CC) $(FLAGS) -c cache.c

clean:
	rm -f *.o dl *.so *~
	(cd cgi-bin; make clean)
