#include "unbounded_int.h"

// Prend un entier et renvoie l'adresse de la chaîne de caractères correspondante.
// La chaîne de caractères ne contient pas le signe de l'entier.
static char *int2string(long long i) {
    if (i == 0) return "0";
    int acc = log10(abs(i)) + 1;
    int n = abs(i);
    printf("%lld %d\n", i, acc);
    char *numbers = calloc(acc, sizeof(char));
    if(numbers == NULL){
        perror("int2string : calloc a échoué");
        exit(1);
    }
    for(int j = acc - 1; j > -1; j--){
        numbers[j] = n % 10 + '0';
        n /= 10;
    }
    return numbers;
}

// Prend un unbounded_int et un caractère et ajoute ce caractère en dernière position
// l'unbounded_int
static unbounded_int ajoute_dernier(unbounded_int i, char e) {
    chiffre *ajout = malloc(sizeof(chiffre));
    if (ajout == NULL) {
        perror("ajoute_dernier : malloc a échoué");
        exit(1);
    }
    ajout->c = e;
    ajout->suivant = NULL;
    
    if (i.dernier == NULL) {
        ajout->precedent = NULL;
        i.premier = ajout;
    } else {
        ajout->precedent = i.dernier;
        i.dernier->suivant = ajout;
    }

    i.dernier = ajout;
    i.len++;
    return i;
}

// Prend un unbounded_int et supprime son premier chiffre
static unbounded_int supprime_premier(unbounded_int i) {
    if (i.premier == NULL) return i;
    unbounded_int res = {.signe = i.signe, .len = 0, .premier = NULL, .dernier = NULL};
    chiffre *tmp = i.premier->suivant;
    while (tmp != NULL) {
        res = ajoute_dernier(res, tmp->c);
        tmp = tmp->suivant;
    }
    return res;
}

// Prend un unbounded_int et supprime tous les zéro inutiles
static unbounded_int supprime_zero_inutile(unbounded_int i) {
    unbounded_int res = {.len = i.len, .signe = i.signe, .premier = i.premier, .dernier = i.dernier};
    if(i.premier == NULL) return res;
    while(res.len > 0 && res.premier->c == '0') {
        res = supprime_premier(res);
    }
    return res;
}

// Prend un unbounded_int et un caractère et ajoute ce caractère en première position
// de l'unbounded_int
static unbounded_int ajoute_premier(unbounded_int i, char e) {
    chiffre *ajout = malloc(sizeof(chiffre));
    if (ajout == NULL) {
        perror("ajoute_premier : malloc a échoué");
        exit(1);
    }
    ajout->c = e;
    ajout->precedent = NULL;
    
    if (i.premier == NULL) {
        ajout->suivant = NULL;
        i.dernier = ajout;
    } else {
        ajout->suivant = i.premier;
        i.premier->precedent = ajout;
    }

    i.premier = ajout;
    i.len++;
    return i;
}

// Prend un unbounded_int et renvoie sa valeur absolue
static unbounded_int unbounded_int_abs(unbounded_int i) {
    unbounded_int res = {.len = i.len, .signe = '+', .premier = NULL, .dernier = NULL};
    chiffre *tmp = i.premier;
    while (tmp != NULL) {
        res = ajoute_dernier(res, tmp->c);
        tmp = tmp->suivant;
    }
    return res;
}

// Copie un unbounded int
static unbounded_int unbounded_int_copie(unbounded_int i) {
    unbounded_int res = {.len = i.len, .signe = i.signe, .premier = NULL, .dernier = NULL};
    chiffre *tmp = i.premier;
    while (tmp != NULL) {
        res = ajoute_dernier(res, tmp->c);
        tmp = tmp->suivant;
    }
    return res;
}

// Prend un unbounded_int et renvoie son opposé
static unbounded_int unbounded_int_oppose(unbounded_int i) {
    char signe = '+';
    if (i.signe == '+') signe = '-';
    unbounded_int res = {.len = i.len, .signe = signe, .premier = NULL, .dernier = NULL};
    chiffre *tmp = i.premier;
    while (tmp != NULL) {
        res = ajoute_dernier(res, tmp->c);
        tmp = tmp->suivant;
    }
    return res;
}


// Prend une chaîne de caractères et renvoie l'unbounded_int correspondant
unbounded_int string2unbounded_int(const char *e) {
    int j = 0;
    char signe = '*';
    if (*e == '-') {
        signe = '-';
        j = 1;
    } else if (*e == '+') {
        signe = '+';
        j = 1;
    } else signe = '+';
    unbounded_int res = {.signe = signe, .len = 0, .premier = NULL, .dernier = NULL};

    for(int i = j; i < strlen(e); i++) {
        if (isdigit(e[i]) == 0) {
            res.signe = '*';
            return res;
        }
        res = ajoute_dernier(res, e[i]);
    }
    return res;
}

// Prend un nombre et renvoie l'unbounded_int correspondant
unbounded_int ll2unbounded_int(long long i) {
    char *numbers = int2string(i);
    unbounded_int res = string2unbounded_int(numbers);
    res.signe = (i < 0) ? '-' : '+';
    return res;
}    

// Prend un unbounded_int et renvoie la chaîne de caractères correspondante
char *unbounded_int2string(unbounded_int i) {
    if (i.premier == NULL) {
        char *res = calloc(2, sizeof(char));
        if (res == NULL) {
            perror("unbounded_int2string : calloc a échoué");
            exit(1);
        }
        res[0] = '0';
        res[1] = '\0';
        return res;
    }
    char *res;
    if (i.signe == '+') res = calloc(i.len + 1, sizeof(char));
    else res = calloc(i.len + 2, sizeof(char));
    if (res == NULL) {
        perror("unbounded_int2string : calloc a échoué");
        exit(1);
    }

    chiffre *tmp = i.premier;
    for (int n = 0; n < i.len; n++) {
        if (i.signe == '+') res[n] = tmp->c;
        else res[n + 1] = tmp->c;
        tmp = tmp->suivant;
    }

    if (i.signe == '+') {
        res[i.len] = '\0';
    } else {
        res[0] = '-';
        res[i.len + 1] = '\0';
    }
    return res;
}

// Prend deux unbounded_int et les compare.
// Renvoie -1 si a < b, 0 si a == b et 1 si a > b
int unbounded_int_cmp_unbounded_int(unbounded_int a, unbounded_int b) {
    if (a.signe == '*' || b.signe == '*') return -2;
    if((a.signe == '-' && b.signe == '+') || (a.len > b.len && (a.signe == '-' && b.signe == '-')) || a.len < b.len) return -1;
    if((a.signe == '+' && b.signe == '-') || (a.len < b.len && (a.signe == '-' && b.signe == '-')) || a.len > b.len) return 1;

    chiffre *tmpA = a.premier;
    chiffre *tmpB = b.premier;
    while (tmpA != NULL) {
        if(a.signe == '-' && tmpA->c < tmpB->c) return 1;
        if(a.signe == '-' && tmpA->c > tmpB->c) return -1;
        if(tmpA->c < tmpB->c) return -1;
        if(tmpA->c > tmpB->c) return 1;
        tmpA = tmpA->suivant;
        tmpB = tmpB->suivant;
    }
    return 0;
}

// Prend un unbounded_int et un entier et les compare.
// Renvoie -1 si a < b, 0 si a == b et 1 si a > b
int unbounded_int_cmp_ll(unbounded_int a, long long b) {
    if (a.signe == '*') return -2;

    char *c = int2string(b);
    if ((a.signe == '-' && b > 0) || (a.len > strlen(c) && (a.signe == '-' && b < 0)) || a.len < strlen(c)) return -1;
    if ((a.signe == '+' && b < 0) || (a.len < strlen(c) && (a.signe == '-' && b < 0)) || a.len > strlen(c)) return 1;

    chiffre *tmp = a.premier;
    for (int i = 0; i < strlen(c); i++) {
        if (a.signe == '-' && tmp->c < c[i]) return 1;
        if (a.signe == '-' && tmp->c > c[i]) return -1;
        if (tmp->c < c[i]) return -1;
        if (tmp->c > c[i]) return 1;
        tmp = tmp->suivant;
    }
    return 0;
}

// Prend deux unbounded_int et renvoie leur somme
unbounded_int unbounded_int_somme(unbounded_int a, unbounded_int b) {
    a = supprime_zero_inutile(a);
    b = supprime_zero_inutile(b);
    if(a.signe == '*' || b.signe == '*') exit(5);
    if(a.signe == '-' && b.signe == '+') return unbounded_int_difference(b, a);
    if(a.signe == '+' && b.signe == '-') return unbounded_int_difference(a, b);
    char signe = '-';
    if(a.signe == '+' && b.signe == '+') signe = '+';
    unbounded_int res = {.len = 0, .signe = signe, .dernier = NULL, .premier = NULL};
    int reste = 0;
    chiffre *tmpA = a.dernier;
    chiffre *tmpB = b.dernier;
    while(tmpA != NULL || tmpB != NULL) {
        int chiffreA, chiffreB;
        if(tmpA != NULL) chiffreA = tmpA->c - '0';
        else chiffreA = 0;
        if(tmpB != NULL) chiffreB = tmpB->c - '0';
        else chiffreB = 0;
        int somme = chiffreA + chiffreB + reste;
        res = ajoute_premier(res, somme % 10 + '0');
        reste = somme / 10;
        if(tmpA != NULL) {
            tmpA = tmpA->precedent;
        } else {
            tmpA = NULL;
        }
        if(tmpB != NULL) {
            tmpB = tmpB->precedent;
        } else {
            tmpB = NULL;
        }
    }
    if(reste != 0) res = ajoute_premier(res, reste + '0');
    return res;
}

// Prend deux unbounded_int et renvoie leur différence
unbounded_int unbounded_int_difference(unbounded_int a, unbounded_int b) {
    a = supprime_zero_inutile(a);
    b = supprime_zero_inutile(b);
    if (a.signe == '*' || b.signe == '*') exit(5);
    if ((a.signe == '+' && b.signe == '-') || (a.signe == '-' && b.signe == '+')) return unbounded_int_somme(a, unbounded_int_oppose(b));

    int compare = unbounded_int_cmp_unbounded_int(unbounded_int_abs(a), unbounded_int_abs(b));
    chiffre *tmpA, *tmpB;
    if (compare == 1) {
        tmpA = a.dernier;
        tmpB = b.dernier;
    } else if (compare == -1) {
        tmpA = b.dernier;
        tmpB = a.dernier;
    } else {
        return string2unbounded_int("0");
    }

    char signe = '+';
    if ((a.signe == '+' && compare == -1) || (a.signe == '-' && compare == 1)) signe = '-';

    unbounded_int res = {.len = 0, .signe = signe, .dernier = NULL, .premier = NULL};
    int reste = 0;

    while (tmpA != NULL) {
        int chiffreA = tmpA->c - '0';
        if (tmpB == NULL) {
            if (chiffreA >= reste) {
                res = ajoute_premier(res, '0' + (chiffreA - reste));
                reste = 0;
            } else {
                res = ajoute_premier(res, '0' + (chiffreA + 10 - reste));
                reste = 1;
            }
        } else {
            int chiffreB = tmpB->c - '0';
            if (chiffreA >= chiffreB + reste) {
                res = ajoute_premier(res, '0' + (chiffreA - chiffreB - reste));
                reste = 0;
            } else {
                res = ajoute_premier(res, '0' + (chiffreA + 10 - chiffreB - reste));
                reste = 1;
            }
        }

        tmpA = tmpA->precedent;
        if(tmpB != NULL) {
            tmpB = tmpB->precedent;
        } else {
            tmpB = NULL;
        }
    }
    res = supprime_zero_inutile(res);
    return res;
}

// Prend deux unbounded_int et renvoie leur produit
unbounded_int unbounded_int_produit(unbounded_int a, unbounded_int b) {
    if (a.signe == '*' || b.signe == '*') exit(5);
    a = supprime_zero_inutile(a);
    b = supprime_zero_inutile(b);

    char signe = '+';
    if ((a.signe == '+' && b.signe == '-') || (a.signe == '-' && b.signe == '+')) signe = '-';

    unbounded_int res = {.len = 0, .signe = signe, .premier = NULL, .dernier = NULL};
    for (int i = 0; i < a.len + b.len; i++) res = ajoute_premier(res, '0');

    chiffre *tmpB = b.dernier;
    chiffre *tmpDernier = res.dernier;
    chiffre *tmpRes = tmpDernier;
    for (int i = 0; i < b.len; i++) {
        int r = 0;
        if (tmpB->c == '0') continue;

        chiffre *tmpA = a.dernier;
        while (tmpA != NULL) {
            int v = (tmpRes->c - '0') + (tmpA->c - '0') * (tmpB->c - '0') + r;
            tmpRes->c = '0' + v % 10;
            r = v / 10;
            tmpA = tmpA->precedent;
            tmpRes = tmpRes->precedent;
        }

        if (r != 0) tmpRes->c = '0' + r;
        tmpB = tmpB->precedent;
        tmpDernier = tmpDernier->precedent;
        tmpRes = tmpDernier;
    }
    res = supprime_zero_inutile(res);
    return res;
}

// Prend deux unbounded_int et renvoie leur produit
unbounded_int unbounded_int_division(unbounded_int a, unbounded_int b) {
    a = supprime_zero_inutile(a);
    b = supprime_zero_inutile(b);
    if(unbounded_int_cmp_unbounded_int(a, b) == - 1) return a;
    if(unbounded_int_cmp_unbounded_int(a, b) == 0) return ll2unbounded_int(1);

    unbounded_int res = {.len = 0, .premier = NULL, .dernier = NULL, .signe = '+'};

    unbounded_int partieDividende = {.len = 0, .premier = NULL, .dernier = NULL, .signe = '+'};
    chiffre *acc = a.premier;
    while(acc != NULL) {
        while(partieDividende.len < b.len && acc != NULL) {
            partieDividende = ajoute_dernier(partieDividende, acc->c);
            acc = acc->suivant;
        }
        if(unbounded_int_cmp_unbounded_int(partieDividende, b) == -1 && acc != NULL){
            partieDividende = ajoute_dernier(partieDividende, acc->c);
            acc = acc->suivant;
        }

        unbounded_int partieSoustraite = partieDividende;
        char nbSoustractions = '0';
        while(unbounded_int_cmp_unbounded_int(partieSoustraite, b) == 1) {
            unbounded_int_difference(partieSoustraite, b);
            nbSoustractions += 1;
        }

        res = ajoute_dernier(res, nbSoustractions);

        partieDividende = unbounded_int_copie(partieSoustraite);
        while(partieDividende.len < b.len && acc != NULL) {
            partieDividende = ajoute_dernier(partieDividende, acc->c);
            acc = acc->suivant;
        }

        if(unbounded_int_cmp_unbounded_int(partieDividende, b) == -1) break;
    }
    res = supprime_zero_inutile(res);
    return res;
}