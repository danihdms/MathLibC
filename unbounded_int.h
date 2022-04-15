#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

typedef struct chiffre {
    struct chiffre *suivant;
    char c;
    struct chiffre *precedent;
} chiffre;

typedef struct {
    char signe;
    size_t len;
    chiffre *premier;
    chiffre *dernier;
} unbounded_int;

// Prend une chaîne de caractères et renvoie l'unbounded_int correspondant
extern unbounded_int string2unbounded_int(const char *e);

// Prend un nombre et renvoie l'unbounded_int correspondant
extern unbounded_int ll2unbounded_int(long long i);

// Prend un unbounded_int et renvoie la chaîne de caractères correspondante
extern char *unbounded_int2string(unbounded_int i);

// Prend deux unbounded_int et les compare.
// Renvoie -1 si a < b, 0 si a == b et 1 si a > b
extern int unbounded_int_cmp_unbounded_int(unbounded_int a, unbounded_int b);

// Prend un unbounded_int et un entier et les compare.
// Renvoie -1 si a < b, 0 si a == b et 1 si a > b
extern int unbounded_int_cmp_ll(unbounded_int a, long long b);

// Prend deux unbounded_int et renvoie leur somme
extern unbounded_int unbounded_int_somme(unbounded_int a, unbounded_int b);

// Prend deux unbounded_int et renvoie leur différence
extern unbounded_int unbounded_int_difference(unbounded_int a, unbounded_int b);

// Prend deux unbounded_int et renvoie leur produit
extern unbounded_int unbounded_int_produit( unbounded_int a, unbounded_int b);