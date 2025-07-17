#include "./matiere.h"
#include <stdio.h>

void initialiser_MatiereDB(MatiereDB *db, size_t capacite_initial) {
  db->matieres = malloc(capacite_initial * sizeof(Matiere));
  if (db->matieres == NULL) {
    fprintf(stderr, "Allocation de memoire echouer\n");
    exit(EXIT_FAILURE);
  }
  db->taille = 0;
}

void ajouter_etudiant(MatiereDB *db, Matiere nouvelle_maitiere) {
  if (db->taille == db->capacite) {
    size_t nouvelle_capacite = db->capacite * 2;

    Matiere *temp = realloc(db->matieres, nouvelle_capacite * sizeof(Matiere));
    if (temp == NULL) {
      fprintf(stderr, "Reallocation de memoire echouer ! \n");
      free(temp);
    }
    db->matieres = temp;
    db->capacite = nouvelle_capacite;
  }
  db->matieres[db->taille++] = nouvelle_maitiere;
}

void supprimer_etudiant(MatiereDB *db, size_t index) {
  if (index >= db->taille) {
    fprintf(stderr,
            "Index invalide, doit etre inferieur aux nombre d'matieres");
    return;
  }
  for (size_t i = index; index < db->taille - 1; i++) {
    db->matieres[i] = db->matieres[i + 1];
  }
  // reduis l'espace si necessaire:
  if (db->taille < db->capacite / 4 && db->capacite > 2) {
    size_t nouvelle_capacite = db->capacite / 2;
    Matiere *temp = realloc(db->matieres, nouvelle_capacite * sizeof(Matiere));
    if (temp != NULL) {
      db->matieres = temp;
      db->capacite = nouvelle_capacite;
    }
  }
}
