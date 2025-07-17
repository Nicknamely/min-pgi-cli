#include "./classe/classe.h"
#include "./etudiant/etudiant.h"
#include "./matiere/matiere.h"
#include "./note/note.h"
#include "utils/csv_utils.h"
#include <stdlib.h>
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

int main() {
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
            case 1:
                printf("\n--- CLASSES ---\n");
                printf("1. Afficher\n2. Ajouter\n3. Supprimer\n4. Modifier\n5. Charger CSV\n0. Retour\nChoix : ");
                int c;
                scanf("%d", &c);
                getchar();
                if (c == 1) afficher_classes(&db_classe);
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
                }
                else if (c == 3) {
                    printf("Index à supprimer : ");
                    int idx;
                    scanf("%d", &idx);
                    getchar();
                    supprimer_classe(&db_classe, idx);
                }
                else if (c == 4) {
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
                }
                else if (c == 5) {
                    printf("Chemin du CSV : ");
                    char chemin[128];
                    fgets(chemin, 128, stdin);
                    chemin[strcspn(chemin, "\n")] = 0;
                    if (charger_classes_csv(chemin, &db_classe) == 0) printf("Chargement réussi.\n");
                    else printf("Erreur chargement.\n");
                }
                break;
            case 2:
                printf("\n--- MATIERES ---\n");
                printf("1. Afficher\n2. Ajouter\n3. Supprimer\n4. Modifier\n5. Charger CSV\n0. Retour\nChoix : ");
                int m;
                scanf("%d", &m);
                getchar();
                if (m == 1) afficher_matieres(&db_matiere);
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
                }
                else if (m == 3) {
                    printf("Index à supprimer : ");
                    int idx;
                    scanf("%d", &idx);
                    getchar();
                    supprimer_matiere(&db_matiere, idx);
                }
                else if (m == 4) {
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
                }
                else if (m == 5) {
                    printf("Chemin du CSV : ");
                    char chemin[128];
                    fgets(chemin, 128, stdin);
                    chemin[strcspn(chemin, "\n")] = 0;
                    if (charger_matieres_csv(chemin, &db_matiere) == 0) printf("Chargement réussi.\n");
                    else printf("Erreur chargement.\n");
                }
                break;
            case 3:
                printf("\n--- ETUDIANTS ---\n");
                printf("1. Afficher\n2. Charger CSV\n0. Retour\nChoix : ");
                int e;
                scanf("%d", &e);
                getchar();
                if (e == 1) afficher_etudiants(&db_etudiant);
                else if (e == 2) {
                    printf("Chemin du CSV : ");
                    char chemin[128];
                    fgets(chemin, 128, stdin);
                    chemin[strcspn(chemin, "\n")] = 0;
                    if (charger_etudiants_csv(chemin, &db_etudiant) == 0) printf("Chargement réussi.\n");
                    else printf("Erreur chargement.\n");
                }
                break;
            case 4:
                printf("\n--- NOTES ---\n");
                printf("1. Afficher\n2. Charger CSV\n0. Retour\nChoix : ");
                int n;
                scanf("%d", &n);
                getchar();
                if (n == 1) afficher_notes(&db_note);
                else if (n == 2) {
                    printf("Chemin du CSV : ");
                    char chemin[128];
                    fgets(chemin, 128, stdin);
                    chemin[strcspn(chemin, "\n")] = 0;
                    if (charger_notes_csv(chemin, &db_note) == 0) printf("Chargement réussi.\n");
                    else printf("Erreur chargement.\n");
                }
                break;
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
