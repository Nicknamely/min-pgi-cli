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
void supprimer_matiere(MatiereDB *db, size_t index);
void associer_matiere_classe(MatiereDB *db_matiere, int reference,
                             int code_classe);
void exporter_matiere_vers_csv();
void afficher_matieres(const MatiereDB *db);
void modifier_matiere(MatiereDB *db, size_t index, Matiere nouvelle_matiere);
int rechercher_matiere(const MatiereDB *db, int reference);
void freeMatiereDB(MatiereDB *db);

#endif // !MATIERE_H
