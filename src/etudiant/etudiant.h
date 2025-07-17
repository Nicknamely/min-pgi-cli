#ifndef ETUDIANT_H

#define ETUDIANT_H

#include <stdlib.h>
// type date
typedef struct Date {
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
} Etudiant;

// Tableau dynamique
typedef struct {
  Etudiant *etudiants;
  size_t capacite;
  size_t taille; // nombre d'element courrant dans le tableau
} EtudiantDB;

// Fonctions CRUD
void initialiser_EtudiantDB(EtudiantDB *db, size_t capacite_initial);
void ajouter_etudiant(EtudiantDB *db, Etudiant nouvel_etudiant);
void supprimer_etudiant(EtudiantDB *db, size_t index);
void freeEtudiantdb(EtudiantDB *db);
#endif // !ETUDIANT_H
