CC = gcc
FLAGS =-g -O2 -w -rdynamic -I . -ldl
LDLIBS=-lpthread

all: dl dll

dl: dl.c csapp.o
	$(CC) $(FLAGS) -o dl dl.c csapp.o

dll:
	(cd dll; make)


csapp.o:
	$(CC) $(BASEFLAGS) -c csapp.c

clean:
	rm -f *.o base dl *.so *~
	(cd dll; make clean)
