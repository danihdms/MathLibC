#include <stdio.h>
#include "unbounded_int.h"

void interpret(FILE *fp) {
    // On crée un tableau de pointeurs de unbounded_int
    unbounded_int *variables = calloc(10, sizeof(unbounded_int));
    // format d'une string à lire dans le fichier

    char *scanned = malloc(sizeof(char));
    while(fscanf(fp, "%s", scanned) != -1) {
        char *arr[5] = calloc(5, sizeof(char));

        int i = 0;
        char *value = malloc(sizeof(char));
        while(sscanf(scanned, "%s", value) != EOF) {
            arr[i] = value;
            i++;
        }
        
        // Le tableua value doit être utilisé pour effectuierles calculs et les stocker dans variables

        for(int i = 0; i < 5; i++) {
            free(arr[i]);
        }
        free(arr);
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
