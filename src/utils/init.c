#include "init.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

// Creation du repertoire de session
int creer_repertoire_session(char *nom_session, char *chemin_complet) {
  printf("Nom de la session : ");
  fgets(nom_session, 64, stdin);
  nom_session[strcspn(nom_session, "\n")] = 0;

  strcpy(chemin_complet, "./");
  strcat(chemin_complet, nom_session);

  struct stat st = {0};
  if (stat(chemin_complet, &st) == -1) {
    // Creation du dossier selon l'OS
#ifdef _WIN32 // si windows est detecter, utilise ce if sinon lautre if
    if (mkdir(chemin_complet) != 0) {
#else
    if (mkdir(chemin_complet, 0700) != 0) { // pour les system POSIX
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

// Creation des fichiers CSV pour la session
void creer_csv_session(const char *chemin_classes, const char *chemin_matieres,
                       const char *chemin_etudiants, const char *chemin_notes, const char *chemin_associations) {
  FILE *f;

  f = fopen(chemin_classes, "r");
  if (!f) {
    f = fopen(chemin_classes, "w");
    if (f) {
      fprintf(f, "code,nom,niveau\n");
      fclose(f);
    }
  } else {
    fclose(f);
  }

  f = fopen(chemin_matieres, "r");
  if (!f) {
    f = fopen(chemin_matieres, "w");
    if (f) {
      fprintf(f, "reference,libelle,coeficient\n");
      fclose(f);
    }
  } else {
    fclose(f);
  }

  // Creation du CSV etudiants avec le champ classe_code
  f = fopen(chemin_etudiants, "r");
  if (!f) {
    f = fopen(chemin_etudiants, "w");
    if (f) {
      fprintf(f, "numero,nom,prenom,email,date_naissance,classe_code\n");
      fclose(f);
    }
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

  // Creation du CSV associations classe-matiere
  f = fopen(chemin_associations, "r");
  if (!f) {
    f = fopen(chemin_associations, "w");
    if (f) {
      fprintf(f, "code_classe,reference_matiere\n");
      fclose(f);
    }
  } else {
    fclose(f);
  }
}

// Genere les chemins des fichiers CSV pour une session
void generer_chemins_csv(const char *base, char *chemin_classes, char *chemin_matieres, char *chemin_etudiants, char *chemin_notes, char *chemin_associations) {
  snprintf(chemin_classes, 160, "%s/classes.csv", base);
  snprintf(chemin_matieres, 160, "%s/matieres.csv", base);
  snprintf(chemin_etudiants, 160, "%s/etudiants.csv", base);
  snprintf(chemin_notes, 160, "%s/notes.csv", base);
  snprintf(chemin_associations, 160, "%s/matiere_clas_asso.csv", base);
}

// Initialise une session : genere les chemins et cree les fichiers CSV si besoin
void initialiser_session(const char *base, char *chemin_classes, char *chemin_matieres, char *chemin_etudiants, char *chemin_notes, char *chemin_associations) {
  generer_chemins_csv(base, chemin_classes, chemin_matieres, chemin_etudiants, chemin_notes, chemin_associations);
  creer_csv_session(chemin_classes, chemin_matieres, chemin_etudiants, chemin_notes, chemin_associations);
}
