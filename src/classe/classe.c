#include "./classe.h"
#include <stdio.h>

void initialiser_ClasseDB(ClasseDB *db, size_t capacite_initial) {
  db->classes = malloc(capacite_initial * sizeof(Classe));
  if (db->classes == NULL) {
    fprintf(stderr, "Allocation de memoire echouer\n");
    exit(EXIT_FAILURE);
  }
  db->taille = 0;
}

void ajouter_etudiant(ClasseDB *db, Classe nouvelle_classe) {
  if (db->taille == db->capacite) {
    size_t nouvelle_capacite = db->capacite * 2;

    Classe *temp = realloc(db->classes, nouvelle_capacite * sizeof(Classe));
    if (temp == NULL) {
      fprintf(stderr, "Reallocation de memoire echouer ! \n");
      free(temp);
    }
    db->classes = temp;
    db->capacite = nouvelle_capacite;
  }
  db->classes[db->taille++] = nouvelle_classe;
}

void supprimer_etudiant(ClasseDB *db, size_t index) {
  if (index >= db->taille) {
    fprintf(stderr, "Index invalide, doit etre inferieur aux nombre d'classes");
    return;
  }
  for (size_t i = index; index < db->taille - 1; i++) {
    db->classes[i] = db->classes[i + 1];
  }
}
