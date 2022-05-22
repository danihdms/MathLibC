#include "liste_lettre.h"

// Prend une liste_lettre et la transforme en string.
char *liste_lettre2string(const liste_lettre l) {
    char *res = calloc(l.len + 1, sizeof(char));
    lettre *tmp = l.premier;
    for (int i = 0; i < l.len; i++) {
        res[i] = tmp->c;
        tmp = tmp->suivant;
    }
    res[l.len] = '\0';
    return res;
}

// Prend une liste_lettre et la vide.
liste_lettre reinitialise_liste_lettre(liste_lettre l) {
    if (l.len == 0) return l;
    if (l.len == 1) {
        free(l.premier);
    } else {
        lettre *tmp = l.premier->suivant;
        while (tmp != NULL) {
            free(tmp->precedent);
            tmp = tmp->suivant;
        }
        free(l.dernier);
    }
    l.premier = NULL;
    l.dernier = NULL;
    l.len = 0;
    return l;
}

// Prend un char et une liste_lettre et ajoute ce caractère à la liste.
liste_lettre ajoute_lettre_a_liste(liste_lettre l, const char e) {
    lettre *ajout = malloc(sizeof(lettre));
    if (ajout == NULL) {
        perror("ajoute_lettre_a_liste : malloc a échoué");
        exit(1);
    }
    ajout->c = e;
    ajout->suivant = NULL;
    
    if (l.dernier == NULL) {
        ajout->precedent = NULL;
        l.premier = ajout;
    } else {
        ajout->precedent = l.dernier;
        l.dernier->suivant = ajout;
    }

    l.dernier = ajout;
    l.len++;
    return l;
}