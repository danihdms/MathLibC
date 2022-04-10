programme : test_unbounded.o unbounded_int.o
	gcc test_unbounded.o unbounded_int.o -o programme

test_unbounded.o : test_unbounded.c unbounded_int.h
	gcc -g -Wall -c -o test_unbounded.o test_unbounded.c 

unbounded_int.o : unbounded_int.c unbounded_int.h
	gcc -g -Wall -c -o unbounded_int.o unbounded_int.c
	
