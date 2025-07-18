#include "./classe_matiere.h"
#include "../classe/classe.h"
#include "../matiere/matiere.h"
#include <stdio.h>

void initialiser_ClasseMatiereDB(ClasseMatiereDB *db, size_t capacite_initial) {
  db->relations = malloc(capacite_initial * sizeof(ClasseMatiere));
  if (db->relations == NULL) {
    fprintf(stderr, "Allocation de memoire echouee\n");
    exit(EXIT_FAILURE);
  }
  db->taille = 0;
  db->capacite = capacite_initial;
}

// Ajout securise : verifie que la classe et la matiere existent
int ajouter_classe_matiere(ClasseMatiereDB *db, ClasseMatiere nouvelle_relation,
                           const ClasseDB *classeDB,
                           const MatiereDB *matiereDB) {
  if (rechercher_classe(classeDB, nouvelle_relation.code_classe) == -1) {
    printf("Classe inexistante !\n");
    return 0;
  }
  if (rechercher_matiere(matiereDB, nouvelle_relation.reference_matiere) ==
      -1) {
    printf("Matiere inexistante !\n");
    return 0;
  }
  // Agrandit le tableau si besoin
  if (db->taille == db->capacite) {
    size_t nouvelle_capacite = db->capacite * 2;
    ClasseMatiere *temp =
        realloc(db->relations, nouvelle_capacite * sizeof(ClasseMatiere));
    if (temp == NULL) {
      fprintf(stderr, "Reallocation de memoire echouee !\n");
      return 0;
    }
    db->relations = temp;
    db->capacite = nouvelle_capacite;
  }
  db->relations[db->taille++] = nouvelle_relation;
  return 1;
}

void supprimer_classe_matiere(ClasseMatiereDB *db, size_t index) {
  // Verifie la validite de l'index
  if (index >= db->taille) {
    fprintf(stderr, "Index invalide\n");
    return;
  }
  // Decale les elements pour combler le trou
  for (size_t i = index; i < db->taille - 1; i++) {
    db->relations[i] = db->relations[i + 1];
  }
  db->taille--;
}

void afficher_classe_matieres(const ClasseMatiereDB *db) {
  if (db->taille == 0) {
    printf("Aucune relation classe-matiere a afficher.\n");
    return;
  }
  // Affichage du tableau formate
  printf("+-----+------------+-----------------+\n");
  printf("| Idx | CodeClasse | RefMatiere      |\n");
  printf("+-----+------------+-----------------+\n");
  for (size_t i = 0; i < db->taille; i++) {
    ClasseMatiere rel = db->relations[i];
    printf("| %3zu | %10d | %13d |\n", i, rel.code_classe,
           rel.reference_matiere);
  }
  printf("+-----+------------+-----------------+\n");
}

int rechercher_classe_matiere(const ClasseMatiereDB *db, int code_classe,
                              int reference_matiere) {
  // Recherche sequentielle par code et reference
  for (size_t i = 0; i < db->taille; i++) {
    if (db->relations[i].code_classe == code_classe &&
        db->relations[i].reference_matiere == reference_matiere) {
      return (int)i;
    }
  }
  return -1;
}

void freeClasseMatiereDB(ClasseMatiereDB *db) {
  if (db->relations) {
    free(db->relations);
    db->relations = NULL;
  }
  db->taille = 0;
  db->capacite = 0;
}
