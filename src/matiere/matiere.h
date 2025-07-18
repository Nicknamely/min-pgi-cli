#ifndef MATIERE_H
#define MATIERE_H
#include <stdlib.h>

// type matiere
typedef struct {
  int reference;
  char libelle[15];
  char coeficient;
} Matiere;

// Tableau dynamique
typedef struct {
  Matiere *matieres;
  size_t capacite;
  size_t taille;
} MatiereDB;

// Fonctions CRUD pour Matiere
/*
 * @brief initialise la structure MatiereDB avec une capacite initiale
 * @param db pointeur vers MatiereDB a initialiser
 * @param capacite_initial taille de depart du tableau
 */
void initialiser_MatiereDB(MatiereDB *db, size_t capacite_initial);
/*
 * @brief ajoute une matiere a la base
 * @param db base de donnees des matieres
 * @param nouvelle_matiere la matiere a ajouter
 */
void ajouter_matiere(MatiereDB *db, Matiere nouvelle_matiere);
/*
 * @brief supprime une matiere par index
 * @param db base de donnees des matieres
 * @param index index de la matiere a supprimer
 */
void supprimer_matiere(MatiereDB *db, size_t index);
/*
 * @brief associe une matiere a une classe
 * @param db_matiere base de donnees des matieres
 * @param reference reference de la matiere
 * @param code_classe code de la classe
 */
void associer_matiere_classe(MatiereDB *db_matiere, int reference,
                             int code_classe);
/*
 * @brief exporte les matieres vers un fichier CSV
 */
void exporter_matiere_vers_csv();
/*
 * @brief affiche toutes les matieres de la base
 * @param db base de donnees des matieres
 */
void afficher_matieres(const MatiereDB *db);
/*
 * @brief modifie une matiere a l'index donne
 * @param db base de donnees des matieres
 * @param index index de la matiere a modifier
 * @param nouvelle_matiere nouvelle valeur
 */
void modifier_matiere(MatiereDB *db, size_t index, Matiere nouvelle_matiere);
/*
 * @brief cherche une matiere par reference
 * @param db base de donnees des matieres
 * @param reference reference de la matiere
 * @return index si trouve, -1 sinon
 */
int rechercher_matiere(const MatiereDB *db, int reference);
/*
 * @brief libere la memoire du MatiereDB
 * @param db base de donnees des matieres
 */
void freeMatiereDB(MatiereDB *db);
#endif // !MATIERE_H
