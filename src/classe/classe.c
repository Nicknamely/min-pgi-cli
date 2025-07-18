#include "./classe.h"
#include <stdio.h>

void initialiser_ClasseDB(ClasseDB *db, size_t capacite_initial) {
  db->classes = malloc(capacite_initial * sizeof(Classe));
  if (db->classes == NULL) {
    fprintf(stderr, "Allocation de memoire echouée\n");
    exit(EXIT_FAILURE);
  }
  db->taille = 0;
  db->capacite = capacite_initial;
}

void ajouter_classe(ClasseDB *db, Classe nouvelle_classe) {
  if (db->taille == db->capacite) {
    size_t nouvelle_capacite = db->capacite > 0 ? db->capacite * 2 : 1;
    Classe *temp = realloc(db->classes, nouvelle_capacite * sizeof(Classe));
    if (temp == NULL) {
      fprintf(stderr, "Reallocation de memoire echouée !\n");
      exit(EXIT_FAILURE);
    }
    db->classes = temp;
    db->capacite = nouvelle_capacite;
  }
  db->classes[db->taille++] = nouvelle_classe;
}

void supprimer_classe(ClasseDB *db, size_t index) {
  if (index >= db->taille) {
    fprintf(stderr,
            "Index invalide, doit être inférieur au nombre de classes\n");
    return;
  }
  for (size_t i = index; i < db->taille - 1; i++) {
    db->classes[i] = db->classes[i + 1];
  }
  db->taille--;
}

void afficher_classes(const ClasseDB *db) {
  if (db->taille == 0) {
    printf("Aucune classe a afficher.\n");
    return;
  }
  printf("+-----+-------+----------------------+----------+\n");
  printf("| Idx | Code  | Nom                  | Niveau   |\n");
  printf("+-----+-------+----------------------+----------+\n");
  for (size_t i = 0; i < db->taille; i++) {
    Classe c = db->classes[i];
    printf("| %3zu | %5d | %-20s | %-8s |\n", i, c.code, c.nom,
           c.niveau == LICENSE ? "LICENSE" : "MASTER");
  }
  printf("+-----+-------+----------------------+----------+\n");
}

void modifier_classe(ClasseDB *db, size_t index, Classe nouvelle_classe) {
  if (index >= db->taille) {
    printf("Index invalide pour modification.\n");
    return;
  }
  db->classes[index] = nouvelle_classe;
}

int rechercher_classe(const ClasseDB *db, int code) {
  for (size_t i = 0; i < db->taille; i++) {
    if (db->classes[i].code == code) {
      return (int)i;
    }
  }
  return -1;
}

void freeClasseDB(ClasseDB *db) {
  if (db->classes) {
    free(db->classes);
    db->classes = NULL;
  }
  db->taille = 0;
  db->capacite = 0;
}
