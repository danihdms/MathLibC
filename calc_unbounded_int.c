#include "unbounded_int.h"
#include <string.h>
#define MAX 5   // le nombre maximum de termes attendu par ligne

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

// Prend une hashmap et un nom et vérifie si la hashmap contient un élément de ce nom
static int contient_variable(hashmap variables, char *nom) {
    paire *tmp = variables.premier;
    while (tmp != NULL) {
        if (strcmp(tmp->nom, nom) == 0) return 1;
        tmp = tmp->suivant;
    }
    return 0;
}

// Prend une hashmap, un nom et une valeur :
//   - si un élément de ce nom existe déjà, change sa valeur
//   - sinon, l'ajoute dans la hashmap
static hashmap ajoute_variable(hashmap variables, char *nom, unbounded_int valeur) {
    if (valeur.signe == '*') {
        return variables;
    } else if (contient_variable(variables, nom) == 0) {
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

// Prend une hashmap et un nom et renvoie la paire de ce nom
static paire *paire_de_nom(hashmap variables, char *nom) {
    paire *tmp = variables.premier;
    while (tmp != NULL) {
        if (strcmp(tmp->nom, nom) == 0) return tmp;
        tmp = tmp->suivant;
    }
    return NULL;
}

// Prend une hashmap et un nom et renvoie la valeur de l'élément de ce nom
static unbounded_int *valeur_de(hashmap variables, char *nom) {
    paire *tmp = variables.premier;
    while (tmp != NULL) {
        if (strcmp(tmp->nom, nom) == 0) return &(tmp->valeur);
        tmp = tmp->suivant;
    }
    return NULL;
}

void interpreteur(FILE *fp) {
    hashmap variables = {.premier = NULL, .dernier = NULL, .len = 0};
    char *scan = malloc(sizeof(char));
    while(fscanf(fp, "%s", scan) != -1) {
        char **string = calloc(MAX, sizeof(char));
        int i = 0;
        // TODO : chercher un moyen d'avoir la taille exacte du string à créer
        char *value = malloc(sizeof(char));
        while(sscanf(scan, "%s", value) != EOF) {
            string[i] = value;
            i++;
        }
        
        if (strcmp(string[0], "print") == 0) {
            paire *p = paire_de_nom(variables, string[1]);
            if (p != NULL) printf("%s = %s", p->nom, unbounded_int2string(p->valeur));
        } else if (strcmp(string[0], "=") == 0) {
            if (strcmp(string[0], "*") == 0 || strcmp(string[0], "+") == 0 || strcmp(string[0], "-") == 0) {
                unbounded_int a = string2unbounded_int(string[2]);
                unbounded_int b = string2unbounded_int(string[4]);
                if (a.signe == '*') a = *valeur_de(variables, string[2]);
                if (b.signe == '*') b = *valeur_de(variables, string[4]);

                if (a.signe != '*' && b.signe != '*') {
                    unbounded_int res;
                    if (strcmp(string[0], "+") == 0) res = unbounded_int_somme(a, b);
                    else if (strcmp(string[0], "-") == 0) res = unbounded_int_difference(a, b);
                    else res = unbounded_int_produit(a, b);
                    variables = ajoute_variable(variables, string[0], res);
                }
            } else {
                variables = ajoute_variable(variables, string[0], string2unbounded_int(string[2]));
            }
        }
        // Le tableau value doit être utilisé pour effectuer les calculs et les stocker dans variables

        for(int i = 0; i < 5; i++) {
            free(string[i]);
        }
        free(string);
    }
}

int main(int argc, char *argv[]) {
    FILE *lecture;
    FILE *ecriture;

    if (strcmp(argv[1], "-i") == 0) lecture = fopen(argv[1], "r");
    else if (strcmp(argv[3], "-i") == 0) lecture = fopen(argv[3], "r");
    // else lecture = stdin;

    // ligne temporaire pour les tests
    else lecture = fopen("./texte.txt", "r");

    if (strcmp(argv[1], "-o") == 0) ecriture = fopen(argv[1], "w");
    else if (strcmp(argv[3], "-o") == 0) ecriture = fopen(argv[3], "w");
    else ecriture = stdout;

    if (lecture == NULL) {
        perror("Failed to open file.");
        exit(1);
    }
    interpreteur(lecture);
    fclose(lecture);
}

//
// si on trouve un séprateur (" ", "=", " + ", " - ", " * "): alors nouveau string
    // -> on a un tableua de string avec tout ce qu'il y a dans la ligne
// si le premier string est print, on va chercher la variable dans le tableau de
    // variables et on l'affiche a partir du deuxième string
    // sinon, on imprime variable non trouvée
// si le deuxième signe est un égal
    // si il n'y en a que trois, on cree un unbounded_int qu'on affecte a la variable
    // sinon, si le 4ème est un opérateur, on affecte a la variable le résultat de l'opération
