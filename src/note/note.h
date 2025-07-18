#ifndef NOTE_H
#define NOTE_H
#include "../classe/classe_matiere.h"
#include "../etudiant/etudiant.h"
#include "../matiere/matiere.h"
#include <stdlib.h>

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

int ajouter_note(NoteDB *db, Note nouvelle_note, const EtudiantDB *etudiantDB,
                 const MatiereDB *matiereDB);

void supprimer_note(NoteDB *db, size_t index);

void afficher_notes(const NoteDB *db, const EtudiantDB *db_etudiant,
                    const MatiereDB *db_matiere);
void modifier_note(NoteDB *db, size_t index, Note nouvelle_note);

int rechercher_note(const NoteDB *db, int numero_etudiant,
                    int reference_matiere);
void freeNoteDB(NoteDB *db);

int ajouter_notes_etudiant_toutes_matieres(
    NoteDB *db, int numero_etudiant, const EtudiantDB *db_etudiant,
    const ClasseMatiereDB *db_classe_matiere, const MatiereDB *db_matiere);

int ajouter_notes_classe_matiere(NoteDB *db, int code_classe, int ref_matiere,
                                 const EtudiantDB *db_etudiant,
                                 const ClasseMatiereDB *db_classe_matiere,
                                 const MatiereDB *db_matiere);

// Fonctions interactives pour le menu
void supprimer_note_interactive(NoteDB *db_note, const char *chemin_notes);
void modifier_note_interactive(NoteDB *db_note, const char *chemin_notes);
void importer_notes_interactive(NoteDB *db_note, const char *chemin_notes, const EtudiantDB *db_etudiant, const MatiereDB *db_matiere);

#endif // !NOTE_H
