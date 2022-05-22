CC = gcc
CFLAGS = -Wall -g -pedantic
LDLIBS = -lm
ALL = programme calc_unbounded_int

all : $(ALL)

programme : test_unbounded.o unbounded_int.o
	$(CC) test_unbounded.o unbounded_int.o -o programme $(LDLIBS)

calc_unbounded_int : calc_unbounded_int.o unbounded_int.o 
	$(CC) calc_unbounded_int.o unbounded_int.o -o calc_unbounded_int $(LDLIBS)


test_unbounded.o : test_unbounded.c unbounded_int.h
	$(CC) $(CFLAGS) -c -o test_unbounded.o test_unbounded.c

unbounded_int.o : unbounded_int.c unbounded_int.h
	$(CC) -c $(CFLAGS) -o unbounded_int.o unbounded_int.c


calc_unbounded_int.o : calc_unbounded_int.c unbounded_int.h
	$(CC) -c $(CFLAGS) -o calc_unbounded_int.o calc_unbounded_int.c


clean :
	rm -f *.o programme
