#include "unbounded_int.h"

int main(int argc, char const *argv[]) {
    unbounded_int a = string2unbounded_int("89");
    unbounded_int b = ll2unbounded_int(89);
    int c = -40;
    char *texteA = unbounded_int2string(a);
    char *texteB = unbounded_int2string(b);
    printf("a = %s\nb = %s\n", texteA, texteB);

    printf("compare %s et %s : %d\n", texteA, texteB, unbounded_int_cmp_unbounded_int(a, b));
    printf("compare %s et %d : %d\n", texteA, c, unbounded_int_cmp_ll(a, c));
    //printf("%s + %s = %s\n", texteA, texteB, unbounded_int2string(unbounded_int_somme(a, b)));
    //printf("%s - %s = %s\n", texteA, texteB, unbounded_int2string(unbounded_int_difference(a, b)));
    printf("%s * %s = %s\n", texteA, texteB, unbounded_int2string(unbounded_int_produit(a, b)));
    //printf("%s / %s = %s\n", texteA, texteB, unbounded_int2string(unbounded_int_division(a, b)));

    return 0;
}
