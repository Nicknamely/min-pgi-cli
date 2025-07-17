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

int charger_classes_csv(const char *chemin, ClasseDB *db) {
    FILE *f = fopen(chemin, "r");
    if (!f) return -1;
    char ligne[256];
    while (fgets(ligne, sizeof(ligne), f)) {
        Classe c;
        char *token = strtok(ligne, ",");
        if (!token) continue;
        c.code = atoi(token);
        token = strtok(NULL, ",");
        if (!token) continue;
        strncpy(c.nom, token, sizeof(c.nom));
        c.nom[sizeof(c.nom)-1] = 0;
        token = strtok(NULL, ",");
        if (!token) continue;
        c.niveau = strcmp(token, "LICENSE") == 0 ? LICENSE : MASTER;
        ajouter_classe(db, c);
    }
    fclose(f);
    return 0;
}

int charger_etudiants_csv(const char *chemin, EtudiantDB *db) {
    FILE *f = fopen(chemin, "r");
    if (!f) return -1;
    char ligne[256];
    while (fgets(ligne, sizeof(ligne), f)) {
        Etudiant e;
        char *token = strtok(ligne, ",");
        if (!token) continue;
        e.numero = atoi(token);
        token = strtok(NULL, ",");
        if (!token) continue;
        strncpy(e.nom, token, sizeof(e.nom));
        e.nom[sizeof(e.nom)-1] = 0;
        token = strtok(NULL, ",");
        if (!token) continue;
        strncpy(e.prenom, token, sizeof(e.prenom));
        e.prenom[sizeof(e.prenom)-1] = 0;
        token = strtok(NULL, ",");
        if (!token) continue;
        strncpy(e.email, token, sizeof(e.email));
        e.email[sizeof(e.email)-1] = 0;
        token = strtok(NULL, ",");
        if (!token) continue;
        sscanf(token, "%d-%d-%d", &e.date_naissance.annee, &e.date_naissance.mois, &e.date_naissance.jour);
        ajouter_etudiant(db, e);
    }
    fclose(f);
    return 0;
}

int charger_notes_csv(const char *chemin, NoteDB *db, const EtudiantDB *etudiantDB, const MatiereDB *matiereDB) {
    FILE *f = fopen(chemin, "r");
    if (!f) return -1;
    char ligne[256];
    while (fgets(ligne, sizeof(ligne), f)) {
        Note n;
        char *token = strtok(ligne, ",");
        if (!token) continue;
        n.numero_etudiant = atoi(token);
        token = strtok(NULL, ",");
        if (!token) continue;
        n.reference_matiere = atoi(token);
        token = strtok(NULL, ",");
        if (!token) continue;
        n.noteCC = atof(token);
        token = strtok(NULL, ",");
        if (!token) continue;
        n.noteDS = atof(token);
        ajouter_note(db, n, etudiantDB, matiereDB);
    }
    fclose(f);
    return 0;
}
