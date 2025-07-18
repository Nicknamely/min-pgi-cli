#include "menu.h"
#include "../classe/classe_matiere.h"
#include "../utils/csv_utils.h"
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
  printf("1. Afficher\n2. Ajouter\n3. Supprimer\n4. Modifier\n5. Association "
         "Classe\n6. Charger CSV\n0. Retour\nChoix : ");
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

void menu_classe_matiere() {
  printf("\n--- ASSOCIATION CLASSE-MATIERE ---\n");
  printf("1. Afficher les associations\n");
  printf("2. Associer une matiere a une classe\n");
  printf("3. Dissocier une matiere d'une classe\n");
  printf("0. Retour\n");
  printf("Votre choix : ");
}
