#ifndef LISTE_MOT_H
#define LISTE_MOT_H

#include <stdio.h>
#include <stdlib.h>

typedef struct mot {
    struct mot *suivant;
    char *s;
    struct mot *precedent;
} mot;

typedef struct {
    mot *premier;
    mot *dernier;
    size_t len;
} liste_mot;

// Prend une liste_mot et la vide.
extern liste_mot reinitialise_liste_mot(liste_mot l);

// Prend un char* et une liste_mot et ajoute le string à la liste.
extern liste_mot ajoute_mot_a_liste(liste_mot l, char *e);

// Prend une liste_mot et un entier et renvoie le mot à cette indice.
extern mot *get_mot_a_indice(liste_mot l, int i);

#endif