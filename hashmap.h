#ifndef HASHMAP_H
#define HASHMAP_H

#include "unbounded_int.h"
#include <stdbool.h>

typedef struct paire {
    struct paire *suivant;
    char *nom;
    unbounded_int valeur;
    struct paire *precedent;
} paire;

typedef struct {
    paire *premier;
    paire *dernier;
    size_t len;
} hashmap;

// Prend une hashmap et un nom et vérifie si la hashmap contient un élément de ce nom.
extern bool contient_variable(hashmap variables, char *nom);

// Prend une hashmap, un nom et une valeur :
//   - si un élément de ce nom existe déjà, change sa valeur
//   - sinon, l'ajoute dans la hashmap
extern hashmap ajoute_variable(hashmap variables, char *nom, unbounded_int valeur);

// Prend une hashmap et un nom et renvoie la paire de ce nom.
extern paire *paire_de_nom(hashmap variables, char *nom);

// Prend une hashmap et un nom et renvoie la valeur de l'élément de ce nom.
extern unbounded_int valeur_de(hashmap variables, char *nom);

#endif