#ifndef AFFICHAGE_APPLICATION_H
#define AFFICHAGE_APPLICATION_H

#include "../classe/classe.h"
#include "../etudiant/etudiant.h"
#include "../matiere/matiere.h"
#include "../note/note.h"

void afficher_application(ClasseDB *db_classe, MatiereDB *db_matiere,
                          EtudiantDB *db_etudiant, NoteDB *db_note,
                          const char *chemin_classes,
                          const char *chemin_matieres,
                          const char *chemin_etudiants,
                          const char *chemin_notes);

#endif // AFFICHAGE_APPLICATION_H
