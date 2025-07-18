#ifndef CLASSE_MATIERE_H
#define CLASSE_MATIERE_H
#include "../classe/classe.h"
#include "../matiere/matiere.h"
#include <stdlib.h>

// type association classe-matiere
typedef struct {
  int code_classe;
  int reference_matiere;
} ClasseMatiere;

// Tableau dynamique
typedef struct {
  ClasseMatiere *relations;
  size_t capacite;
  size_t taille;
} ClasseMatiereDB;

// Fonctions CRUD pour ClasseMatiere
/*
* @brief initialise la structure ClasseMatiereDB avec une capacite initiale
* @param db pointeur vers ClasseMatiereDB a initialiser
* @param capacite_initial taille de depart du tableau
*/
void initialiser_ClasseMatiereDB(ClasseMatiereDB *db, size_t capacite_initial);
/*
* @brief ajoute une association classe-matiere (securise)
* @param db base de donnees des associations
* @param nouvelle_relation association a ajouter
* @param classeDB base des classes
* @param matiereDB base des matieres
* @return 1 si ajoute, 0 sinon
*/
int ajouter_classe_matiere(ClasseMatiereDB *db, ClasseMatiere nouvelle_relation,
                           const ClasseDB *classeDB,
                           const MatiereDB *matiereDB);
/*
* @brief supprime une association par index
* @param db base de donnees des associations
* @param index index de l'association a supprimer
*/
void supprimer_classe_matiere(ClasseMatiereDB *db, size_t index);
/*
* @brief affiche toutes les associations classe-matiere
* @param db base de donnees des associations
*/
void afficher_classe_matieres(const ClasseMatiereDB *db);
/*
* @brief cherche une association classe-matiere
* @param db base de donnees des associations
* @param code_classe code de la classe
* @param reference_matiere reference de la matiere
* @return index si trouve, -1 sinon
*/
int rechercher_classe_matiere(const ClasseMatiereDB *db, int code_classe,
                              int reference_matiere);
/*
* @brief libere la memoire du ClasseMatiereDB
* @param db base de donnees des associations
*/
void freeClasseMatiereDB(ClasseMatiereDB *db);
#endif // !CLASSE_MATIERE_H
