#include "unbounded_int.h"
#include "hashmap.h"
#include "liste_lettre.h"
#include "liste_mot.h"

hashmap variables = {.premier = NULL, .dernier = NULL, .len = 0};

static void traiteur(FILE *ecriture, liste_mot ligne) {
    if (ligne.len == 0) return;
    mot *premier = ligne.premier;
    if (strcasecmp(premier->s, "print") == 0) {
        mot *tmp = premier->suivant;
        while (tmp != NULL) {
            unbounded_int valeur = valeur_de(variables, tmp->s);
            if (valeur.signe == '*') fprintf(ecriture, "%s = 0\n", tmp->s);
            else fprintf(ecriture, "%s = %s\n", tmp->s, unbounded_int2string(valeur));
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
                if (a.signe == '*') a = valeur_de(variables, troisieme->s);
                if (b.signe == '*') b = valeur_de(variables, cinquieme->s);
                if (a.signe == '*') a = ll2unbounded_int(0);
                if (b.signe == '*') b = ll2unbounded_int(0);

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

static void parseur(FILE *lecture, FILE *ecriture) {
    liste_mot ligne = {.premier = NULL, .dernier = NULL, .len = 0};
    liste_lettre mot = {.premier = NULL, .dernier = NULL, .len = 0};
    int caractere;
    while ((caractere = fgetc(lecture)) != EOF) {
        if (isspace(caractere) == 0) {
            if (caractere == '=') {
                if (mot.len > 0) {
                    char *string = liste_lettre2string(mot);
                    ligne = ajoute_mot_a_liste(ligne, string);
                    ligne = ajoute_mot_a_liste(ligne, "=");
                    mot = reinitialise_liste_lettre(mot);
                } else {
                    ligne = ajoute_mot_a_liste(ligne, "=");
                }
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
                traiteur(ecriture, ligne);
                ligne = reinitialise_liste_mot(ligne);
            }
        }
    }

    if (mot.len > 0) {
        char *string = liste_lettre2string(mot);
        ligne = ajoute_mot_a_liste(ligne, string);
        mot = reinitialise_liste_lettre(mot);
    }
    if (ligne.len > 0) {
        traiteur(ecriture, ligne);
        ligne = reinitialise_liste_mot(ligne);
    }
}

int main(int argc, char *argv[]) {
    FILE *lecture;
    FILE *ecriture;

    if (argc > 2 && strcmp(argv[1], "-i") == 0) lecture = fopen(argv[2], "r");
    else if (argc > 4 && strcmp(argv[3], "-i") == 0) lecture = fopen(argv[4], "r");
    else lecture = stdin;

    if (argc > 2 && strcmp(argv[1], "-o") == 0) ecriture = fopen(argv[2], "w");
    else if (argc > 4 && strcmp(argv[3], "-o") == 0) ecriture = fopen(argv[4], "w");
    else ecriture = stdout;

    if (lecture == NULL || ecriture == NULL) {
        perror("Failed to open file.");
        exit(1);
    }

    parseur(lecture, ecriture);
    fclose(lecture);
    fclose(ecriture);
}
