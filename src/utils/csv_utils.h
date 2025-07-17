#ifndef CSV_UTILS_H
#define CSV_UTILS_H

#include "../matiere/matiere.h"
#include "../classe/classe.h"
#include "../etudiant/etudiant.h"
#include "../note/note.h"

int charger_matieres_csv(const char *chemin, MatiereDB *db);
int charger_classes_csv(const char *chemin, ClasseDB *db);
int charger_etudiants_csv(const char *chemin, EtudiantDB *db);
int charger_notes_csv(const char *chemin, NoteDB *db, const EtudiantDB *etudiantDB, const MatiereDB *matiereDB);

#endif
