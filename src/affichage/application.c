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

  do {
    menu_principal();
    scanf("%d", &choix);
    getchar();

    switch (choix) {
    case 1: {
      int c;
      do {
        menu_classes();
        scanf("%d", &c);
        getchar();

        if (c == 1)
          afficher_classes(db_classe);

        else if (c == 2) {
          Classe cl;
          printf("Code : ");
          scanf("%d", &cl.code);
          getchar();

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
          scanf("%d", &idx);
          getchar();

          supprimer_classe(db_classe, idx);
          exporter_classes_csv(chemin_classes, db_classe);
        } else if (c == 4) {
          printf("Index a modifier : ");
          int idx;
          scanf("%d", &idx);
          getchar();

          Classe cl;
          printf("Nouveau code : ");
          scanf("%d", &cl.code);
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
        scanf("%d", &m);
        getchar();

        if (m == 1)
          afficher_matieres(db_matiere);

        else if (m == 2) {
          Matiere mat;
          printf("Reference : ");
          scanf("%d", &mat.reference);
          getchar();

          printf("Libelle : ");
          fgets(mat.libelle, sizeof(mat.libelle), stdin);
          mat.libelle[strcspn(mat.libelle, "\n")] = 0;

          printf("Coefficient : ");
          scanf("%hhd", &mat.coeficient);
          getchar();

          ajouter_matiere(db_matiere, mat);
          exporter_matieres_csv(chemin_matieres, db_matiere);
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
          scanf("%d", &idx);
          getchar();

          Matiere mat;
          printf("Nouvelle reference : ");
          scanf("%d", &mat.reference);
          getchar();

          printf("Nouveau libelle : ");
          fgets(mat.libelle, sizeof(mat.libelle), stdin);
          mat.libelle[strcspn(mat.libelle, "\n")] = 0;

          printf("Nouveau coefficient : ");
          scanf("%hhd", &mat.coeficient);
          getchar();

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
          Etudiant et;
          printf("Numéro : ");
          scanf("%d", &et.numero);
          getchar();

          printf("Nom : ");
          fgets(et.nom, sizeof(et.nom), stdin);
          et.nom[strcspn(et.nom, "\n")] = 0;

          printf("Prenom : ");
          fgets(et.prenom, sizeof(et.prenom), stdin);
          et.prenom[strcspn(et.prenom, "\n")] = 0;

          // Email et date de naissance à compléter si besoin

          ajouter_etudiant(db_etudiant, et);
          exporter_etudiants_csv(chemin_etudiants, db_etudiant);
        } else if (e == 3) {
          printf("Index a supprimer : ");
          int idx;
          scanf("%d", &idx);
          getchar();

          supprimer_etudiant(db_etudiant, idx);
          exporter_etudiants_csv(chemin_etudiants, db_etudiant);
        } else if (e == 4) {
          printf("Index a modifier : ");
          int idx;
          scanf("%d", &idx);
          getchar();

          Etudiant et;
          printf("Nouveau numéro : ");
          scanf("%d", &et.numero);
          getchar();

          printf("Nouveau nom : ");
          fgets(et.nom, sizeof(et.nom), stdin);
          et.nom[strcspn(et.nom, "\n")] = 0;

          printf("Nouveau prenom : ");
          fgets(et.prenom, sizeof(et.prenom), stdin);
          et.prenom[strcspn(et.prenom, "\n")] = 0;

          // Email et date de naissance à compléter si besoin

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
          afficher_notes(db_note);

        else if (n == 2) {
          Note note;
          printf("Numéro étudiant : ");
          scanf("%d", &note.numero_etudiant);
          getchar();

          printf("Référence matière : ");
          scanf("%d", &note.reference_matiere);
          getchar();

          printf("Note CC : ");
          scanf("%f", &note.noteCC);
          getchar();

          printf("Note DS : ");
          scanf("%f", &note.noteDS);
          getchar();

          ajouter_note(db_note, note, db_etudiant, db_matiere);
          exporter_notes_csv(chemin_notes, db_note);
        } else if (n == 3) {
          printf("Index a supprimer : ");
          int idx;
          scanf("%d", &idx);
          getchar();

          supprimer_note(db_note, idx);
          exporter_notes_csv(chemin_notes, db_note);
        } else if (n == 4) {
          printf("Index a modifier : ");
          int idx;
          scanf("%d", &idx);
          getchar();

          Note note;
          printf("Nouveau numéro étudiant : ");
          scanf("%d", &note.numero_etudiant);
          getchar();

          printf("Nouvelle référence matière : ");
          scanf("%d", &note.reference_matiere);
          getchar();

          printf("Nouvelle note CC : ");
          scanf("%f", &note.noteCC);
          getchar();

          printf("Nouvelle note DS : ");
          scanf("%f", &note.noteDS);
          getchar();

          modifier_note(db_note, idx, note);
          exporter_notes_csv(chemin_notes, db_note);
        } else if (n == 5) {
          printf("Chemin du CSV : ");
          char chemin[128];
          fgets(chemin, 128, stdin);
          chemin[strcspn(chemin, "\n")] = 0;

          if (charger_notes_csv(chemin, db_note, db_etudiant, db_matiere) == 0)
            printf("Chargement reussi.\n");
          else
            printf("Erreur chargement.\n");

          exporter_notes_csv(chemin_notes, db_note);
        }
      } while (n != 0);
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

// Les fonctions d'affichage et de menu sont à utiliser via les modules dédiés.
// Les appels doivent utiliser les prototypes des headers, pas de redéfinition ici.
