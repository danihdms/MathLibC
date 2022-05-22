#ifndef LISTE_LETTRE_H
#define LISTE_LETTRE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct lettre {
    struct lettre *suivant;
    char c;
    struct lettre *precedent;
} lettre;

typedef struct {
    lettre *premier;
    lettre *dernier;
    size_t len;
} liste_lettre;

// Prend une liste_lettre et la transforme en string.
extern char *liste_lettre2string(const liste_lettre l);

// Prend une liste_lettre et la vide.
extern liste_lettre reinitialise_liste_lettre(liste_lettre l);

// Prend un char et une liste_lettre et ajoute ce caractère à la liste.
extern liste_lettre ajoute_lettre_a_liste(liste_lettre l, const char e);

#endif