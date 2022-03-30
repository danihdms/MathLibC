#include <unbounded_int.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Prend un int et renvoie l'adresse d'une chaine de caractères correspondante
static char *convertIntToString(long long i){
    int n = i;
    int acc = 0;
    while(n != 0) {
        acc++;
        n = n/10;
    }
    n = i;
    char *numbers = calloc(acc, sizeof(char));
    if(numbers == NULL){
        abort();
    }
    for(int j = 0; j < acc; j++){
        numbers[j] = n % 10;
        n /= 10;
    }
    return numbers;
}

// Prend l'adresse d'une chaîne de caractères et renvoie le
// unbounded_int correspondant
unbounded_int string2unbounded_int(const char *e) {
    chiffre *premier = malloc(sizeof(chiffre));
    chiffre *dernier = malloc(sizeof(chiffre));
    premier->precedent = NULL;
    dernier->suivant = NULL;

    chiffre *tmp = NULL;
    for(int j = 0; j < sizeof(*e)/sizeof(char); j++){
        chiffre *next = malloc(sizeof(chiffre));
        next->c = e[j];
        next->precedent = tmp;
        if(tmp != NULL){
            tmp->suivant = next;
        }
        tmp = next;
    }
    char signe = '*';
    if(*e == '-') {
        signe = '-';
    } else signe = '+';
    unbounded_int res = {.signe = signe, .dernier = dernier, .premier = premier, .len = sizeof(*e)/sizeof(char)};
    if(premier == NULL || dernier == NULL){
        res.signe = '*';
        perror("Malloc a échoué");
        return res;
    }
    return res;
}

// Prend un nombre et renvoie le unbounded_int correspondant
unbounded_int ll2unbounded_int(long long i) {
    char *numbers = convertIntToString(i);
    return string2unbounded_int(numbers);
}    

// Prend en argument un unbounded_int et renvoie la chaîne de
// caractères correspondant
char *unbounded_int2string(unbounded_int i);

// Prend deux unbounded_int et les compares
// renvoie -1 si a < b, 0 si a == b et 1 si a > b
int unbounded_int_cmp_unbounded_int(unbounded_int a, unbounded_int b) {
    if(a.signe == '-' && b.signe == '+' || a.len < b.len) return -1;
    if(a.signe == '+' && b.signe == '-' || a.len > b.len) return 1;

    chiffre *tmpA = a.premier;
    chiffre *tmpB = b.premier;
    while (tmpA != NULL) {
        if(tmpA->c < tmpB->c) return -1;
        if(tmpA->c > tmpB->c) return 1;
        tmpA = tmpA->suivant;
        tmpB = tmpB->suivant;
    }
    return 0;
}

// Prend un unbounded_int et un entier et les compares
// renvoie -1 si a < b, 0 si a == b et 1 si a > b
int unbounded_int_cmp_ll(unbounded_int a, long long b);

// Prend deux unbounded_int et renvoie leur somme
unbounded_int unbounded_int_somme(unbounded_int a, unbounded_int b) {
    if(a.signe == '-' && b.signe == '+') return unbounded_int_difference(b, a);
    if(a.signe == '+' && b.signe == '-') return unbounded_int_difference(a, b);

    unbounded_int res;
    int max = a.len;
    chiffre *tmpA = a.dernier;
    chiffre *tmpB = b.dernier;
    chiffre *prev;

    if(a.len < b.len) max = b.len;
    while (tmpA != NULL && tmpB != NULL){

    }    
}

// Prend deux unbounded_int et renvoie leur différence
unbounded_int unbounded_int_difference(unbounded_int a, unbounded_int b);

// Prend deux unbounded_int et renvoie leur produit
unbounded_int unbounded_int_produit( unbounded_int a, unbounded_int b);