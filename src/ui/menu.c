#include "menu.h"
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
    printf("1. Afficher\n2. Ajouter\n3. Supprimer\n4. Modifier\n5. Charger CSV\n0. Retour\nChoix : ");
}

void menu_matieres() {
    printf("\n--- MATIERES ---\n");
    printf("1. Afficher\n2. Ajouter\n3. Supprimer\n4. Modifier\n5. Charger CSV\n0. Retour\nChoix : ");
}

void menu_etudiants() {
    printf("\n--- ETUDIANTS ---\n");
    printf("1. Afficher\n2. Charger CSV\n0. Retour\nChoix : ");
}

void menu_notes() {
    printf("\n--- NOTES ---\n");
    printf("1. Afficher\n2. Charger CSV\n0. Retour\nChoix : ");
}
