#include "./note.h"
#include "../etudiant/etudiant.h"
#include "../matiere/matiere.h"
#include "../utils/csv_utils.h"
#include <stdio.h>
#include <string.h>

void initialiser_NoteDB(NoteDB *db, size_t capacite_initial) {
  db->notes = malloc(capacite_initial * sizeof(Note));
  if (db->notes == NULL) {
    fprintf(stderr, "allocation memoire echouer\n");
    exit(EXIT_FAILURE);
  }
  db->taille = 0;
  db->capacite = capacite_initial;
}

// Ajout securise : verifie que l'etudiant et la matiere existent
int ajouter_note(NoteDB *db, Note nouvelle_note, const EtudiantDB *etudiantDB,
                 const MatiereDB *matiereDB) {
  if (rechercher_etudiant(etudiantDB, nouvelle_note.numero_etudiant) == -1) {
    printf("etudiant inexistant\n");
    return 0;
  }
  if (rechercher_matiere(matiereDB, nouvelle_note.reference_matiere) == -1) {
    printf("matiere inexistante\n");
    return 0;
  }
  if (db->taille == db->capacite) {
    size_t nouvelle_capacite = db->capacite * 2;
    Note *temp = realloc(db->notes, nouvelle_capacite * sizeof(Note));
    if (temp == NULL) {
      fprintf(stderr, "reallocation memoire echouer\n");
      return 0;
    }
    db->notes = temp;
    db->capacite = nouvelle_capacite;
  }
  db->notes[db->taille++] = nouvelle_note;
  return 1;
}

// Supprime une note par index (decale le tableau)
void supprimer_note(NoteDB *db, size_t index) {
  // verifie la validite de l'index
  if (index >= db->taille) {
    fprintf(stderr, "index invalide\n");
    return;
  }
  // decale les elements pour combler le trou
  for (size_t i = index; i < db->taille - 1; i++) {
    db->notes[i] = db->notes[i + 1];
  }
  db->taille--;
}

// Modifie une note par index (remplace la structure)
void modifier_note(NoteDB *db, size_t index, Note nouvelle_note) {
  if (index >= db->taille) {
    printf("index invalide pour modification\n");
    return;
  }
  db->notes[index] = nouvelle_note;
}

void afficher_notes(const NoteDB *db, const EtudiantDB *db_etudiant,
                    const MatiereDB *db_matiere) {
  if (db->taille == 0) {
    printf("Aucune note a afficher.\n");
    return;
  }
  printf("+-----+--------------+----------------------+----------------------+-"
         "---------------------+----------------------+-------------+----------"
         "---+-------------+-------------+\n");
  printf("| Idx | Etudiant     | Nom                  | Prenom               | "
         "Email                | Matiere              | Coefficient | NoteCC   "
         "   | NoteDS      |\n");
  printf("+-----+--------------+----------------------+----------------------+-"
         "---------------------+----------------------+-------------+----------"
         "---+-------------+-------------+\n");
  for (size_t i = 0; i < db->taille; i++) {
    Note n = db->notes[i];
    int idx_e = -1;
    for (size_t j = 0; j < db_etudiant->taille; j++) {
      if (db_etudiant->etudiants[j].numero == n.numero_etudiant) {
        idx_e = j;
        break;
      }
    }
    int idx_m = -1;
    for (size_t j = 0; j < db_matiere->taille; j++) {
      if (db_matiere->matieres[j].reference == n.reference_matiere) {
        idx_m = j;
        break;
      }
    }
    if (idx_e != -1 && idx_m != -1) {
      Etudiant e = db_etudiant->etudiants[idx_e];
      Matiere m = db_matiere->matieres[idx_m];
      printf("| %3zu | %10d | %-20s | %-20s | %-20s | %-20s | %11d | %9.2f | "
             "%9.2f |\n",
             i, n.numero_etudiant, e.nom, e.prenom, e.email, m.libelle,
             m.coeficient, n.noteCC, n.noteDS);
    }
  }
  printf("+-----+--------------+----------------------+----------------------+-"
         "---------------------+----------------------+-------------+----------"
         "---+-------------+-------------+\n");
}

// Charge les notes depuis un CSV (format: numero_etudiant,reference_matiere,noteCC,noteDS)
// Ajoute chaque note si l'etudiant et la matiere existent
// (Suppression de charger_notes_csv ici)

// Exporte toutes les notes dans un CSV (format: numero_etudiant,reference_matiere,noteCC,noteDS)
// (Suppression d'exporter_notes_csv ici)

int rechercher_note(const NoteDB *db, int numero_etudiant,
                    int reference_matiere) {
  for (size_t i = 0; i < db->taille; i++) {
    if (db->notes[i].numero_etudiant == numero_etudiant &&
        db->notes[i].reference_matiere == reference_matiere) {
      return (int)i;
    }
  }
  return -1;
}

void freeNoteDB(NoteDB *db) {
  if (db->notes) {
    free(db->notes);
    db->notes = NULL;
  }
  db->taille = 0;
  db->capacite = 0;
}

// Ajoute toutes les notes d'un étudiant dans toutes ses matières
int ajouter_notes_etudiant_toutes_matieres(
    NoteDB *db, int numero_etudiant, const EtudiantDB *db_etudiant,
    const ClasseMatiereDB *db_classe_matiere, const MatiereDB *db_matiere) {
  int idx_etudiant = rechercher_etudiant(db_etudiant, numero_etudiant);
  if (idx_etudiant == -1) {
    printf("etudiant inexistant\n");
    return 0;
  }
  int code_classe = db_etudiant->etudiants[idx_etudiant].classe_code;
  int nb_ajoutees = 0;
  for (size_t i = 0; i < db_classe_matiere->taille; i++) {
    if (db_classe_matiere->relations[i].code_classe == code_classe) {
      int ref_matiere = db_classe_matiere->relations[i].reference_matiere;
      Note n;
      n.numero_etudiant = numero_etudiant;
      n.reference_matiere = ref_matiere;
      printf("Saisir noteCC pour matiere %d : ", ref_matiere);
      char buf[32];
      float noteCC = 0, noteDS = 0;
      if (fgets(buf, sizeof(buf), stdin) && sscanf(buf, "%f", &noteCC) == 1) {
        n.noteCC = noteCC;
      } else {
        n.noteCC = 0;
      }
      printf("Saisir noteDS pour matiere %d : ", ref_matiere);
      if (fgets(buf, sizeof(buf), stdin) && sscanf(buf, "%f", &noteDS) == 1) {
        n.noteDS = noteDS;
      } else {
        n.noteDS = 0;
      }
      if (ajouter_note(db, n, db_etudiant, db_matiere)) {
        nb_ajoutees++;
      }
    }
  }
  printf("%d notes ajoutees pour l'etudiant %d\n", nb_ajoutees,
         numero_etudiant);
  return nb_ajoutees;
}

// Ajoute les notes de tous les etudiants d'une classe pour une matiere donnee
int ajouter_notes_classe_matiere(NoteDB *db, int code_classe, int ref_matiere,
                                 const EtudiantDB *db_etudiant,
                                 const ClasseMatiereDB *db_classe_matiere,
                                 const MatiereDB *db_matiere) {
  // Verifier que la matiere est bien associee a la classe
  int trouve = 0;
  for (size_t i = 0; i < db_classe_matiere->taille; i++) {
    if (db_classe_matiere->relations[i].code_classe == code_classe &&
        db_classe_matiere->relations[i].reference_matiere == ref_matiere) {
      trouve = 1;
      break;
    }
  }
  if (!trouve) {
    printf("association classe-matiere inexistante\n");
    return 0;
  }
  int nb_ajoutees = 0;
  for (size_t i = 0; i < db_etudiant->taille; i++) {
    if (db_etudiant->etudiants[i].classe_code == code_classe) {
      Note n;
      n.numero_etudiant = db_etudiant->etudiants[i].numero;
      n.reference_matiere = ref_matiere;
      printf("Saisir noteCC pour etudiant %d : ", n.numero_etudiant);
      char buf[32];
      float noteCC = 0, noteDS = 0;
      if (fgets(buf, sizeof(buf), stdin) && sscanf(buf, "%f", &noteCC) == 1) {
        n.noteCC = noteCC;
      } else {
        n.noteCC = 0;
      }
      printf("Saisir noteDS pour etudiant %d : ", n.numero_etudiant);
      if (fgets(buf, sizeof(buf), stdin) && sscanf(buf, "%f", &noteDS) == 1) {
        n.noteDS = noteDS;
      } else {
        n.noteDS = 0;
      }
      if (ajouter_note(db, n, db_etudiant, db_matiere)) {
        nb_ajoutees++;
      }
    }
  }
  printf("%d notes ajoutees pour la classe %d en matiere %d\n", nb_ajoutees,
         code_classe, ref_matiere);
  return nb_ajoutees;
}

// Suppression interactive d'une note (menu)
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

// Modification interactive d'une note (menu)
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

// Import interactif de notes (menu)
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
