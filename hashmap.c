#include "hashmap.h"

// Prend une hashmap et un nom et vérifie si la hashmap contient un élément de ce nom.
bool contient_variable(hashmap variables, char *nom) {
    paire *tmp = variables.premier;
    while (tmp != NULL) {
        if (strcmp(tmp->nom, nom) == 0) return true;
        tmp = tmp->suivant;
    }
    return false;
}

// Prend une hashmap, un nom et une valeur :
//   - si un élément de ce nom existe déjà, change sa valeur
//   - sinon, l'ajoute dans la hashmap
hashmap ajoute_variable(hashmap variables, char *nom, unbounded_int valeur) {
    if (valeur.signe == '*') {
        return variables;
    } else if (contient_variable(variables, nom) == true) {
        paire *tmp = variables.premier;
        while (tmp != NULL) {
            if (strcmp(tmp->nom, nom) == 0) {
                tmp->valeur = valeur;
                return variables;
            }
            tmp = tmp->suivant;
        }
    } else {
        paire *ajout = malloc(sizeof(paire));
        if (ajout == NULL) {
            perror("ajoute_variable : malloc a échoué");
            exit(1);
        }
        ajout->nom = nom;
        ajout->valeur = valeur;
        ajout->suivant = NULL;
        
        if (variables.dernier == NULL) {
            ajout->precedent = NULL;
            variables.premier = ajout;
        } else {
            ajout->precedent = variables.dernier;
            variables.dernier->suivant = ajout;
        }

        variables.dernier = ajout;
        variables.len++;
    }
    return variables;
}

// Prend une hashmap et un nom et renvoie la paire de ce nom.
paire *paire_de_nom(hashmap variables, char *nom) {
    paire *tmp = variables.premier;
    while (tmp != NULL) {
        if (strcmp(tmp->nom, nom) == 0) return tmp;
        tmp = tmp->suivant;
    }
    return NULL;
}

// Prend une hashmap et un nom et renvoie la valeur de l'élément de ce nom.
unbounded_int valeur_de(hashmap variables, char *nom) {
    paire *tmp = variables.premier;
    while (tmp != NULL) {
        if (strcmp(tmp->nom, nom) == 0) return tmp->valeur;
        tmp = tmp->suivant;
    }
    unbounded_int *res = malloc(sizeof(unbounded_int));
    if (res == NULL) {
        perror("valeur_de : malloc a échoué");
        exit(1);
    }
    res->premier = NULL;
    res->dernier = NULL;
    res->len = 0;
    res->signe = '*';
    return *res;
}