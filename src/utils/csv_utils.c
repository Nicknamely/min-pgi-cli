#include "csv_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int charger_matieres_csv(const char *chemin, MatiereDB *db) {
    FILE *f = fopen(chemin, "r");
    if (!f) return -1;

    char ligne[256];
    while (fgets(ligne, sizeof(ligne), f)) {
        Matiere m;
        char *token = strtok(ligne, ",");
        if (!token) continue;
        m.reference = atoi(token);

        token = strtok(NULL, ",");
        if (!token) continue;
        strncpy(m.libelle, token, sizeof(m.libelle));
        m.libelle[sizeof(m.libelle)-1] = 0;

        token = strtok(NULL, ",");
        if (!token) continue;
        m.coeficient = atoi(token);

        ajouter_matiere(db, m);
    }
    fclose(f);
    return 0;
}
