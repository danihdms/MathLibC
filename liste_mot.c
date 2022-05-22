#include "liste_mot.h"

// Prend une liste_mot et la vide.
liste_mot reinitialise_liste_mot(liste_mot l) {
    if (l.len == 0) return l;
    if (l.len == 1) {
        free(l.premier->s);
        free(l.premier);
    } else {
        mot *tmp = l.premier->suivant;
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

// Prend un char* et une liste_mot et ajoute le string à la liste.
liste_mot ajoute_mot_a_liste(liste_mot l, char *e) {
    mot *ajout = malloc(sizeof(mot));
    if (ajout == NULL) {
        perror("ajoute_mot_a_liste : malloc a échoué");
        exit(1);
    }
    ajout->s = e;
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

// Prend une liste_mot et un entier et renvoie le mot à cette indice.
mot *get_mot_a_indice(liste_mot l, int i) {
    if (i < 0 || i >= l.len) return NULL;
    if (i < l.len / 2) {
        mot *tmp = l.premier;
        for (int j = 0; j < i; j++) tmp = tmp->suivant;
        return tmp;
    } else {
        mot *tmp = l.dernier;
        for (int j = l.len - 1; j > i; j--) tmp = tmp->precedent;
        return tmp;
    }
}