#ifndef CLASSE_MATIERE_H
#define CLASSE_MATIERE_H
#include <stdlib.h>
#include "../classe/classe.h"
#include "../matiere/matiere.h"

typedef struct {
  int code_classe;
  int reference_matiere;
} ClasseMatiere;

typedef struct {
  ClasseMatiere *relations;
  size_t capacite;
  size_t taille;
} ClasseMatiereDB;

void initialiser_ClasseMatiereDB(ClasseMatiereDB *db, size_t capacite_initial);
int ajouter_classe_matiere(ClasseMatiereDB *db, ClasseMatiere nouvelle_relation, const ClasseDB *classeDB, const MatiereDB *matiereDB);
void supprimer_classe_matiere(ClasseMatiereDB *db, size_t index);
void afficher_classe_matieres(const ClasseMatiereDB *db);
int rechercher_classe_matiere(const ClasseMatiereDB *db, int code_classe, int reference_matiere);
void freeClasseMatiereDB(ClasseMatiereDB *db);

#endif // !CLASSE_MATIERE_H 