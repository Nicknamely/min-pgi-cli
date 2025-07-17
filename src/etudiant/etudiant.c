#include "./etudiant.h"
#include <stdio.h>

void initialiser_EtudiantDB(EtudiantDB *db, size_t capacite_initial) {
  db->etudiants = malloc(capacite_initial * sizeof(Etudiant));
  if (db->etudiants == NULL) {
    fprintf(stderr, "Allocation de memoire echouer\n");
    exit(EXIT_FAILURE);
  }
  db->taille = 0;
}

void ajouter_etudiant(EtudiantDB *db, Etudiant nouvel_etudiant) {
  if (db->taille == db->capacite) {
    size_t nouvelle_capacite = db->capacite * 2;

    Etudiant *temp =
        realloc(db->etudiants, nouvelle_capacite * sizeof(Etudiant));
    if (temp == NULL) {
      fprintf(stderr, "Reallocation de memoire echouer ! \n");
      free(temp);
    }
    db->etudiants = temp;
    db->capacite = nouvelle_capacite;
  }
  db->etudiants[db->taille++] = nouvel_etudiant;
}

void supprimer_etudiant(EtudiantDB *db, size_t index) {
  if (index >= db->taille) {
    fprintf(stderr,
            "Index invalide, doit etre inferieur aux nombre d'etudiants");
    return;
  }
  for (size_t i = index; index < db->taille - 1; i++) {
    db->etudiants[i] = db->etudiants[i + 1];
  }
  // reduis l'espace si necessaire:
  if (db->taille < db->capacite / 4 && db->capacite > 2) {
    size_t nouvelle_capacite = db->capacite / 2;
    Etudiant *temp =
        realloc(db->etudiants, nouvelle_capacite * sizeof(Etudiant));
    if (temp != NULL) {
      db->etudiants = temp;
      db->capacite = nouvelle_capacite;
    }
  }
}
