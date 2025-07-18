#include "application.h"
#include "../ui/menu.h"
#include "../ui/menu_classe_matiere.h"
#include "../utils/csv_classe_matiere.h"
#include "../utils/csv_utils.h"
#include <stdio.h>
#include <string.h>

// Fonction principale d'affichage et de gestion
void afficher_application(ClasseDB *db_classe, MatiereDB *db_matiere,
                          EtudiantDB *db_etudiant, NoteDB *db_note,
                          const char *chemin_classes,
                          const char *chemin_matieres,
                          const char *chemin_etudiants,
                          const char *chemin_notes) {
  int choix;

  // Déclaration de la base de données des associations classe-matière
  static ClasseMatiereDB db_classe_matiere;
  // Initialisation si nécessaire (à adapter selon le flux du programme)
  if (db_classe_matiere.relations == NULL) {
    initialiser_ClasseMatiereDB(&db_classe_matiere, 10);
  }

  /* Utilisation de fgets() et sscanf() pour error handling et securite */
  do {
    menu_principal();
    char buffer[128];
    if (fgets(buffer, sizeof(buffer), stdin)) {
      if (sscanf(buffer, "%d", &choix) != 1) {
        printf("Entree invalide. Veuillez entrer un nombre valide.\n");
        continue;
      }
    } else {
      printf("Erreur lors de la lecture de l'entree.\n");
      continue;
    }

    switch (choix) {
    case 1: {
      int c;
      do {
        menu_classes();
        if (fgets(buffer, sizeof(buffer), stdin)) {
          if (sscanf(buffer, "%d", &c) != 1) {
            printf("Entree invalide. Veuillez entrer un nombre valide.\n");
            continue;
          }
        } else {
          printf("Erreur lors de la lecture de l'entree.\n");
          continue;
        }

        if (c == 1)
          afficher_classes(db_classe);

        else if (c == 2) {
          Classe cl;
          printf("Code : ");
          if (fgets(buffer, sizeof(buffer), stdin)) {
            if (sscanf(buffer, "%d", &cl.code) != 1) {
              printf("Entree invalide. Veuillez entrer un code valide.\n");
              continue;
            }
          } else {
            printf("Erreur lors de la lecture de l'entree.\n");
            continue;
          }

          printf("Nom : ");
          fgets(cl.nom, sizeof(cl.nom), stdin);
          cl.nom[strcspn(cl.nom, "\n")] = 0;

          printf("Niveau (LICENSE/MASTER) : ");
          char niv[10];
          fgets(niv, 10, stdin);
          niv[strcspn(niv, "\n")] = 0;
          cl.niveau = strcmp(niv, "LICENSE") == 0 ? LICENSE : MASTER;

          ajouter_classe(db_classe, cl);
          exporter_classes_csv(chemin_classes, db_classe);
        } else if (c == 3) {
          printf("Index a supprimer : ");
          int idx;
          if (fgets(buffer, sizeof(buffer), stdin)) {
            if (sscanf(buffer, "%d", &idx) != 1) {
              printf("Entree invalide. Veuillez entrer un index valide.\n");
              continue;
            }
          } else {
            printf("Erreur lors de la lecture de l'entree.\n");
            continue;
          }

          supprimer_classe(db_classe, idx);
          exporter_classes_csv(chemin_classes, db_classe);
        } else if (c == 4) {
          printf("Index a modifier : ");
          int idx;
          if (fgets(buffer, sizeof(buffer), stdin)) {
            if (sscanf(buffer, "%d", &idx) != 1) {
              printf("Entree invalide. Veuillez entrer un index valide.\n");
              continue;
            }
          } else {
            printf("Erreur lors de la lecture de l'entree.\n");
            continue;
          }

          Classe cl;
          printf("Nouveau code : ");
          if (fgets(buffer, sizeof(buffer), stdin)) {
            if (sscanf(buffer, "%d", &cl.code) != 1) {
              printf("Entree invalide. Veuillez entrer un code valide.\n");
              continue;
            }
          } else {
            printf("Erreur lors de la lecture de l'entree.\n");
            continue;
          };
          getchar();

          printf("Nouveau nom : ");
          fgets(cl.nom, sizeof(cl.nom), stdin);
          cl.nom[strcspn(cl.nom, "\n")] = 0;

          printf("Niveau (LICENSE/MASTER) : ");
          char niv[10];
          fgets(niv, 10, stdin);
          niv[strcspn(niv, "\n")] = 0;
          cl.niveau = strcmp(niv, "LICENSE") == 0 ? LICENSE : MASTER;

          modifier_classe(db_classe, idx, cl);
          exporter_classes_csv(chemin_classes, db_classe);
        } else if (c == 5) {
          printf("Chemin du CSV : ");
          char chemin[128];
          fgets(chemin, 128, stdin);
          chemin[strcspn(chemin, "\n")] = 0;

          if (charger_classes_csv(chemin, db_classe) == 0)
            printf("Chargement reussi.\n");
          else
            printf("Erreur chargement.\n");

          exporter_classes_csv(chemin_classes, db_classe);
        }
      } while (c != 0);
      break;
    }

    case 2: {
      int m;
      do {
        menu_matieres();
        if (fgets(buffer, sizeof(buffer), stdin)) {
          if (sscanf(buffer, "%d", &m) != 1) {
            printf("Entree invalide. Veuillez entrer un nombre valide.\n");
            continue;
          }
        } else {
          printf("Erreur lors de la lecture de l'entree.\n");
          continue;
        }

        if (m == 1)
          afficher_matieres(db_matiere);

        else if (m == 2) {
          if (db_classe->taille == 0) {
            printf("Aucune classe existante. Veuillez d'abord créer une "
                   "classe.\n");
            break;
          }
          Matiere mat;
          printf("Reference : ");
          if (fgets(buffer, sizeof(buffer), stdin)) {
            if (sscanf(buffer, "%d", &mat.reference) != 1) {
              printf(
                  "Entree invalide. Veuillez entrer une reference valide.\n");
              continue;
            }
          } else {
            printf("Erreur lors de la lecture de l'entree.\n");
            continue;
          }

          printf("Libelle : ");
          fgets(mat.libelle, sizeof(mat.libelle), stdin);
          mat.libelle[strcspn(mat.libelle, "\n")] = 0;

          printf("Coefficient : ");
          if (fgets(buffer, sizeof(buffer), stdin)) {
            if (sscanf(buffer, "%hhd", &mat.coeficient) != 1) {
              printf(
                  "Entree invalide. Veuillez entrer un coefficient valide.\n");
              continue;
            }
          } else {
            printf("Erreur lors de la lecture de l'entree.\n");
            continue;
          }

          ajouter_matiere(db_matiere, mat);
          exporter_matieres_csv(chemin_matieres, db_matiere);

          // Association à une classe
          printf("Sélectionnez la classe à associer à cette matière :\n");
          for (size_t i = 0; i < db_classe->taille; i++) {
            printf("  %zu. %s (code %d)\n", i + 1, db_classe->classes[i].nom,
                   db_classe->classes[i].code);
          }
          int choix_classe = 0;
          printf("Numéro de la classe : ");
          if (fgets(buffer, sizeof(buffer), stdin)) {
            if (sscanf(buffer, "%d", &choix_classe) != 1) {
              printf("Entree invalide. Veuillez entrer un numero valide.\n");
              continue;
            }
          } else {
            printf("Erreur lors de la lecture de l'entree.\n");
            continue;
          }
          if (choix_classe < 1 || (size_t)choix_classe > db_classe->taille) {
            printf("Numéro de classe invalide.\n");
            break;
          }
          ClasseMatiere rel;
          rel.code_classe = db_classe->classes[choix_classe - 1].code;
          rel.reference_matiere = mat.reference;
          ajouter_classe_matiere(&db_classe_matiere, rel, db_classe,
                                 db_matiere);
        } else if (m == 3) {
          printf("Index a supprimer : ");
          int idx;
          scanf("%d", &idx);
          getchar();

          supprimer_matiere(db_matiere, idx);
          exporter_matieres_csv(chemin_matieres, db_matiere);
        } else if (m == 4) {
          printf("Index a modifier : ");
          int idx;
          if (fgets(buffer, sizeof(buffer), stdin)) {
            if (sscanf(buffer, "%d", &idx) != 1) {
              printf("Entree invalide. Veuillez entrer un index valide.\n");
              continue;
            }
          } else {
            printf("Erreur lors de la lecture de l'entree.\n");
            continue;
          }

          Matiere mat;
          printf("Nouvelle reference : ");
          if (fgets(buffer, sizeof(buffer), stdin)) {
            if (sscanf(buffer, "%d", &mat.reference) != 1) {
              printf(
                  "Entree invalide. Veuillez entrer une reference valide.\n");
              continue;
            }
          } else {
            printf("Erreur lors de la lecture de l'entree.\n");
            continue;
          }

          printf("Nouveau libelle : ");
          fgets(mat.libelle, sizeof(mat.libelle), stdin);
          mat.libelle[strcspn(mat.libelle, "\n")] = 0;

          printf("Nouveau coefficient : ");
          if (fgets(buffer, sizeof(buffer), stdin)) {
            if (sscanf(buffer, "%hhd", &mat.coeficient) != 1) {
              printf(
                  "Entree invalide. Veuillez entrer un coefficient valide.\n");
              continue;
            }
          } else {
            printf("Erreur lors de la lecture de l'entree.\n");
            continue;
          }

          modifier_matiere(db_matiere, idx, mat);
          exporter_matieres_csv(chemin_matieres, db_matiere);
        } else if (m == 5) {
          printf("Chemin du CSV : ");
          char chemin[128];
          fgets(chemin, 128, stdin);
          chemin[strcspn(chemin, "\n")] = 0;

          if (charger_matieres_csv(chemin, db_matiere) == 0)
            printf("Chargement reussi.\n");
          else
            printf("Erreur chargement.\n");

          exporter_matieres_csv(chemin_matieres, db_matiere);
        }

      } while (m != 0);
      break;
    }

    case 3: {
      int e;
      do {
        menu_etudiants();
        scanf("%d", &e);
        getchar();

        if (e == 1)
          afficher_etudiants(db_etudiant);

        else if (e == 2) {
          if (db_classe->taille == 0) {
            printf("Aucune classe existante. Veuillez d'abord créer une "
                   "classe.\n");
            break;
          }
          Etudiant et;
          printf("Numéro : ");
          if (fgets(buffer, sizeof(buffer), stdin)) {
            if (sscanf(buffer, "%d", &et.numero) != 1) {
              printf("Entree invalide. Veuillez entrer un numero valide.\n");
              continue;
            }
          } else {
            printf("Erreur lors de la lecture de l'entree.\n");
            continue;
          }

          printf("Nom : ");
          fgets(et.nom, sizeof(et.nom), stdin);
          et.nom[strcspn(et.nom, "\n")] = 0;

          printf("Prenom : ");
          fgets(et.prenom, sizeof(et.prenom), stdin);
          et.prenom[strcspn(et.prenom, "\n")] = 0;

          // Date de naissance
          printf("Date de naissance (JJ MM AAAA) : ");
          if (fgets(buffer, sizeof(buffer), stdin)) {
            if (sscanf(buffer, "%d %d %d", &et.date_naissance.jour,
                       &et.date_naissance.mois,
                       &et.date_naissance.annee) != 3) {
              printf("Entree invalide. Veuillez entrer une date valide.\n");
              continue;
            }
          } else {
            printf("Erreur lors de la lecture de l'entree.\n");
            continue;
          }

          // email
          printf("Email: ");
          if (fgets(et.email, sizeof(et.email), stdin)) {
            et.email[strcspn(et.email, "\n")] = 0;
          } else {
            printf("Erreur lors de la lecture de l'entree.\n");
            continue;
          }

          // Sélection de la classe
          printf("Sélectionnez la classe à associer :\n");
          for (size_t i = 0; i < db_classe->taille; i++) {
            printf("  %zu. %s (code %d)\n", i + 1, db_classe->classes[i].nom,
                   db_classe->classes[i].code);
          }
          int choix_classe = 0;
          printf("Numéro de la classe : ");
          if (fgets(buffer, sizeof(buffer), stdin)) {
            if (sscanf(buffer, "%d", &choix_classe) != 1) {
              printf("Entree invalide. Veuillez entrer un numero valide.\n");
              continue;
            }
          } else {
            printf("Erreur lors de la lecture de l'entree.\n");
            continue;
          }
          if (choix_classe < 1 || (size_t)choix_classe > db_classe->taille) {
            printf("Numéro de classe invalide.\n");
            break;
          }
          et.classe_code = db_classe->classes[choix_classe - 1].code;

          ajouter_etudiant(db_etudiant, et);
          exporter_etudiants_csv(chemin_etudiants, db_etudiant);
        } else if (e == 3) {
          printf("Index a supprimer : ");
          int idx;
          if (fgets(buffer, sizeof(buffer), stdin)) {
            if (sscanf(buffer, "%d", &idx) != 1) {
              printf("Entree invalide. Veuillez entrer un index valide.\n");
              continue;
            }
          } else {
            printf("Erreur lors de la lecture de l'entree.\n");
            continue;
          }

          supprimer_etudiant(db_etudiant, idx);
          exporter_etudiants_csv(chemin_etudiants, db_etudiant);
        } else if (e == 4) {
          printf("Index a modifier : ");
          int idx;
          if (fgets(buffer, sizeof(buffer), stdin)) {
            if (sscanf(buffer, "%d", &idx) != 1) {
              printf("Entree invalide. Veuillez entrer un index valide.\n");
              continue;
            }
          } else {
            printf("Erreur lors de la lecture de l'entree.\n");
            continue;
          }

          Etudiant et;
          printf("Nouveau numéro : ");
          if (fgets(buffer, sizeof(buffer), stdin)) {
            if (sscanf(buffer, "%d", &et.numero) != 1) {
              printf("Entree invalide. Veuillez entrer un numero valide.\n");
              continue;
            }
          } else {
            printf("Erreur lors de la lecture de l'entree.\n");
            continue;
          }

          printf("Nouveau nom : ");
          fgets(et.nom, sizeof(et.nom), stdin);
          et.nom[strcspn(et.nom, "\n")] = 0;

          printf("Nouveau prenom : ");
          fgets(et.prenom, sizeof(et.prenom), stdin);
          et.prenom[strcspn(et.prenom, "\n")] = 0;

          // Date de naissance
          printf("Nouvelle date de naissance (JJ MM AAAA) : ");
          if (fgets(buffer, sizeof(buffer), stdin)) {
            if (sscanf(buffer, "%d %d %d", &et.date_naissance.jour,
                       &et.date_naissance.mois,
                       &et.date_naissance.annee) != 3) {
              printf("Entree invalide. Veuillez entrer une date valide.\n");
              continue;
            }
          } else {
            printf("Erreur lors de la lecture de l'entree.\n");
            continue;
          }

          // email
          printf("Nouvel email: ");
          if (fgets(et.email, sizeof(et.email), stdin)) {
            et.email[strcspn(et.email, "\n")] = 0;
          } else {
            printf("Erreur lors de la lecture de l'entree.\n");
            continue;
          }

          // Sélection de la classe
          printf("Sélectionnez la classe à associer :\n");
          for (size_t i = 0; i < db_classe->taille; i++) {
            printf("  %zu. %s (code %d)\n", i + 1, db_classe->classes[i].nom,
                   db_classe->classes[i].code);
          }
          int choix_classe = 0;
          printf("Numéro de la classe : ");
          if (fgets(buffer, sizeof(buffer), stdin)) {
            if (sscanf(buffer, "%d", &choix_classe) != 1) {
              printf("Entree invalide. Veuillez entrer un numero valide.\n");
              continue;
            }
          } else {
            printf("Erreur lors de la lecture de l'entree.\n");
            continue;
          }
          if (choix_classe < 1 || (size_t)choix_classe > db_classe->taille) {
            printf("Numéro de classe invalide.\n");
            break;
          }
          et.classe_code = db_classe->classes[choix_classe - 1].code;

          modifier_etudiant(db_etudiant, idx, et);
          exporter_etudiants_csv(chemin_etudiants, db_etudiant);
        } else if (e == 5) {
          printf("Chemin du CSV : ");
          char chemin[128];
          fgets(chemin, 128, stdin);
          chemin[strcspn(chemin, "\n")] = 0;

          if (charger_etudiants_csv(chemin, db_etudiant) == 0)
            printf("Chargement reussi.\n");
          else
            printf("Erreur chargement.\n");

          exporter_etudiants_csv(chemin_etudiants, db_etudiant);
        }

      } while (e != 0);
      break;
    }

    case 4: {
      int n;
      do {
        menu_notes();
        scanf("%d", &n);
        getchar();

        if (n == 1)
          afficher_notes(db_note, db_etudiant, db_matiere);

        else if (n == 2) {
          // Ajout des notes d'un étudiant pour une matière donnée
          int num_etudiant, ref_matiere;
          printf("Numéro étudiant : ");
          if (fgets(buffer, sizeof(buffer), stdin)) {
            if (sscanf(buffer, "%d", &num_etudiant) != 1) {
              printf("Entree invalide. Veuillez entrer un numero valide.\n");
              continue;
            }
          } else {
            printf("Erreur lors de la lecture de l'entree.\n");
            continue;
          }
          printf("Référence matière : ");
          if (fgets(buffer, sizeof(buffer), stdin)) {
            if (sscanf(buffer, "%d", &ref_matiere) != 1) {
              printf(
                  "Entree invalide. Veuillez entrer une reference valide.\n");
              continue;
            }
          } else {
            printf("Erreur lors de la lecture de l'entree.\n");
            continue;
          }
          Note note;
          note.numero_etudiant = num_etudiant;
          note.reference_matiere = ref_matiere;
          printf("Note CC : ");
          if (fgets(buffer, sizeof(buffer), stdin)) {
            if (sscanf(buffer, "%f", &note.noteCC) != 1) {
              printf("Entree invalide. Veuillez entrer une note valide.\n");
              continue;
            }
          } else {
            printf("Erreur lors de la lecture de l'entree.\n");
            continue;
          }
          printf("Note DS : ");
          if (fgets(buffer, sizeof(buffer), stdin)) {
            if (sscanf(buffer, "%f", &note.noteDS) != 1) {
              printf("Entree invalide. Veuillez entrer une note valide.\n");
              continue;
            }
          } else {
            printf("Erreur lors de la lecture de l'entree.\n");
            continue;
          }
          ajouter_note(db_note, note, db_etudiant, db_matiere);
          exporter_notes_csv(chemin_notes, db_note);
        } else if (n == 3) {
          // Ajout des notes pour toutes les matières d'un étudiant
          int num_etudiant;
          printf("Numéro étudiant : ");
          if (fgets(buffer, sizeof(buffer), stdin)) {
            if (sscanf(buffer, "%d", &num_etudiant) != 1) {
              printf("Entree invalide. Veuillez entrer un numero valide.\n");
              continue;
            }
          } else {
            printf("Erreur lors de la lecture de l'entree.\n");
            continue;
          }
          // Recherche de la classe de l'étudiant
          int idx_etudiant = rechercher_etudiant(db_etudiant, num_etudiant);
          if (idx_etudiant == -1) {
            printf("Étudiant introuvable.\n");
            break;
          }
          // Boucle sur les matières associées à la classe
          int code_classe = db_etudiant->etudiants[idx_etudiant].classe_code;
          for (size_t i = 0; i < db_classe_matiere.taille; i++) {
            if (db_classe_matiere.relations[i].code_classe == code_classe) {
              int ref_matiere =
                  db_classe_matiere.relations[i].reference_matiere;
              Note note;
              note.numero_etudiant = num_etudiant;
              note.reference_matiere = ref_matiere;
              printf("Matière %d - Note CC : ", ref_matiere);
              if (fgets(buffer, sizeof(buffer), stdin)) {
                if (sscanf(buffer, "%f", &note.noteCC) != 1) {
                  printf("Entree invalide. Veuillez entrer une note valide.\n");
                  continue;
                }
              } else {
                printf("Erreur lors de la lecture de l'entree.\n");
                continue;
              }
              printf("Matière %d - Note DS : ", ref_matiere);
              if (fgets(buffer, sizeof(buffer), stdin)) {
                if (sscanf(buffer, "%f", &note.noteDS) != 1) {
                  printf("Entree invalide. Veuillez entrer une note valide.\n");
                  continue;
                }
              } else {
                printf("Erreur lors de la lecture de l'entree.\n");
                continue;
              }
              ajouter_note(db_note, note, db_etudiant, db_matiere);
            }
          }
          exporter_notes_csv(chemin_notes, db_note);
        } else if (n == 4) {
          // Suppression d'une note
          printf("Index à supprimer : ");
          int idx;
          if (fgets(buffer, sizeof(buffer), stdin)) {
            if (sscanf(buffer, "%d", &idx) != 1) {
              printf("Entree invalide. Veuillez entrer un index valide.\n");
              continue;
            }
          } else {
            printf("Erreur lors de la lecture de l'entree.\n");
            continue;
          }
          supprimer_note(db_note, idx);
          exporter_notes_csv(chemin_notes, db_note);
        } else if (n == 5) {
          // Modification d'une note
          printf("Index à modifier : ");
          int idx;
          if (fgets(buffer, sizeof(buffer), stdin)) {
            if (sscanf(buffer, "%d", &idx) != 1) {
              printf("Entree invalide. Veuillez entrer un index valide.\n");
              continue;
            }
          } else {
            printf("Erreur lors de la lecture de l'entree.\n");
            continue;
          }
          Note note;
          printf("Nouveau numéro étudiant : ");
          if (fgets(buffer, sizeof(buffer), stdin)) {
            if (sscanf(buffer, "%d", &note.numero_etudiant) != 1) {
              printf("Entree invalide. Veuillez entrer un numero valide.\n");
              continue;
            }
          } else {
            printf("Erreur lors de la lecture de l'entree.\n");
            continue;
          }
          printf("Nouvelle référence matière : ");
          if (fgets(buffer, sizeof(buffer), stdin)) {
            if (sscanf(buffer, "%d", &note.reference_matiere) != 1) {
              printf(
                  "Entree invalide. Veuillez entrer une reference valide.\n");
              continue;
            }
          } else {
            printf("Erreur lors de la lecture de l'entree.\n");
            continue;
          }
          printf("Nouvelle note CC : ");
          if (fgets(buffer, sizeof(buffer), stdin)) {
            if (sscanf(buffer, "%f", &note.noteCC) != 1) {
              printf("Entree invalide. Veuillez entrer une note valide.\n");
              continue;
            }
          } else {
            printf("Erreur lors de la lecture de l'entree.\n");
            continue;
          }
          printf("Nouvelle note DS : ");
          if (fgets(buffer, sizeof(buffer), stdin)) {
            if (sscanf(buffer, "%f", &note.noteDS) != 1) {
              printf("Entree invalide. Veuillez entrer une note valide.\n");
              continue;
            }
          } else {
            printf("Erreur lors de la lecture de l'entree.\n");
            continue;
          }
          modifier_note(db_note, idx, note);
          exporter_notes_csv(chemin_notes, db_note);
        } else if (n == 6) {
          // Recherche d'une note
          int num_etudiant, ref_matiere;
          printf("Numéro étudiant : ");
          scanf("%d", &num_etudiant);
          getchar();
          printf("Référence matière : ");
          scanf("%d", &ref_matiere);
          getchar();
          int idx = rechercher_note(db_note, num_etudiant, ref_matiere);
          if (idx != -1) {
            Note n = db_note->notes[idx];
            printf("Note trouvée : CC %.2f, DS %.2f\n", n.noteCC, n.noteDS);
          } else {
            printf("Note introuvable.\n");
          }
        } else if (n == 7) {
          // Import CSV
          printf("Chemin du CSV : ");
          char chemin[128];
          fgets(chemin, 128, stdin);
          chemin[strcspn(chemin, "\n")] = 0;
          if (charger_notes_csv(chemin, db_note, db_etudiant, db_matiere) == 0)
            printf("Import réussi.\n");
          else
            printf("Erreur import.\n");
          exporter_notes_csv(chemin_notes, db_note);
        } else if (n == 8) {
          // Export CSV
          printf("Chemin du CSV : ");
          char chemin[128];
          fgets(chemin, 128, stdin);
          chemin[strcspn(chemin, "\n")] = 0;
          if (exporter_notes_csv(chemin, db_note) == 0)
            printf("Export réussi.\n");
          else
            printf("Erreur export.\n");
        }
      } while (n != 0);
      break;
    }

    case 5: {
      // Appel du menu d'association classe-matiere
      menu_classe_matiere(&db_classe_matiere, db_classe, db_matiere);
      break;
    }

    case 6: {
      printf("1. Exporter CSV\n2. Importer CSV\nVotre choix : ");
      int sub;
      scanf("%d", &sub);
      getchar();
      char chemin[128];
      printf("Chemin du CSV : ");
      fgets(chemin, 128, stdin);
      chemin[strcspn(chemin, "\n")] = 0;
      if (sub == 1) {
        if (exporter_classe_matieres_csv(chemin, &db_classe_matiere, db_classe,
                                         db_matiere) == 0)
          printf("Export réussi.\n");
        else
          printf("Erreur export.\n");
      } else if (sub == 2) {
        if (charger_classe_matieres_csv(chemin, &db_classe_matiere) == 0)
          printf("Import réussi.\n");
        else
          printf("Erreur import.\n");
      }
      break;
    }

    case 0:
      printf("Au revoir !\n");
      break;

    default:
      if (choix != 0)
        printf("Choix invalide.\n");
      break;
    }

  } while (choix != 0);
}

// Supprimer la définition de menu_notes ici pour éviter le conflit de linkage
