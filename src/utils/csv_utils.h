#ifndef CSV_UTILS_H
#define CSV_UTILS_H

#include "../classe/classe.h"
#include "../etudiant/etudiant.h"
#include "../matiere/matiere.h"
#include "../note/note.h"

int charger_matieres_csv(const char *chemin, MatiereDB *db);
int charger_classes_csv(const char *chemin, ClasseDB *db);
int charger_etudiants_csv(const char *chemin, EtudiantDB *db);
int charger_notes_csv(const char *chemin, NoteDB *db,
                      const EtudiantDB *etudiantDB, const MatiereDB *matiereDB);
int exporter_classes_csv(const char *chemin, const ClasseDB *db);
int exporter_matieres_csv(const char *chemin, const MatiereDB *db);
int exporter_etudiants_csv(const char *chemin, const EtudiantDB *db);
int exporter_notes_csv(const char *chemin, const NoteDB *db);

#endif
