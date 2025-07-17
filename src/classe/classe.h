#ifndef CLASSE_H
#define CLASSE_H
#include <stdlib.h>
typedef enum { LICENSE, MASTER } NIVEAU;

typedef struct {
  int code;
  char nom[30];
  NIVEAU niveau;
} Classe;

// Tableau dynamique
typedef struct {
  Classe *classes;
  size_t capacite;
  size_t taille; // nombre d'element courrant dans le tableau
} ClasseDB;

// Fonctions CRUD
void initialiser_ClasseDB(ClasseDB *db, size_t capacite_initial);
void ajouter_classe(ClasseDB *db, Classe nouvelle_classe);
void supprimer_classe(ClasseDB *db, size_t index);
void afficher_classes(const ClasseDB *db);
void modifier_classe(ClasseDB *db, size_t index, Classe nouvelle_classe);
int rechercher_classe(const ClasseDB *db, int code);
void freeClasseDB(ClasseDB *db);
#endif // !CLASSE_H
