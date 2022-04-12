#include "unbounded_int.h"

// Prend un int et renvoie l'adresse d'une chaine de caractères correspondante
// Si le nombre est négatif, le signe '-' n'apparaîtra pas dans la chaîne de caractères
static char *int2string(long long i){
    int n = i;
    int acc = 0;
    while(n != 0) {
        acc++;
        n = n/10;
    }
    n = abs(i);
    char *numbers = calloc(acc, sizeof(char));
    if(numbers == NULL){
        abort();
    }
    for(int j = acc - 1; j > -1; j--){
        numbers[j] = n % 10 + '0';
        n /= 10;
    }
    return numbers;
}

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

static unbounded_int unbounded_int_abs(unbounded_int i) {
    unbounded_int res = {.len = i.len, .signe = '+', .premier = NULL, .dernier = NULL};
    chiffre *tmp = i.premier;
    while (tmp != NULL) {
        res = ajoute_dernier(res, tmp->c);
        tmp = tmp->suivant;
    }
    return res;
}

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

static unbounded_int supprime_zero_inutile(unbounded_int i) {
    unbounded_int res = {.len = i.len, .signe = i.signe, .premier = i.premier, .dernier = i.dernier};
    while(res.premier->c == '0') {
        res = supprime_premier(res);
    }
    return res;
}

// Prend l'adresse d'une chaîne de caractères et renvoie le
// unbounded_int correspondant
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
        res = ajoute_dernier(res, e[i]);
    }
    return res;
}

// Prend un nombre et renvoie le unbounded_int correspondant
unbounded_int ll2unbounded_int(long long i) {
    char *numbers = int2string(i);
    unbounded_int res = string2unbounded_int(numbers);
    res.signe = (i < 0) ? '-' : '+';
    return res;
}    

// Prend en argument un unbounded_int et renvoie la chaîne de
// caractères correspondant
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

// Prend deux unbounded_int et les compares
// renvoie -1 si a < b, 0 si a == b et 1 si a > b
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

// Prend un unbounded_int et un entier et les compares
// renvoie -1 si a < b, 0 si a == b et 1 si a > b
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
        tmpA = tmpA->precedent;
        tmpB = tmpB->precedent;
    }
    if(reste != 0) res = ajoute_premier(res, reste + '0');
    return res;
}

// Prend deux unbounded_int et renvoie leur différence
unbounded_int unbounded_int_difference(unbounded_int a, unbounded_int b) {
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
        if (tmpB == NULL) {
            res = ajoute_premier(res, tmpA->c);
        } else {
            int chiffreA = tmpA->c - '0';
            int chiffreB = tmpB->c - '0';
            if (chiffreA >= chiffreB + reste) {
                res = ajoute_premier(res, '0' + chiffreA - chiffreB - reste);
                reste = 0;
            } else {
                res = ajoute_premier(res, '0' + chiffreA + 10 - chiffreB - reste);
                reste = 1;
            }
        }

        tmpA = tmpA->precedent;
        tmpB = tmpB->precedent;
    }
    res = supprime_zero_inutile(res);
    return res;
}

// Prend deux unbounded_int et renvoie leur produit
unbounded_int unbounded_int_produit(unbounded_int a, unbounded_int b) {
    if (a.signe == '*' || b.signe == '*') exit(5);

    char signe = '+';
    if ((a.signe == '+' && b.signe == '-') || (a.signe == '-' && b.signe == '+')) signe = '-';

    unbounded_int res = {.len = 0, .signe = signe, .premier = NULL, .dernier = NULL};
    for (int i = 0; i < a.len + b.len - 1; i++) res = ajoute_dernier(res, '0');

    chiffre *tmpB = b.dernier;
    chiffre *tmpRes = res.dernier;
    for (int i = 0; i < b.len; i++) {
        for (int j = 0; j < i; j++) tmpRes = tmpRes->precedent;

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

        tmpRes = res.dernier;
        if (i == 0) res.dernier = tmpRes;
        tmpB = tmpB->precedent;
    }
    return res;
}