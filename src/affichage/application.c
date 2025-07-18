#include "application.h"
#include "../ui/menu.h"
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

  // Declaration de la base de donnees des associations classe-matiere
  static ClasseMatiereDB db_classe_matiere;
  // Initialisation si necessaire (a adapter selon le flux du programme)
  if (db_classe_matiere.relations == NULL) {
    initialiser_ClasseMatiereDB(&db_classe_matiere, 10);
    // Chargement automatique des associations a l'ouverture de la session
    charger_classe_matieres_csv("docs/samples/matiere_clas_asso.csv",
                                &db_classe_matiere);
  }

  // Utilisation de fgets() et sscanf() pour error handling et securite
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
            printf("Aucune classe existante. Veuillez d'abord creer une "
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
        } else if (m == 3) {
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
          if (idx < 0 || (size_t)idx >= db_matiere->taille) {
            printf("Index hors borne.\n");
            continue;
          }
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
          int choix_asso;
          do {
            menu_classe_matiere();
            if (fgets(buffer, sizeof(buffer), stdin)) {
              if (sscanf(buffer, "%d", &choix_asso) != 1) {
                printf("Entree invalide. Veuillez entrer un nombre valide.\n");
                continue;
              }
            } else {
              printf("Erreur lors de la lecture de l'entree.\n");
              continue;
            }
            if (choix_asso == 1) {
              afficher_classe_matieres(&db_classe_matiere);
            } else if (choix_asso == 2) {
              ClasseMatiere rel;
              printf("Code classe : ");
              if (fgets(buffer, sizeof(buffer), stdin)) {
                if (sscanf(buffer, "%d", &rel.code_classe) != 1) {
                  printf("Entree invalide. Veuillez entrer un code valide.\n");
                  continue;
                }
              } else {
                printf("Erreur lors de la lecture de l'entree.\n");
                continue;
              }
              printf("Reference matiere : ");
              if (fgets(buffer, sizeof(buffer), stdin)) {
                if (sscanf(buffer, "%d", &rel.reference_matiere) != 1) {
                  printf("Entree invalide. Veuillez entrer une reference "
                         "valide.\n");
                  continue;
                }
              } else {
                printf("Erreur lors de la lecture de l'entree.\n");
                continue;
              }
              if (ajouter_classe_matiere(&db_classe_matiere, rel, db_classe,
                                         db_matiere))
                printf("Association ajoutee.\n");
              exporter_classe_matieres_csv(chemin_matieres, &db_classe_matiere,
                                           db_classe, db_matiere);
            } else if (choix_asso == 3) {
              printf("Index a dissocier : ");
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
              supprimer_classe_matiere(&db_classe_matiere, idx);
              exporter_classe_matieres_csv(chemin_matieres, &db_classe_matiere,
                                           db_classe, db_matiere);
            }
          } while (choix_asso != 0);
        } else if (m == 6) {
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
            printf("Aucune classe existante. Veuillez d'abord creer une "
                   "classe.\n");
            break;
          }
          Etudiant et;
          printf("Numero : ");
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
            // Vider le buffer si trop long: Sinon il sera impossible de saisir
            // le numero de la classe
            if (strchr(et.email, '\0') == &et.email[sizeof(et.email) - 1] &&
                et.email[sizeof(et.email) - 2] != '\n') {
              int c;
              while ((c = getchar()) != '\n' && c != EOF)
                ;
            }
          } else {
            printf("Erreur lors de la lecture de l'entree.\n");
            continue;
          }

          // Selection de la classe
          printf("Selectionnez la classe a associer :\n");
          for (size_t i = 0; i < db_classe->taille; i++) {
            printf("  %zu. %s (code %d)\n", i + 1, db_classe->classes[i].nom,
                   db_classe->classes[i].code);
          }
          int code_classe = 0;
          printf("Code de la classe : ");
          if (fgets(buffer, sizeof(buffer), stdin)) {
            if (sscanf(buffer, "%d", &code_classe) != 1) {
              printf("Entree invalide. Veuillez entrer un code valide.\n");
              continue;
            }
          } else {
            printf("Erreur lors de la lecture de l'entree.\n");
            continue;
          }
          // Verifier que le code existe
          int trouve = 0;
          for (size_t i = 0; i < db_classe->taille; i++) {
            if (db_classe->classes[i].code == code_classe) {
              et.classe_code = code_classe;
              trouve = 1;
              break;
            }
          }
          if (!trouve) {
            printf("Code de classe inexistant.\n");
            continue;
          }

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
          if (idx < 0 || (size_t)idx >= db_etudiant->taille) {
            printf("Index hors borne.\n");
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
          printf("Nouveau numero : ");
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

          // Nouvelle date de naissance
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

          // Nouvel email
          printf("Nouvel email: ");
          if (fgets(et.email, sizeof(et.email), stdin)) {
            et.email[strcspn(et.email, "\n")] = 0;
            // Vider le buffer si trop long
            if (strchr(et.email, '\0') == &et.email[sizeof(et.email) - 1] &&
                et.email[sizeof(et.email) - 2] != '\n') {
              int c;
              while ((c = getchar()) != '\n' && c != EOF)
                ;
            }
          } else {
            printf("Erreur lors de la lecture de l'entree.\n");
            continue;
          }

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
        char buffer[128];
        if (fgets(buffer, sizeof(buffer), stdin)) {
          if (sscanf(buffer, "%d", &n) != 1) {
            printf("Entree invalide. Veuillez entrer un nombre valide.\n");
            continue;
          }
        } else {
          printf("Erreur lors de la lecture de l'entree.\n");
          continue;
        }
        if (n == 2) { // Ajouter une note (etudiant)
          int num_etudiant, ref_matiere;
          float noteCC, noteDS;
          printf("Numero etudiant : ");
          if (fgets(buffer, sizeof(buffer), stdin) &&
              sscanf(buffer, "%d", &num_etudiant) == 1) {
            if (rechercher_etudiant(db_etudiant, num_etudiant) == -1) {
              printf("Etudiant inexistant.\n");
              continue;
            }
          } else {
            printf("Entree invalide.\n");
            continue;
          }
          printf("Reference matiere : ");
          if (fgets(buffer, sizeof(buffer), stdin) &&
              sscanf(buffer, "%d", &ref_matiere) == 1) {
            if (rechercher_matiere(db_matiere, ref_matiere) == -1) {
              printf("Matiere inexistante.\n");
              continue;
            }
          } else {
            printf("Entree invalide.\n");
            continue;
          }
          printf("Note CC (0-20) : ");
          if (fgets(buffer, sizeof(buffer), stdin) &&
              sscanf(buffer, "%f", &noteCC) == 1 && noteCC >= 0 &&
              noteCC <= 20) {
          } else {
            printf("Note CC invalide.\n");
            continue;
          }
          printf("Note DS (0-20) : ");
          if (fgets(buffer, sizeof(buffer), stdin) &&
              sscanf(buffer, "%f", &noteDS) == 1 && noteDS >= 0 &&
              noteDS <= 20) {
          } else {
            printf("Note DS invalide.\n");
            continue;
          }
          Note note = {num_etudiant, ref_matiere, noteCC, noteDS};
          if (ajouter_note(db_note, note, db_etudiant, db_matiere)) {
            printf("Note ajoutee.\n");
            exporter_notes_csv(chemin_notes, db_note);
          } else {
            printf("Erreur lors de l'ajout de la note.\n");
          }
        } else if (n == 3) { // Ajouter les notes d'un etudiant dans toutes ses
                             // matieres
          int num_etudiant;
          printf("Numero etudiant : ");
          if (fgets(buffer, sizeof(buffer), stdin) &&
              sscanf(buffer, "%d", &num_etudiant) == 1) {
            if (rechercher_etudiant(db_etudiant, num_etudiant) == -1) {
              printf("Etudiant inexistant.\n");
              continue;
            }
          } else {
            printf("Entree invalide.\n");
            continue;
          }
          ajouter_notes_etudiant_toutes_matieres(
              db_note, num_etudiant, db_etudiant, &db_classe_matiere,
              db_matiere);
          exporter_notes_csv(chemin_notes, db_note);
        } else if (n == 4) { // Ajouter les notes d'une classe dans une matiere
          int code_classe, ref_matiere;
          printf("Code classe : ");
          if (fgets(buffer, sizeof(buffer), stdin) &&
              sscanf(buffer, "%d", &code_classe) == 1) {
            if (rechercher_classe(db_classe, code_classe) == -1) {
              printf("Classe inexistante.\n");
              continue;
            }
          } else {
            printf("Entree invalide.\n");
            continue;
          }
          printf("Reference matiere : ");
          if (fgets(buffer, sizeof(buffer), stdin) &&
              sscanf(buffer, "%d", &ref_matiere) == 1) {
            if (rechercher_matiere(db_matiere, ref_matiere) == -1) {
              printf("Matiere inexistante.\n");
              continue;
            }
          } else {
            printf("Entree invalide.\n");
            continue;
          }
          ajouter_notes_classe_matiere(db_note, code_classe, ref_matiere,
                                       db_etudiant, &db_classe_matiere,
                                       db_matiere);
          exporter_notes_csv(chemin_notes, db_note);
        } else if (n == 5) { // Supprimer une note
          supprimer_note_interactive(db_note, chemin_notes);
        } else if (n == 6) { // Modifier une note
          modifier_note_interactive(db_note, chemin_notes);
        } else if (n == 7) { // Importer les notes depuis un CSV
          importer_notes_interactive(db_note, chemin_notes, db_etudiant,
                                     db_matiere);
        }
        // TODO: autres modes (3, 4, etc.)
      } while (n != 0);
      break;
    }

    case 0:
      printf("Au revoir !\n");
      break;

    default:
      printf("Choix invalide. Veuillez reessayer.\n");
      break;
    }
  } while (choix != 0);
}
