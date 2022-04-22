CC = gcc
CFLAGS = -Wall -g -pedantic
LDLIBS = -lm


programme : test_unbounded.o unbounded_int.o
	$(CC) test_unbounded.o unbounded_int.o -o programme $(LDLIBS)

test_unbounded.o : test_unbounded.c unbounded_int.h
	$(CC) $(CFLAGS) -c -o test_unbounded.o test_unbounded.c

unbounded_int.o : unbounded_int.c unbounded_int.h
	$(CC) -c $(CFLAGS) -o unbounded_int.o unbounded_int.c

clean :
	rm -f *.o programme
