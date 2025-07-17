#include "./note.h"
#include "../etudiant/etudiant.h"
#include "../matiere/matiere.h"
#include <stdio.h>

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

void supprimer_note(NoteDB *db, size_t index) {
  if (index >= db->taille) {
    fprintf(stderr, "index invalide\n");
    return;
  }
  for (size_t i = index; i < db->taille - 1; i++) {
    db->notes[i] = db->notes[i + 1];
  }
  db->taille--;
}

void afficher_notes(const NoteDB *db) {
  if (db->taille == 0) {
    printf("aucune note a afficher\n");
    return;
  }
  for (size_t i = 0; i < db->taille; i++) {
    Note n = db->notes[i];
    printf("[%zu] etudiant: %d | matiere: %d | cc: %.2f | ds: %.2f\n", i,
           n.numero_etudiant, n.reference_matiere, n.noteCC, n.noteDS);
  }
}

void modifier_note(NoteDB *db, size_t index, Note nouvelle_note) {
  if (index >= db->taille) {
    printf("index invalide pour modification\n");
    return;
  }
  db->notes[index] = nouvelle_note;
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
