#include "./matiere.h"
#include <stdio.h>

void initialiser_MatiereDB(MatiereDB *db, size_t capacite_initial) {
  db->matieres = malloc(capacite_initial * sizeof(Matiere));
  if (db->matieres == NULL) {
    fprintf(stderr, "Allocation de memoire echouee\n");
    exit(EXIT_FAILURE);
  }
  db->taille = 0;
  db->capacite = capacite_initial;
}

void ajouter_matiere(MatiereDB *db, Matiere nouvelle_maitiere) {
  // Agrandit le tableau si besoin
  if (db->taille == db->capacite) {
    size_t nouvelle_capacite = db->capacite * 2;
    Matiere *temp = realloc(db->matieres, nouvelle_capacite * sizeof(Matiere));
    if (temp == NULL) {
      fprintf(stderr, "Reallocation de memoire echouee !\n");
      exit(EXIT_FAILURE);
    }
    db->matieres = temp;
    db->capacite = nouvelle_capacite;
  }
  db->matieres[db->taille++] = nouvelle_maitiere;
}

void supprimer_matiere(MatiereDB *db, size_t index) {
  // Verifie la validite de l'index
  if (index >= db->taille) {
    fprintf(stderr,
            "Index invalide, doit etre inferieur au nombre de matieres\n");
    return;
  }
  // Decale les elements pour combler le trou
  for (size_t i = index; i < db->taille - 1; i++) {
    db->matieres[i] = db->matieres[i + 1];
  }
  db->taille--;
}

void afficher_matieres(const MatiereDB *db) {
  if (db->taille == 0) {
    printf("Aucune matiere a afficher.\n");
    return;
  }
  // Affichage du tableau formate
  printf("+-----+-----------+----------------------+-------------+\n");
  printf("| Idx | Reference | Libelle              | Coefficient |\n");
  printf("+-----+-----------+----------------------+-------------+\n");
  for (size_t i = 0; i < db->taille; i++) {
    Matiere m = db->matieres[i];
    printf("| %3zu | %9d | %-20s | %11d |\n", i, m.reference, m.libelle,
           m.coeficient);
  }
  printf("+-----+-----------+----------------------+-------------+\n");
}

void modifier_matiere(MatiereDB *db, size_t index, Matiere nouvelle_matiere) {
  // Verifie la validite de l'index
  if (index >= db->taille) {
    printf("Index invalide pour modification.\n");
    return;
  }
  db->matieres[index] = nouvelle_matiere;
}

void associer_matiere_classe(MatiereDB *db_matiere, int reference,
                             int code_classe) {
  // Fonction a implementer si besoin
}

int rechercher_matiere(const MatiereDB *db, int reference) {
  // Recherche sequentielle par reference
  for (size_t i = 0; i < db->taille; i++) {
    if (db->matieres[i].reference == reference) {
      return (int)i;
    }
  }
  return -1;
}

void freeMatiereDB(MatiereDB *db) {
  if (db->matieres) {
    free(db->matieres);
    db->matieres = NULL;
  }
  db->taille = 0;
  db->capacite = 0;
}
