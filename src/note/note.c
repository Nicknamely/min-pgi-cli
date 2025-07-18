#include "./note.h"
#include "../etudiant/etudiant.h"
#include "../matiere/matiere.h"
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

// Ajoute toutes les notes d'un etudiant dans toutes ses matieres
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
  // Verifie que la matiere est bien associee a la classe (sinon rien a faire)
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
    // Pour chaque etudiant de la classe
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
