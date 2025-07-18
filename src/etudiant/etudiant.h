#ifndef ETUDIANT_H
#define ETUDIANT_H

#include <stdlib.h>

// type date
typedef struct {
  int jour;
  int mois;
  int annee;
} Date;

// type etudiant
typedef struct {
  int numero;
  char nom[30];
  char prenom[20];
  char email[20];
  Date date_naissance;
  int classe_code;
} Etudiant;

// Tableau dynamique
typedef struct {
  Etudiant *etudiants;
  size_t capacite;
  size_t taille;
} EtudiantDB;

// Fonctions CRUD pour Etudiant
/*
* @brief initialise la structure EtudiantDB avec une capacite initiale
* @param db pointeur vers EtudiantDB a initialiser
* @param capacite_initial taille de depart du tableau
*/
void initialiser_EtudiantDB(EtudiantDB *db, size_t capacite_initial);

/*
* @brief ajoute un etudiant a la base
* @param db base de donnees des etudiants
* @param nouvel_etudiant l'etudiant a ajouter
*/
void ajouter_etudiant(EtudiantDB *db, Etudiant nouvel_etudiant);

/*
* @brief supprime un etudiant par index
* @param db base de donnees des etudiants
* @param index index de l'etudiant a supprimer
*/
void supprimer_etudiant(EtudiantDB *db, size_t index);

/*
* @brief affiche tous les etudiants de la base
* @param db base de donnees des etudiants
*/
void afficher_etudiants(const EtudiantDB *db);

/*
* @brief modifie un etudiant a l'index donne
* @param db base de donnees des etudiants
* @param index index de l'etudiant a modifier
* @param nouvel_etudiant nouvelle valeur
*/
void modifier_etudiant(EtudiantDB *db, size_t index, Etudiant nouvel_etudiant);

/*
* @brief cherche un etudiant par numero
* @param db base de donnees des etudiants
* @param numero numero de l'etudiant
* @return index si trouve, -1 sinon
*/
int rechercher_etudiant(const EtudiantDB *db, int numero);

/*
* @brief libere la memoire du EtudiantDB
* @param db base de donnees des etudiants
*/
void freeEtudiantDB(EtudiantDB *db);
#endif // !ETUDIANT_H
