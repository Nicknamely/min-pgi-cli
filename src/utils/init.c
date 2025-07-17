#include "init.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

// Création du répertoire de session
int creer_repertoire_session(char *nom_session, char *chemin_complet) {
    printf("Nom de la session : ");
    fgets(nom_session, 64, stdin);
    nom_session[strcspn(nom_session, "\n")] = 0;

    strcpy(chemin_complet, "./");
    strcat(chemin_complet, nom_session);

  struct stat st = {0};
  if (stat(chemin_complet, &st) == -1) {
    // Creation du dossier selon l'OS
#ifdef _WIN32 //si windows est detecter, utilise ce if sinon lautre if
    if (mkdir(chemin_complet) != 0) {
#else
        if (mkdir(chemin_complet, 0700) != 0) {  // pour les system POSIX
#endif
            printf("Erreur creation dossier : %s\n", strerror(errno));
            return -1;
        }
        return 0;
    } else {
        printf("Ce nom de session existe deja. Veuillez en choisir un autre.\n");
        return -2;
    }
}

// Création des fichiers CSV pour la session
void creer_csv_session(const char *chemin_classes, const char *chemin_matieres,
                       const char *chemin_etudiants, const char *chemin_notes) {
    FILE *f;

    f = fopen(chemin_classes, "r");
    if (!f) {
        f = fopen(chemin_classes, "w");
        if (f)
            fclose(f);
    } else {
        fclose(f);
    }

    f = fopen(chemin_matieres, "r");
    if (!f) {
        f = fopen(chemin_matieres, "w");
        if (f)
            fclose(f);
    } else {
        fclose(f);
    }

    f = fopen(chemin_etudiants, "r");
    if (!f) {
        f = fopen(chemin_etudiants, "w");
        if (f)
            fclose(f);
    } else {
        fclose(f);
    }

    f = fopen(chemin_notes, "r");
    if (!f) {
        f = fopen(chemin_notes, "w");
        if (f)
            fclose(f);
    } else {
        fclose(f);
    }
}
