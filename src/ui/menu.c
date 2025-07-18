#include "menu.h"
#include "../classe/classe_matiere.h"
#include "../utils/csv_classe_matiere.h"
#include <stdio.h>

void menu_principal() {
  printf("\n--- MENU PRINCIPAL ---\n");
  printf("1. Gestion des classes\n");
  printf("2. Gestion des matières\n");
  printf("3. Gestion des étudiants\n");
  printf("4. Gestion des notes\n");
  printf("0. Quitter\n");
  printf("Choix : ");
}

void menu_classes() {
  printf("\n--- CLASSES ---\n");
  printf("1. Afficher\n2. Ajouter\n3. Supprimer\n4. Modifier\n5. Charger "
         "CSV\n0. Retour\nChoix : ");
}

void menu_matieres() {
  printf("\n--- MATIERES ---\n");
  printf("1. Afficher\n2. Ajouter\n3. Supprimer\n4. Modifier\n5. Association Classe\n6. Charger CSV\n0. Retour\nChoix : ");
}

void menu_etudiants() {
  printf("\n--- ETUDIANTS ---\n");
  printf("1. Afficher\n2. Ajouter\n3. Supprimer\n4. Modifier\n5. Charger "
         "CSV\n0. Retour\nChoix : ");
}

void menu_notes() {
  printf("\n--- NOTES ---\n");
  printf("1. Afficher\n2. Ajouter une note (étudiant)\n3. Ajouter une note "
         "(matière)\n4. Ajouter une note (classe/matière)\n5. Supprimer\n6. "
         "Modifier\n7. Charger CSV\n0. Retour\nChoix : ");
}

void menu_classe_matiere(ClasseMatiereDB *db, ClasseDB *classeDB, MatiereDB *matiereDB) {
    int choix;
    do {
        printf("\n--- ASSOCIATION CLASSE-MATIERE ---\n");
        printf("1. Afficher les associations\n");
        printf("2. Associer une matière à une classe\n");
        printf("3. Dissocier une matière d'une classe\n");
        printf("0. Retour\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        getchar();

        if (choix == 1) {
            afficher_classe_matieres(db);
        } else if (choix == 2) {
            ClasseMatiere rel;
            printf("Code classe : ");
            scanf("%d", &rel.code_classe);
            getchar();
            printf("Référence matière : ");
            scanf("%d", &rel.reference_matiere);
            getchar();
            if (ajouter_classe_matiere(db, rel, classeDB, matiereDB))
                printf("Association ajoutée.\n");
            // Exporter après ajout
            exporter_classe_matieres_csv("./donnees/matiere_clas_asso.csv", db, classeDB, matiereDB);
        } else if (choix == 3) {
            printf("Index à dissocier : ");
            int idx;
            scanf("%d", &idx);
            getchar();
            supprimer_classe_matiere(db, idx);
            // Exporter après suppression
            exporter_classe_matieres_csv("./donnees/matiere_clas_asso.csv", db, classeDB, matiereDB);
        }
    } while (choix != 0);
}
