/* Contient les tests des fonctions définies dans unbounded_int.c */
#include "unbounded_int.h"

/* Lignes pour compiler le programme (en attendant d'écrire le Makefile) :

gcc -g -Wall -c -o unbounded_int.o unbounded_int.c
gcc -g -Wall -c -o test_unbounded.o test_unbounded.c 
gcc test_unbounded.o unbounded_int.o -o programme

Le fichier exécutable sera "programme".
*/

int main(int argc, char const *argv[]) {
    printf("Appel à string2unbounded_int\n");
    unbounded_int a = string2unbounded_int("3");
    printf("Fin d'appel à string2unbounded_int\n");
    unbounded_int b = ll2unbounded_int(5);
    char *texteA = unbounded_int2string(a);
    //char *texteB = unbounded_int2string(b);
    //printf("a = %s\nb = %s", texteA, texteB);
    return 0;
}
