#ifndef CLASSE_H
#define CLASSE_H
#include <stdlib.h>

// type niveau
typedef enum { LICENSE, MASTER } NIVEAU;

// type classe
typedef struct {
  int code;
  char nom[30];
  NIVEAU niveau;
} Classe;

// Tableau dynamique
typedef struct {
  Classe *classes;
  size_t capacite;
  size_t taille;
} ClasseDB;

// Fonctions CRUD pour Classe
/*
 * @brief initialise la structure ClasseDB avec une capacite initiale
 * @param db pointeur vers ClasseDB a initialiser
 * @param capacite_initial taille de depart du tableau
 */
void initialiser_ClasseDB(ClasseDB *db, size_t capacite_initial);
/*
 * @brief ajoute une classe a la base
 * @param db base de donnees des classes
 * @param nouvelle_classe la classe a ajouter
 */
void ajouter_classe(ClasseDB *db, Classe nouvelle_classe);
/*
 * @brief supprime une classe par index
 * @param db base de donnees des classes
 * @param index index de la classe a supprimer
 */
void supprimer_classe(ClasseDB *db, size_t index);
/*
 * @brief affiche toutes les classes de la base
 * @param db base de donnees des classes
 */
void afficher_classes(const ClasseDB *db);
/*
 * @brief modifie une classe a l'index donne
 * @param db base de donnees des classes
 * @param index index de la classe a modifier
 * @param nouvelle_classe nouvelle valeur
 */
void modifier_classe(ClasseDB *db, size_t index, Classe nouvelle_classe);
/*
 * @brief cherche une classe par code
 * @param db base de donnees des classes
 * @param code code de la classe
 * @return index si trouve, -1 sinon
 */
int rechercher_classe(const ClasseDB *db, int code);
/*
 * @brief libere la memoire du ClasseDB
 * @param db base de donnees des classes
 */
void freeClasseDB(ClasseDB *db);
#endif // !CLASSE_H
