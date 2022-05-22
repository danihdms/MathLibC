#include "unbounded_int.h"

int main(int argc, char const *argv[]) {
    unbounded_int a = string2unbounded_int("19456787654345678909876545678567893");
    unbounded_int b = ll2unbounded_int(-0);
    unbounded_int c = string2unbounded_int("-5");
    unbounded_int d = ll2unbounded_int(-5);
    unbounded_int e = ll2unbounded_int(56);



    char *texteA = unbounded_int2string(a);
    char *texteB = unbounded_int2string(b);
    char *texteC = unbounded_int2string(c);
    char *texteD = unbounded_int2string(d);
    char *texteE = unbounded_int2string(e);



    printf("a = %s\nb = %s\nc = %s\nd = %s\n", texteA, texteB, texteC, texteD);

    printf("compare %s et %s : %d\n", texteB, texteA, unbounded_int_cmp_unbounded_int(b, a));
    printf("compare %s et %s : %d\n", texteB, texteC, unbounded_int_cmp_unbounded_int(b, c));
    printf("compare %s et %s : %d\n\n", texteC, texteD, unbounded_int_cmp_unbounded_int(c, d));

    printf("compare %s et %d : %d\n", texteA, -5, unbounded_int_cmp_ll(a, -5));
    printf("compare %s et %d : %d\n", texteB, 10, unbounded_int_cmp_ll(b, 10));
    printf("compare %s et %d : %d\n\n", texteC, -5, unbounded_int_cmp_ll(c, -5));



    printf("%s + %s = %s\n", texteA, texteB, unbounded_int2string(unbounded_int_somme(a, b)));
    printf("%s + %s = %s\n", texteB, texteC, unbounded_int2string(unbounded_int_somme(b, c)));
    printf("%s + %s = %s\n\n", texteD, texteC, unbounded_int2string(unbounded_int_somme(d, c)));


    printf("%s - %s = %s\n", texteA, texteB, unbounded_int2string(unbounded_int_difference(a, b)));
    printf("%s - %s = %s\n", texteB, texteE, unbounded_int2string(unbounded_int_difference(b, e)));
    printf("%s - %s = %s\n", texteE, texteB, unbounded_int2string(unbounded_int_difference(e, b)));
    printf("%s - %s = %s\n\n", texteC, texteE, unbounded_int2string(unbounded_int_difference(c, e)));

    printf("%s * %s = %s\n", texteA, texteB, unbounded_int2string(unbounded_int_produit(a, a)));
    printf("%s * %s = %s\n", texteC, texteA, unbounded_int2string(unbounded_int_produit(c, a)));
    printf("%s * %s = %s\n\n", texteB, texteA, unbounded_int2string(unbounded_int_produit(b, a)));

    printf("%s / %s = %s\n", texteA, texteB, unbounded_int2string(unbounded_int_division(a, b)));
    printf("%s / %s = %s\n", texteA, texteE, unbounded_int2string(unbounded_int_division(a, e)));
    printf("%s / %s = %s\n\n", texteA, texteC, unbounded_int2string(unbounded_int_division(a, c)));

    return 0;
}
