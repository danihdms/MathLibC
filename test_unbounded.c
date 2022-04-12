/* Contient les tests des fonctions définies dans unbounded_int.c */
#include "unbounded_int.h"

/* Lignes pour compiler le programme (en attendant d'écrire le Makefile) :

gcc -g -Wall -c -o unbounded_int.o unbounded_int.c
gcc -g -Wall -c -o test_unbounded.o test_unbounded.c 
gcc test_unbounded.o unbounded_int.o -o programme

Le fichier exécutable sera "programme".
*/

int main(int argc, char const *argv[]) {
    unbounded_int a = string2unbounded_int("10");
    unbounded_int b = ll2unbounded_int(12);
    int c = -40;
    char *texteA = unbounded_int2string(a);
    char *texteB = unbounded_int2string(b);
    printf("a = %s\nb = %s\n", texteA, texteB);

    printf("compare %s et %s : %d\n", texteA, texteB, unbounded_int_cmp_unbounded_int(a, b));
    printf("compare %s et %d : %d\n", texteA, c, unbounded_int_cmp_ll(a, c));
    printf("%s + %s = %s\n", texteA, texteB, unbounded_int2string(unbounded_int_somme(a, b)));
    printf("%s - %s = %s\n", texteA, texteB, unbounded_int2string(unbounded_int_difference(a, b)));
    printf("%s * %s = %s\n", texteA, texteB, unbounded_int2string(unbounded_int_produit(a, b)));
    return 0;
}
