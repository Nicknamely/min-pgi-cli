#include "menu.h"
#include "../classe/classe_matiere.h"
#include "../utils/csv_utils.h"
#include <stdio.h>


#include "../note/note.h"
#include "../etudiant/etudiant.h"
#include "../matiere/matiere.h"
#include "../utils/csv_utils.h"
#include <string.h>
#include <stdio.h>

void menu_principal() {
  printf("\n--- MENU PRINCIPAL ---\n");
  printf("1. Gestion des classes\n");
  printf("2. Gestion des matieres\n");
  printf("3. Gestion des etudiants\n");
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
  printf("1. Afficher\n2. Ajouter une note (etudiant)\n3. Ajouter une note "
         "(matiere)\n4. Ajouter une note (classe/matiere)\n5. Supprimer\n6. "
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

void supprimer_note_interactive(NoteDB *db_note, const char *chemin_notes) {
    char buffer[128];
    printf("Suppression par : 1.Index  2.Etudiant/Matiere ? ");
    int mode = 0;
    if (fgets(buffer, sizeof(buffer), stdin) && sscanf(buffer, "%d", &mode) == 1) {
        if (mode == 1) {
            printf("Index de la note a supprimer : ");
            int idx;
            if (fgets(buffer, sizeof(buffer), stdin) && sscanf(buffer, "%d", &idx) == 1) {
                supprimer_note(db_note, idx);
                exporter_notes_csv(chemin_notes, db_note);
                printf("Note supprimee.\n");
            } else {
                printf("Entree invalide.\n");
            }
        } else if (mode == 2) {
            int num_etudiant, ref_matiere;
            printf("Numero etudiant : ");
            if (fgets(buffer, sizeof(buffer), stdin) && sscanf(buffer, "%d", &num_etudiant) == 1) {
                printf("Reference matiere : ");
                if (fgets(buffer, sizeof(buffer), stdin) && sscanf(buffer, "%d", &ref_matiere) == 1) {
                    int idx = rechercher_note(db_note, num_etudiant, ref_matiere);
                    if (idx != -1) {
                        supprimer_note(db_note, idx);
                        exporter_notes_csv(chemin_notes, db_note);
                        printf("Note supprimee.\n");
                    } else {
                        printf("Note introuvable.\n");
                    }
                } else {
                    printf("Entree invalide.\n");
                }
            } else {
                printf("Entree invalide.\n");
            }
        }
    }
}

void modifier_note_interactive(NoteDB *db_note, const char *chemin_notes) {
    char buffer[128];
    printf("Modification par : 1.Index  2.Etudiant/Matiere ? ");
    int mode = 0;
    if (fgets(buffer, sizeof(buffer), stdin) && sscanf(buffer, "%d", &mode) == 1) {
        int idx = -1;
        if (mode == 1) {
            printf("Index de la note a modifier : ");
            if (fgets(buffer, sizeof(buffer), stdin) && sscanf(buffer, "%d", &idx) == 1) {
                if (idx < 0 || (size_t)idx >= db_note->taille) {
                    printf("Index hors borne.\n");
                    return;
                }
            } else {
                printf("Entree invalide.\n");
                return;
            }
        } else if (mode == 2) {
            int num_etudiant, ref_matiere;
            printf("Numero etudiant : ");
            if (fgets(buffer, sizeof(buffer), stdin) && sscanf(buffer, "%d", &num_etudiant) == 1) {
                printf("Reference matiere : ");
                if (fgets(buffer, sizeof(buffer), stdin) && sscanf(buffer, "%d", &ref_matiere) == 1) {
                    idx = rechercher_note(db_note, num_etudiant, ref_matiere);
                    if (idx == -1) {
                        printf("Note introuvable.\n");
                        return;
                    }
                } else {
                    printf("Entree invalide.\n");
                    return;
                }
            } else {
                printf("Entree invalide.\n");
                return;
            }
        }
        if (idx != -1) {
            float noteCC, noteDS;
            printf("Nouvelle note CC (0-20) : ");
            if (!(fgets(buffer, sizeof(buffer), stdin) && sscanf(buffer, "%f", &noteCC) == 1 && noteCC >= 0 && noteCC <= 20)) {
                printf("Note CC invalide.\n");
                return;
            }
            printf("Nouvelle note DS (0-20) : ");
            if (!(fgets(buffer, sizeof(buffer), stdin) && sscanf(buffer, "%f", &noteDS) == 1 && noteDS >= 0 && noteDS <= 20)) {
                printf("Note DS invalide.\n");
                return;
            }
            Note n = db_note->notes[idx];
            n.noteCC = noteCC;
            n.noteDS = noteDS;
            modifier_note(db_note, idx, n);
            exporter_notes_csv(chemin_notes, db_note);
            printf("Note modifiee.\n");
        }
    }
}

void importer_notes_interactive(NoteDB *db_note, const char *chemin_notes, const EtudiantDB *db_etudiant, const MatiereDB *db_matiere) {
    char chemin[128];
    printf("Chemin du CSV a importer : ");
    fgets(chemin, 128, stdin);
    chemin[strcspn(chemin, "\n")] = 0;
    if (charger_notes_csv(chemin, db_note, db_etudiant, db_matiere) == 0)
        printf("Import reussi.\n");
    else
        printf("Erreur import.\n");
    exporter_notes_csv(chemin_notes, db_note);
}
