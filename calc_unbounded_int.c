#include "unbounded_int.h"
#include <string.h>
#include <ctype.h>
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

// Prend une hashmap et un nom et vérifie si la hashmap contient un élément de ce nom
static bool contient_variable(hashmap variables, char *nom) {
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
static hashmap ajoute_variable(hashmap variables, char *nom, unbounded_int valeur) {
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


static char *liste_lettre2string(const liste_lettre l) {
    char *res = calloc(l.len + 1, sizeof(char));
    lettre *tmp = l.premier;
    for (int i = 0; i < l.len; i++) {
        res[i] = tmp->c;
        tmp = tmp->suivant;
    }
    res[l.len] = '\0';
    return res;
}

static liste_lettre reinitialise_liste_lettre(liste_lettre l) {
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

static liste_lettre ajoute_lettre_a_liste(liste_lettre l, const char e) {
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

static liste_mot reinitialise_liste_mot(liste_mot l) {
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

static liste_mot ajoute_mot_a_liste(liste_mot l, char *e) {
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

static mot *get_mot_a_indice(liste_mot l, int i) {
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



hashmap variables = {.premier = NULL, .dernier = NULL, .len = 0};

static void traiteur(liste_mot ligne) {
    if (ligne.len == 0) return;
    mot *premier = ligne.premier;
    if (strcasecmp(premier->s, "print") == 0) {
        mot *tmp = premier->suivant;
        while (tmp != NULL) {
            unbounded_int *valeur = valeur_de(variables, tmp->s);
            if (valeur == NULL) printf("%s = 0\n", tmp->s);
            else printf("%s = %s\n", tmp->s, unbounded_int2string(*valeur));
            tmp = tmp->suivant;
        }
    }

    if (ligne.len > 2 && strcmp(premier->suivant->s, "=") == 0) {
        mot *troisieme = get_mot_a_indice(ligne, 2);
        if (ligne.len > 4) {
            mot *quatrieme = get_mot_a_indice(ligne, 3);
            if (strcmp(quatrieme->s, "*") == 0 || strcmp(quatrieme->s, "+") == 0 || strcmp(quatrieme->s, "-") == 0) {
                mot *cinquieme = get_mot_a_indice(ligne, 4);
                unbounded_int a = string2unbounded_int(troisieme->s);
                unbounded_int b = string2unbounded_int(cinquieme->s);
                if (a.signe == '*') a = *valeur_de(variables, troisieme->s);
                if (b.signe == '*') b = *valeur_de(variables, cinquieme->s);

                if (a.signe != '*' && b.signe != '*') {
                    unbounded_int res;
                    if (strcmp(quatrieme->s, "+") == 0) res = unbounded_int_somme(a, b);
                    else if (strcmp(quatrieme->s, "-") == 0) res = unbounded_int_difference(a, b);
                    else res = unbounded_int_produit(a, b);
                    variables = ajoute_variable(variables, premier->s, res);
                }
            }
        } else {
            variables = ajoute_variable(variables, premier->s, string2unbounded_int(troisieme->s));
        }
    }
}

static void parseur(FILE *fp) {
    liste_mot ligne = {.premier = NULL, .dernier = NULL, .len = 0};
    liste_lettre mot = {.premier = NULL, .dernier = NULL, .len = 0};
    int caractere;
    while ((caractere = fgetc(fp)) != EOF) {
        if (isspace(caractere) == 0) {
            if (caractere == '=' && mot.len > 0) {
                char *string = liste_lettre2string(mot);
                ligne = ajoute_mot_a_liste(ligne, string);
                ligne = ajoute_mot_a_liste(ligne, "=");
                mot = reinitialise_liste_lettre(mot);
            } else {
                mot = ajoute_lettre_a_liste(mot, caractere);
            }
        } else {
            if (mot.len > 0) {
                char *string = liste_lettre2string(mot);
                ligne = ajoute_mot_a_liste(ligne, string);
                mot = reinitialise_liste_lettre(mot);
            }
            if (caractere == '\n') {
                traiteur(ligne);
                ligne = reinitialise_liste_mot(ligne);
            }
        }
    }
    /*
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
    }*/
}

int main(int argc, char *argv[]) {
    FILE *lecture;
    FILE *ecriture;

    lecture = fopen("./texte.txt", "r");
    if (lecture == NULL) {
        perror("Failed to open file.");
        exit(1);
    }
    /*
    if (argc > 2 && strcmp(argv[1], "-i") == 0) lecture = fopen(argv[2], "r");
    else if (argc > 4 && strcmp(argv[3], "-i") == 0) lecture = fopen(argv[4], "r");
    else lecture = stdin;

    if (argc > 2 && strcmp(argv[1], "-o") == 0) ecriture = fopen(argv[2], "w");
    else if (argc > 4 && strcmp(argv[3], "-o") == 0) ecriture = fopen(argv[4], "w");
    else ecriture = stdout;

    if (lecture == NULL) {
        perror("Failed to open file.");
        exit(1);
    }
    */
    parseur(lecture);
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
