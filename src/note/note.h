#ifndef NOTE_H
#define NOTE_H
#include <stdlib.h>
#include "../etudiant/etudiant.h"
#include "../matiere/matiere.h"

// Structure Note (etre_note)
typedef struct {
  int numero_etudiant;
  int reference_matiere;
  float noteCC;
  float noteDS;
} Note;

// Tableau dynamique de notes
typedef struct {
  Note *notes;
  size_t capacite;
  size_t taille;
} NoteDB;

// Fonctions CRUD pour Note
void initialiser_NoteDB(NoteDB *db, size_t capacite_initial);
int ajouter_note(NoteDB *db, Note nouvelle_note, const EtudiantDB *etudiantDB, const MatiereDB *matiereDB);
void supprimer_note(NoteDB *db, size_t index);
void afficher_notes(const NoteDB *db);
void modifier_note(NoteDB *db, size_t index, Note nouvelle_note);
int rechercher_note(const NoteDB *db, int numero_etudiant, int reference_matiere);
void freeNoteDB(NoteDB *db);

#endif // !NOTE_H
