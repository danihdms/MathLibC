CC = gcc
CFLAGS = -Wall -g -pedantic
LDLIBS = -lm
ALL = programme calc_unbounded_int

all : $(ALL)

programme : test_unbounded.o unbounded_int.o
	$(CC) test_unbounded.o unbounded_int.o -o programme $(LDLIBS)

calc_unbounded_int : calc_unbounded_int.o unbounded_int.o hashmap.o liste_lettre.o liste_mot.o
	$(CC) calc_unbounded_int.o unbounded_int.o hashmap.o liste_lettre.o liste_mot.o -o calc_unbounded_int $(LDLIBS)


test_unbounded.o : test_unbounded.c unbounded_int.h
	$(CC) $(CFLAGS) -c -o test_unbounded.o test_unbounded.c

unbounded_int.o : unbounded_int.c unbounded_int.h
	$(CC) -c $(CFLAGS) -o unbounded_int.o unbounded_int.c


calc_unbounded_int.o : calc_unbounded_int.c hashmap.h liste_lettre.h liste_mot.h
	$(CC) -c $(CFLAGS) -o calc_unbounded_int.o calc_unbounded_int.c

hashmap.o : hashmap.c hashmap.h
	$(CC) -c $(CFLAGS) -o hashmap.o hashmap.c

liste_lettre.o : liste_lettre.c liste_lettre.h
	$(CC) -c $(CFLAGS) -o liste_lettre.o liste_lettre.c

liste_mot.o : liste_mot.c liste_mot.h
	$(CC) -c $(CFLAGS) -o liste_mot.o liste_mot.c


clean :
	rm -f *.o programme
