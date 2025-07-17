#include "./classe/classe.h"
#include "./etudiant/etudiant.h"
#include "./matiere/matiere.h"
#include "./note/note.h"
#include "utils/csv_utils.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

void menu_principal() {
  printf("\n--- MENU PRINCIPAL ---\n");
  printf("1. Gestion des classes\n");
  printf("2. Gestion des matières\n");
  printf("3. Gestion des étudiants\n");
  printf("4. Gestion des notes\n");
  printf("0. Quitter\n");
  printf("Choix : ");
}

int creer_repertoire_session(char *nom_session, char *chemin_complet) {
    printf("Nom de la session : ");
    fgets(nom_session, 64, stdin);
    nom_session[strcspn(nom_session, "\n")] = 0;
    strcpy(chemin_complet, "./");
    strcat(chemin_complet, nom_session);
    struct stat st = {0};
    if (stat(chemin_complet, &st) == -1) {
#ifdef _WIN32
        if (mkdir(chemin_complet) != 0) {
#else
        if (mkdir(chemin_complet, 0700) != 0) {
#endif
            printf("Erreur création dossier : %s\n", strerror(errno));
            return -1;
        }
        return 0;
    } else {
        printf("Ce nom de session existe déjà. Veuillez en choisir un autre.\n");
        return -2;
    }
}

int main() {
  char nom_session[64];
  char chemin_session[128];
  int ok = -1;
  do {
    ok = creer_repertoire_session(nom_session, chemin_session);
  } while (ok == -2);

  // Utilisation des chemins pour les fichiers CSV
  char chemin_classes[160], chemin_matieres[160], chemin_etudiants[160], chemin_notes[160];
  snprintf(chemin_classes, sizeof(chemin_classes), "%s/classes.csv", chemin_session);
  snprintf(chemin_matieres, sizeof(chemin_matieres), "%s/matieres.csv", chemin_session);
  snprintf(chemin_etudiants, sizeof(chemin_etudiants), "%s/etudiants.csv", chemin_session);
  snprintf(chemin_notes, sizeof(chemin_notes), "%s/notes.csv", chemin_session);

  ClasseDB db_classe;
  initialiser_ClasseDB(&db_classe, 10);
  MatiereDB db_matiere;
  initialiser_MatiereDB(&db_matiere, 10);
  EtudiantDB db_etudiant;
  initialiser_EtudiantDB(&db_etudiant, 10);
  NoteDB db_note;
  initialiser_NoteDB(&db_note, 10);

  int choix;
  do {
    menu_principal();
    scanf("%d", &choix);
    getchar();
    switch (choix) {
    case 1: {
      int c;
      do {
        printf("\n--- CLASSES ---\n");
        printf("1. Afficher\n2. Ajouter\n3. Supprimer\n4. Modifier\n5. Charger CSV\n0. Retour\nChoix : ");
        scanf("%d", &c);
        getchar();
        if (c == 1)
          afficher_classes(&db_classe);
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
          ajouter_classe(&db_classe, cl);
        } else if (c == 3) {
          printf("Index à supprimer : ");
          int idx;
          scanf("%d", &idx);
          getchar();
          supprimer_classe(&db_classe, idx);
        } else if (c == 4) {
          printf("Index à modifier : ");
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
          modifier_classe(&db_classe, idx, cl);
        } else if (c == 5) {
          printf("Chemin du CSV : ");
          char chemin[128];
          fgets(chemin, 128, stdin);
          chemin[strcspn(chemin, "\n")] = 0;
          if (charger_classes_csv(chemin, &db_classe) == 0)
            printf("Chargement réussi.\n");
          else
            printf("Erreur chargement.\n");
        }
      } while (c != 0);
      break;
    }
    case 2: {
      int m;
      do {
        printf("\n--- MATIERES ---\n");
        printf("1. Afficher\n2. Ajouter\n3. Supprimer\n4. Modifier\n5. Charger CSV\n0. Retour\nChoix : ");
        scanf("%d", &m);
        getchar();
        if (m == 1)
          afficher_matieres(&db_matiere);
        else if (m == 2) {
          Matiere ma;
          printf("Référence : ");
          scanf("%d", &ma.reference);
          getchar();
          printf("Libellé : ");
          fgets(ma.libelle, sizeof(ma.libelle), stdin);
          ma.libelle[strcspn(ma.libelle, "\n")] = 0;
          printf("Coefficient : ");
          scanf("%d", &ma.coeficient);
          getchar();
          ajouter_matiere(&db_matiere, ma);
        } else if (m == 3) {
          printf("Index à supprimer : ");
          int idx;
          scanf("%d", &idx);
          getchar();
          supprimer_matiere(&db_matiere, idx);
        } else if (m == 4) {
          printf("Index à modifier : ");
          int idx;
          scanf("%d", &idx);
          getchar();
          Matiere ma;
          printf("Nouvelle référence : ");
          scanf("%d", &ma.reference);
          getchar();
          printf("Nouveau libellé : ");
          fgets(ma.libelle, sizeof(ma.libelle), stdin);
          ma.libelle[strcspn(ma.libelle, "\n")] = 0;
          printf("Nouveau coefficient : ");
          scanf("%d", &ma.coeficient);
          getchar();
          modifier_matiere(&db_matiere, idx, ma);
        } else if (m == 5) {
          printf("Chemin du CSV : ");
          char chemin[128];
          fgets(chemin, 128, stdin);
          chemin[strcspn(chemin, "\n")] = 0;
          if (charger_matieres_csv(chemin, &db_matiere) == 0)
            printf("Chargement réussi.\n");
          else
            printf("Erreur chargement.\n");
        }
      } while (m != 0);
      break;
    }
    case 3: {
      int e;
      do {
        printf("\n--- ETUDIANTS ---\n");
        printf("1. Afficher\n2. Charger CSV\n0. Retour\nChoix : ");
        scanf("%d", &e);
        getchar();
        if (e == 1)
          afficher_etudiants(&db_etudiant);
        else if (e == 2) {
          printf("Chemin du CSV : ");
          char chemin[128];
          fgets(chemin, 128, stdin);
          chemin[strcspn(chemin, "\n")] = 0;
          if (charger_etudiants_csv(chemin, &db_etudiant) == 0)
            printf("Chargement réussi.\n");
          else
            printf("Erreur chargement.\n");
        }
      } while (e != 0);
      break;
    }
    case 4: {
      int n;
      do {
        printf("\n--- NOTES ---\n");
        printf("1. Afficher\n2. Charger CSV\n0. Retour\nChoix : ");
        scanf("%d", &n);
        getchar();
        if (n == 1)
          afficher_notes(&db_note);
        else if (n == 2) {
          printf("Chemin du CSV : ");
          char chemin[128];
          fgets(chemin, 128, stdin);
          chemin[strcspn(chemin, "\n")] = 0;
          if (charger_notes_csv(chemin, &db_note, &db_etudiant, &db_matiere) == 0)
            printf("Chargement réussi.\n");
          else
            printf("Erreur chargement.\n");
        }
      } while (n != 0);
      break;
    }
    case 0:
      printf("Au revoir !\n");
      break;
    default:
      printf("Choix invalide.\n");
    }
  } while (choix != 0);

  freeClasseDB(&db_classe);
  freeMatiereDB(&db_matiere);
  freeEtudiantDB(&db_etudiant);
  freeNoteDB(&db_note);
  return 0;
}
