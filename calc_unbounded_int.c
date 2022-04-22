#include "unbounded_int.h"
#define MAX 5   // le nombre maximum de termes attendu par ligne

typedef struct {
    paire *suivant;
    char *nom;
    unbounded_int valeur;
    paire *precedent;
} paire;

typedef struct {
    paire *premier;
    paire *dernier;
    size_t len;
} hashmap;

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

static int contient_variable(hashmap variables, char *nom) {
    paire *tmp = variables.premier;
    while (tmp != NULL) {
        if (strcmp(tmp->nom, nom) == 0) return 1;
        tmp = tmp->suivant;
    }
    return 0;
}

static paire *paire_de_nom(hashmap variables, char *nom) {
    paire *tmp = variables.premier;
    while (tmp != NULL) {
        if (strcmp(tmp->nom, nom) == 0) return tmp;
        tmp = tmp->suivant;
    }
    return NULL;
}

static unbounded_int *valeur_de(hashmap variables, char *nom) {
    paire *tmp = variables.premier;
    while (tmp != NULL) {
        if (strcmp(tmp->nom, nom) == 0) return &(tmp->valeur);
        tmp = tmp->suivant;
    }
    return NULL;
}

void interpret(FILE *fp) {
    hashmap variables = {.premier = NULL, .dernier = NULL, .len = 0};
    char *scan = malloc(sizeof(char));
    while(fscanf(fp, "%s", scan) != -1) {
        char *string[MAX] = calloc(MAX, sizeof(char));
        int i = 0;
        char *value = malloc(sizeof(char));
        while(sscanf(scan, "%s", value) != EOF) {
            string[i] = value;
            i++;
        }
        
        if (string[0] == "print") {
            paire *p = paire_de_nom(variables, string[1]);
            if (p != NULL) printf("%s = %s", p->nom, unbounded_int2string(p->valeur));
        } else if (string[1] == '=') {
            if (string[3] == '*' || string[3] == '+' || string[3] == '-') {
                unbounded_int a = string2unbounded_int(string[2]);
                unbounded_int b = string2unbounded_int(string[4]);
                if (a.signe != '*' && b.signe != '*') {
                    unbounded_int res;
                    if (string[3] == '+') res = unbounded_int_somme(a, b);
                    else if (string[3] == '-') res = unbounded_int_difference(a, b);
                    else res = unbounded_int_produit(a, b);
                    variables = ajoute_variable(variables, string[0], res);
                }
            } else {
                variables = ajoute_variable(variables, string[0], string2unbounded_int(string[2]));
            }
        }
        // Le tableua value doit être utilisé pour effectuierles calculs et les stocker dans variables

        for(int i = 0; i < 5; i++) {
            free(string[i]);
        }
        free(string);
    }
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
