#include "./classe/classe.h"
#include "./etudiant/etudiant.h"
#include "./matiere/matiere.h"
#include "./note/note.h"
#include "affichage/application.h"
#include "utils/csv_utils.h"
#include "utils/init.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
  // Declaration des variables pour la session
  char nom_session[64];
  char chemin_session[128];

  int mode = 0;
  // Demande a l'utilisateur s'il veut creer ou importer une session
  printf("1. Creer une nouvelle session\n2. Importer une session "
         "existante\nChoix : ");
  scanf("%d", &mode);
  getchar();

  int ok = -1;
  if (mode == 1) {
    // Creation d'une nouvelle session, boucle si le nom existe deja
    do {
      ok = creer_repertoire_session(nom_session, chemin_session);
    } while (ok == -2);
  } else {
    // Import d'une session existante, verification du dossier
    printf("Chemin du dossier de session a importer : ");
    fgets(chemin_session, sizeof(chemin_session), stdin);
    chemin_session[strcspn(chemin_session, "\n")] = 0;
    struct stat st = {0};
    if (stat(chemin_session, &st) == -1) {
      printf("Ce dossier n'existe pas.\n");
      return 1;
    }
  }

  // Construction et initialisation des chemins/fichiers CSV pour la session
  char chemin_classes[160];
  char chemin_matieres[160];
  char chemin_etudiants[160];
  char chemin_notes[160];
  char chemin_associations[160];

  initialiser_session(chemin_session, chemin_classes, chemin_matieres,
                      chemin_etudiants, chemin_notes, chemin_associations);

  // Creation des fichiers CSV si besoin (nouvelle session)
  creer_csv_session(chemin_classes, chemin_matieres, chemin_etudiants,
                    chemin_notes, chemin_associations);

  // Initialisation des bases de donnees dynamiques
  ClasseDB db_classe;
  initialiser_ClasseDB(&db_classe, 10);

  MatiereDB db_matiere;
  initialiser_MatiereDB(&db_matiere, 10);

  EtudiantDB db_etudiant;
  initialiser_EtudiantDB(&db_etudiant, 10);

  NoteDB db_note;
  initialiser_NoteDB(&db_note, 10);

  if (mode == 2) {
    // Chargement des donnees depuis les CSV si import
    int ok1 = charger_classes_csv(chemin_classes, &db_classe);
    int ok2 = charger_matieres_csv(chemin_matieres, &db_matiere);
    int ok3 = charger_etudiants_csv(chemin_etudiants, &db_etudiant);
    int ok4 =
        charger_notes_csv(chemin_notes, &db_note, &db_etudiant, &db_matiere);

    // Affichage d'un message si un fichier est manquant ou vide
    if (ok1 != 0)
      printf("Attention : classes.csv manquant ou vide.\n");
    if (ok2 != 0)
      printf("Attention : matieres.csv manquant ou vide.\n");
    if (ok3 != 0)
      printf("Attention : etudiants.csv manquant ou vide.\n");
    if (ok4 != 0)
      printf("Attention : notes.csv manquant ou vide.\n");
  }

  // Lancement de l'application principale (menus, gestion)
  afficher_application(&db_classe, &db_matiere, &db_etudiant, &db_note,
                       chemin_classes, chemin_matieres, chemin_etudiants,
                       chemin_notes);

  // Liberation de la memoire allouee pour les bases de donnees
  freeClasseDB(&db_classe);
  freeMatiereDB(&db_matiere);
  freeEtudiantDB(&db_etudiant);
  freeNoteDB(&db_note);

  return 0;
}
