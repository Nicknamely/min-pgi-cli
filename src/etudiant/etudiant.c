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

void afficher_etudiants(const EtudiantDB *db) {
  if (db->taille == 0) {
    printf("Aucun etudiant a afficher.\n");
    return;
  }
  for (size_t i = 0; i < db->taille; i++) {
    Etudiant e = db->etudiants[i];
    printf("[%zu] %d | %s %s | %s | %02d/%02d/%04d\n", i, e.numero, e.nom, e.prenom, e.email, e.date_naissance.jour, e.date_naissance.mois, e.date_naissance.annee);
  }
}

void modifier_etudiant(EtudiantDB *db, size_t index, Etudiant nouvel_etudiant) {
  if (index >= db->taille) {
    printf("Index invalide pour modification.\n");
    return;
  }
  db->etudiants[index] = nouvel_etudiant;
}

int rechercher_etudiant(const EtudiantDB *db, int numero) {
  for (size_t i = 0; i < db->taille; i++) {
    if (db->etudiants[i].numero == numero) {
      return (int)i;
    }
  }
  return -1;
}

void freeEtudiantDB(EtudiantDB *db) {
  if (db->etudiants) {
    free(db->etudiants);
    db->etudiants = NULL;
  }
  db->taille = 0;
  db->capacite = 0;
}
