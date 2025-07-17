#ifndef MATIERE_H
#define MATIERE_H
#include <stdlib.h>
typedef struct {
  int reference;
  char libelle[15];
  char coeficient;
} Matiere;

// Tableau dynamique
typedef struct {
  Matiere *matieres;
  size_t capacite;
  size_t taille; // nombre d'element courrant dans le tableau
} MatiereDB;

// Fonctions CRUD
void initialiser_MatiereDB(MatiereDB *db, size_t capacite_initial);
void ajouter_matiere(MatiereDB *db, Matiere nouvelle_matiere);
void suprimer_matiere(MatiereDB *db, size_t index);

#endif // !MATIERE_H
