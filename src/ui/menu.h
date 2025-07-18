#ifndef UI_MENU_H
#define UI_MENU_H

#include "../classe/classe.h"
#include "../classe/classe_matiere.h"
#include "../matiere/matiere.h"
#include "../note/note.h"

void menu_principal();
void menu_classes();
void menu_matieres();
void menu_etudiants();
void menu_notes();
void menu_classe_matiere();

// Fonctions interactives pour le menu notes
void supprimer_note_interactive(NoteDB *db_note, const char *chemin_notes);
void modifier_note_interactive(NoteDB *db_note, const char *chemin_notes);
void importer_notes_interactive(NoteDB *db_note, const char *chemin_notes,
                                const EtudiantDB *db_etudiant,
                                const MatiereDB *db_matiere);

#endif // UI_MENU_H
